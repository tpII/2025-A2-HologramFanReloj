#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// SENSOR HALL
#define HALL_PIN D5  

// SHIFT REGISTER
#define DATA  D2
#define CLOCK D7
#define LATCH D8

// VARIABLES RPM 
volatile unsigned long ultimaDeteccion = 0;
volatile unsigned long periodo = 0;     // en microsegundos

// RELOJ
int hours   = 12;
int minutes = 15;
int seconds = 0;
unsigned long lastSecondMillis = 0;

const int NUM_COLS = 120;

// SERVIDOR WEB
ESP8266WebServer server(80);
float rpm_global = 0.0f;

// MAPEO DIGITOS
int MAPEO[8] = {
  1, 2, 3, 4, 5, 6, 7, 0
};

const uint8_t digitFont[10][3] = {
  {0x1F, 0x11, 0x1F},
  {0x09, 0x1F, 0x01},
  {0x17, 0x15, 0x1D},
  {0x15, 0x15, 0x1F},
  {0x1C, 0x04, 0x1F},
  {0x1D, 0x15, 0x17},
  {0x1F, 0x15, 0x17},
  {0x10, 0x10, 0x1F},
  {0x1F, 0x15, 0x1F},
  {0x1D, 0x15, 0x1F}
};

const uint8_t colonFont = 0x0A; // DOS PUNTOS

// GIRO VERTICAL
uint8_t flipVertical5(uint8_t b) {
  uint8_t r = 0;
  if (b & 0x01) r |= 0x10;
  if (b & 0x02) r |= 0x08;
  if (b & 0x04) r |= 0x04;
  if (b & 0x08) r |= 0x02;
  if (b & 0x10) r |= 0x01;
  return r;
}

// ISR HALL
void IRAM_ATTR detectarIman() {
  unsigned long ahora = micros();
  unsigned long dt = ahora - ultimaDeteccion;

  if (dt > 5000) periodo = dt;

  ultimaDeteccion = ahora;
}

// SALIDA SHIFT
void sendByte(uint8_t b) {
  digitalWrite(LATCH, LOW);
  shiftOut(DATA, CLOCK, MSBFIRST, b);
  digitalWrite(LATCH, HIGH);
}

void apagarTodos() {
  sendByte(0);
}

//GENERAR COLUMNA
uint8_t mostrar8bits(uint16_t mask5bitsShifted) {
  uint8_t phys = 0;

  for (int fila = 0; fila < 8; fila++) {
    int bitFuente = fila + 5;
    if (mask5bitsShifted & (1 << bitFuente)) {
      phys |= (1 << MAPEO[fila]);
    }
  }

  sendByte(phys);
  return phys;
}

// DIBUJAR HORA COMPLETA
uint16_t getTimeColumnMask(int col, int h, int m, int s) {

  int d1 = (h / 10) % 10;
  int d2 = h % 10;
  int d3 = (m / 10) % 10;
  int d4 = m % 10;
  int d5 = (s / 10) % 10;
  int d6 = s % 10;

  struct GlyphSpan { int type; int width; };

  GlyphSpan glyphs[] = {
    { d1, 3 }, { -1, 1 },
    { d2, 3 }, { -1, 1 },
    { 10, 1 }, { -1, 1 },

    { d3, 3 }, { -1, 1 },
    { d4, 3 }, { -1, 1 },
    { 10, 1 }, { -1, 1 },

    { d5, 3 }, { -1, 1 },
    { d6, 3 }
  };

  int GLYPH_COUNT = sizeof(glyphs) / sizeof(GlyphSpan);

  int totalWidth = 0;
  for (int i = 0; i < GLYPH_COUNT; i++) totalWidth += glyphs[i].width;

  int textStart = (NUM_COLS - totalWidth) / 2;
  int textEnd   = textStart + totalWidth;

  if (col < textStart || col >= textEnd) return 0;

  int localCol = col - textStart;

  for (int i = 0; i < GLYPH_COUNT; i++) {
    if (localCol < glyphs[i].width) {

      if (glyphs[i].type == -1) return 0;

      uint8_t colPattern5bits = 0;

      if (glyphs[i].type == 10) {
        colPattern5bits = colonFont;
      }
      else if (glyphs[i].type >= 0) {
        colPattern5bits = digitFont[glyphs[i].type][localCol];
      }

      colPattern5bits = flipVertical5(colPattern5bits);

      return ((uint16_t)colPattern5bits) << 5;
    }

    localCol -= glyphs[i].width;
  }

  return 0;
}

// HTML PAGINA
String htmlPage(String mensaje = "") {

  String html =
  "<html><head>"
  "<meta name='viewport' content='width=device-width, initial-scale=1'>"
  "<style>"
  "body{font-family:Arial;background:#111;color:#eee;text-align:center;padding:20px;}"
  ".msg{background:#2a2;padding:10px;border-radius:10px;margin-bottom:15px;}"
  ".box{background:#222;padding:20px;border-radius:15px;display:inline-block;}"
  "input{font-size:20px;width:70px;padding:8px;margin:5px;border-radius:8px;border:none;text-align:center;}"
  "button{font-size:20px;padding:10px 25px;margin-top:10px;border:none;border-radius:10px;background:#4CAF50;color:white;}"
  "</style>"
  "</head><body>"
  "<h1>Configurar Hora</h1>";

  if (mensaje.length() > 0)
    html += "<div class='msg'>" + mensaje + "</div>";

  // hora dinámicamente actualizada por JS
  html += "<h2 id='hora'>Cargando hora...</h2>";

  html +=
  "<div class='box'>"
  "<form method='POST' action='/settime'>"
    "<input name='h' type='number' min='0' max='23' value='" + String(hours) + "'> : "
    "<input name='m' type='number' min='0' max='59' value='" + String(minutes) + "'> : "
    "<input name='s' type='number' min='0' max='59' value='" + String(seconds) + "'><br>"
    "<button type='submit'>Actualizar</button>"
  "</form>"
  "</div>"

  "<script>"
  "function actualizarHora(){"
  " fetch('/time')"
  "  .then(r=>r.json())"
  "  .then(t=>{"
  "    var hh=t.h.toString().padStart(2,'0');"
  "    var mm=t.m.toString().padStart(2,'0');"
  "    var ss=t.s.toString().padStart(2,'0');"
  "    document.getElementById('hora').innerText='Hora actual: '+hh+':'+mm+':'+ss;"
  "  });"
  "}"
  "setInterval(actualizarHora,1000);"
  "actualizarHora();"
  "</script>"

  "</body></html>";

  return html;
}

// MANEJADORES WEB
void handleRoot() {
  server.send(200, "text/html", htmlPage());
}

void handleSetTime() {
  if (server.hasArg("h")) hours   = server.arg("h").toInt();
  if (server.hasArg("m")) minutes = server.arg("m").toInt();
  if (server.hasArg("s")) seconds = server.arg("s").toInt();

  hours   = constrain(hours,   0, 23);
  minutes = constrain(minutes, 0, 59);
  seconds = constrain(seconds, 0, 59);

  server.send(200, "text/html", htmlPage("Hora actualizada correctamente"));
}

void handleGetTime() {
  String json = "{";
  json += "\"h\":" + String(hours) + ",";
  json += "\"m\":" + String(minutes) + ",";
  json += "\"s\":" + String(seconds);
  json += "}";
  server.send(200, "application/json", json);
}


// SETUP
void setup() {
  Serial.begin(115200);

  pinMode(HALL_PIN, INPUT_PULLUP);
  pinMode(DATA, OUTPUT);
  pinMode(CLOCK, OUTPUT);
  pinMode(LATCH, OUTPUT);

  apagarTodos();

  WiFi.mode(WIFI_AP);
  WiFi.softAP("RPM_Reloj", "12345678");

  Serial.println("AP listo!");
  Serial.println("http://192.168.4.1");

  attachInterrupt(digitalPinToInterrupt(HALL_PIN), detectarIman, FALLING);

  server.on("/", handleRoot);
  server.on("/settime", HTTP_POST, handleSetTime);
  server.on("/time", handleGetTime);
  server.begin();

  lastSecondMillis = millis();
}

// LOOP
void loop() {

  unsigned long nowMs = millis();
  if (nowMs - lastSecondMillis >= 1000) {
    lastSecondMillis += 1000;

    seconds++;
    if (seconds >= 60) { seconds = 0; minutes++; }
    if (minutes >= 60) { minutes = 0; hours++; }
    if (hours >= 24)   { hours = 0; }
  }

  unsigned long localPeriodo, localUltima;
  noInterrupts();
  localPeriodo = periodo;
  localUltima  = ultimaDeteccion;
  interrupts();

  if (localPeriodo == 0) {
    apagarTodos();
  } else {
    rpm_global = 60000000.0 / (float)localPeriodo;

    unsigned long nowUs = micros();
    unsigned long dt = nowUs - localUltima;
    if (dt >= localPeriodo) dt %= localPeriodo;

    float frac = (float)dt / (float)localPeriodo;
    int col = (int)(frac * NUM_COLS);
    if (col >= NUM_COLS) col = NUM_COLS - 1;

    uint16_t mask = getTimeColumnMask(col, hours, minutes, seconds);
    mostrar8bits(mask);
  }

  server.handleClient();
}

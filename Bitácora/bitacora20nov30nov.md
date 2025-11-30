#Bitácora Semanal – Semana del 20 al 30 de noviembre

##Detección del Fallo en el Conector Giratorio

Al comenzar las pruebas se observó que el sistema dejaba de mostrar correctamente algunos LEDs.
Primero se pensó que el error era ruido metido por los cables, por lo que soldamos a una placa asi dejamos de usar esos cables, pero aun seguía sin andar.
Luego se revisaron las conexiones del conector giratorio y se realizó una medición de continuidad en cada línea.
Durante la prueba se descubrió que uno de los cables del conector había dejado de conducir, lo que afectaba toda una columna de LEDs.
Dado que no era posible reparar el cable individual, se decidió sacrificar una columna completa, reduciendo la cantidad de líneas utilizadas.
Para mantener el funcionamiento mínimo esencial del sistema, se conservaron únicamente cinco cables necesarios para los registros 74HC595:
Vcc, GND, Latch, Clock, Data

Con esta reconfiguración fue posible continuar operando la matriz de LEDs, aunque ahora limitada a 8 LEDs útiles.

##Ajustes de Código y Visualización de la Hora

Tras modificar las conexiones físicas, fue necesario adaptar el código para manejar únicamente los 8 LEDs disponibles.
Se actualizaron los patrones para mostrar correctamente la hora completa con minutos y segundos (HH:MM:SS).

Posteriormente se agregó una nueva funcionalidad:
el ESP8266 levanta un Access Point con una página web, desde donde se puede configurar la hora actual.
Al ingresar manualmente la hora, el sistema ajusta sus valores internos y actualiza inmediatamente la visualización en la hélice.

En el drive se puede ver el video del holograma funcionando, y una imagen de la pagina levantada por el access point: https://drive.google.com/drive/folders/1sZ_75MWhc0w5avFAjfK5a24StMbPqEwb?usp=sharing

##Problemas con la Velocidad del Motor

Durante las pruebas prolongadas surgió un problema adicional:
el motor comenzaba girando bien, pero tras unos segundos su velocidad disminuía progresivamente hasta detenerse.

Se analizaron las conexiones y se detectó que la causa era una soldadura defectuosa en los cables del motor, lo que provocaba variaciones intermitentes en la alimentación.

##Próximos Pasos

El siguiente paso será resoldar correctamente los cables del motor, asegurando una unión firme y sin falsos contactos.
Una vez realizada esta reparación, el sistema debería mantener una velocidad estable para permitir el funcionamiento continuo del reloj.

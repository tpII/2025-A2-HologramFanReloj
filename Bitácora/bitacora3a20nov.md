# Bitácora Semanal – Semanas del 3 al 20 de Noviembre
## Integración del Sensor Hall y Sincronización del Sistema

## Problema Inicial con el Sensor Hall
Durante las primeras pruebas de esta etapa, el sensor Hall no registraba el paso del imán de la hélice.  
Se revisaron conexiones, el código y hasta el propio sensor, sin resultados.
Finalmente se detectó la causa: el Hall y el ESP8266 no compartían el mismo Vcc y GND.  
Una vez unificados los puntos de alimentación, el sensor comenzó a responder de manera correcta y estable.

## Ajustes Mecánicos para la Detección
Con el Hall funcionando, se trabajó sobre la alineación del imán adherido a la hélice.  
El sensor requiere que el imán pase muy cerca de su superficie para generar un pulso confiable, por lo que se realizaron varias pruebas moviendo la altura y el ángulo del soporte.
Después de estos ajustes, se logró que el imán pase a pocos milímetros del Hall sin rozar, permitiendo una detección consistente incluso con el motor girando.

## Pruebas Dinámicas con el Motor
Una vez alineados ambos elementos, se encendió el motor para comprobar si el sensor seguía registrando el paso del imán en movimiento.

## Primer Código: Medición de RPM
Se desarrolló un primer código dedicado exclusivamente a medir las revoluciones por minuto del motor.  
A partir de los pulsos del Hall, se obtuvieron valores estables entre 700 y 720 RPM.
Se observó también que, tras varios minutos encendido, el motor se calienta y pierde levemente velocidad, bajando algunos RPM respecto al valor inicial.

## Segundo Código: Sincronización de LEDs por Posición
Con la velocidad del motor conocida, se programó un segundo código para controlar la activación vertical de los LEDs.
El pulso del Hall se tomó como posición angular cero, permitiendo sincronizar el patrón visual con cada vuelta de la hélice.

El link del drive contiene el video de esta prueba: https://drive.google.com/drive/u/0/folders/1qLg9ZE9C3drEAhVaZB5uGrzww2Yv27y0

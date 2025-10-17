#  Semana del 13 al 17 de Octubre

## Avances Realizados

Durante esta semana se completaron las soldaduras finales de los componentes montados sobre la hélice, conectando los registros de desplazamiento 74HC595 con los 16 LEDs del sistema y realizando las conexiones correspondientes hacia el conector giratorio.

Además, se definió que no todos los componentes electrónicos estarán sobre la hélice.  
El sensor Hall A3144 y la placa ESP8266 se ubicaron en la base fija, mientras que los LEDs y registros de desplazamiento permanecerán en la parte giratoria.  

## Pruebas Realizadas

- **Prueba de motor:** se verificó el funcionamiento del motor actual en conjunto con la estructura.  
- **Prueba de red Wi-Fi:** la ESP8266 logró levantar un Access Point correctamente como prueba de conectividad inicial.  
- **Prueba de encendido de LEDs:** se encendieron los LEDs mediante los registros 74HC595. En esta instancia se detectó un problema de soldadura, ya que los LEDs controlados por uno de los registros se encendían todos juntos, en lugar de manera individual.  
Se determinó que el error proviene de la soldadura, por lo que la próxima tarea será corregir la soldadura y volver a testear el control individual de cada LED.

## Decisiones de Diseño

Se reemplazará el motor actual por otro con mayor número de RPM, tras determinar que el original no lograba una velocidad adecuada para el efecto holográfico.

## Justificación de la Velocidad del Motor

El efecto holográfico se basa en la persistencia de la visión, la cual requiere que la hélice complete una rotación lo suficientemente rápida como para que el ojo humano perciba una imagen estable.  
Considerando una tasa de percepción de 24–30 cuadros por segundo (FPS).
En la práctica, con valores en torno a 16 FPS la persistencia de la visión ya permite que las figuras sean claramente perceptibles y estables. Por lo que se determinó que un motor de 1000 RPM es suficiente para lo que se busca lograr (16FPSx60=960 RPM).

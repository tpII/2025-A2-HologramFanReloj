# Bitácora Semanal – Semanas del 20 de Octubre al 3 de Noviembre

## Construcción de la Base

Durante esta etapa se construyó la base del sistema utilizando piezas de madera, lo que permitió obtener una estructura firme y estable para sostener tanto el motor como el conector giratorio. Es pesada para evitar balanceo.

## Pruebas de Motores y Solución de Torque

Esta semana llegaron los nuevos motores adquiridos para reemplazar el anterior.  
Sin embargo, al probarlos se observó que ninguno tenía el torque suficiente para mover correctamente la hélice junto con el conector rotatorio, el cual tambien hacía de traba, lo que impedía alcanzar una velocidad de giro adecuada.

Para resolverlo, se adaptó uno de los nuevos motores acoplándole la caja reductora del motor original de Arduino, aprovechando que ambas piezas eran compatibles.  
Con esta modificación, se logró obtener el torque necesario para hacer girar la hélice de manera estable, con la perdida considerable de velocidad, pero que era necesaria, pues el conector rotatorio de todas maneras no permite un giro de tantos RPM.

## Reemplazo del Conector Giratorio

Durante las pruebas se notó que el conector giratorio anterior generaba una gran fricción, afectando notablemente la velocidad del sistema.  
Se decidió reemplazarlo por otro con menor resistencia mecánica, lo cual mejoró la libertad de giro.

Para ello fue necesario:
- Desoldar el conector anterior.
- Soldar el nuevo, cuidando la polaridad y el orden de las líneas.
- Verificar continuidad con el multímetro para cada pin.
- Probar encendido de los LEDs para asegurar que la conexión eléctrica fuera correcta.

Todas las líneas fueron comprobadas y se confirmó que los 18 LEDs encienden correctamente con el nuevo conector instalado.

## Integración Final y Pruebas Iniciales

Una vez verificado el correcto funcionamiento del motor y el conector, se procedió a montar todo el conjunto sobre la base de madera, asegurando tanto la hélice como los cables de conexión.  
En esta instancia se cargó un primer código de prueba, el cual permitió:
- Encender los LEDs mediante los registros 74HC595.  
- Activar el motor en simultáneo desde la base.  

Estas pruebas iniciales confirmaron la correcta integración eléctrica y mecánica del sistema.

Se adjunta link a un drive con fotos de como quedo la base y un video de la prueba mencionada: https://drive.google.com/drive/folders/11d92gohjuYRsEgTqIoQc2lDO1TWfNLhJ?usp=sharing

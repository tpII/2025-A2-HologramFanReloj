# Holograma Fan Reloj

Proyecto desarrollado con fines académicos en la materia Taller de Proyecto 2 en la Facultad de Informática de la UNLP.

## 👨‍💻 Autores
- Franco Niderhaus
- Mateo Larsen
- Bruno Zanetti


## 📌 Descripción general

Este proyecto consiste en el diseño e implementación de un sistema embebido tipo “holograma fan” capaz de mostrar la hora en formato digital mediante una hélice rotativa con LEDs sincronizados.

Aprovechando el fenómeno de persistencia de la visión, el sistema controla el encendido preciso de los LEDs en función de la velocidad de rotación, logrando la visualización de caracteres “flotantes” en el aire.

El proyecto integra programación de bajo nivel, electrónica digital y control de tiempo, con foco en la sincronización precisa y la estabilidad del sistema.

## 🎯 Objetivos del proyecto

- Diseñar un sistema embebido capaz de mostrar información visual mediante LEDs en rotación.

- Implementar un reloj digital con control preciso del tiempo.

- Lograr sincronización confiable entre la rotación mecánica y el encendido de los LEDs.

- Aplicar conceptos de programación en C, temporización y manejo de interrupciones.

- Integrar hardware y software en un sistema funcional y estable.

## ⚙️ Funcionamiento general

1. Un sensor detecta la posición de referencia de la hélice en cada vuelta.

2. El microcontrolador mide el período de rotación.

3. A partir de ese período, se calculan los instantes exactos para encender los LEDs.

4. Se renderizan los caracteres de la hora columna por columna durante cada giro.

5. La sincronización se ajusta dinámicamente ante cambios de velocidad.

## 🛠 Tecnologías y herramientas utilizadas

### Software

- Lenguaje C

- Programación de bajo nivel

- Control de temporización

- Renderizado de caracteres

- Manejo de interrupciones

### Hardware

- Microcontrolador

- LEDs

- Sensor de posición / efecto Hall

- Circuitos de control y alimentación

## 📐 Aspectos técnicos destacados

- Sincronización precisa entre velocidad de rotación y encendido de LEDs.

- Renderizado eficiente de caracteres para minimizar errores visuales.

- Control estable del tiempo de visualización.

- Integración completa entre electrónica y software.




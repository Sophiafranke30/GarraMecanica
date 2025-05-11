# Proyecto 2 de Electrónica Digital 1
**Sophia Franke (23030) y Dulce Ovando (23441)**

## Descripción del Proyecto:
Este proyecto consiste en el control de una garra mecánica con 4 grados de libertad utilizando:
- 2 joysticks para el control manual de los servomotores.
- Un modo automático de 5 pasos predefinidos para movimientos repetitivos.
- Una pantalla LCD para mostrar los ángulos actuales de los 4 servomotores.
- LEDs para indicar si el sistema está en modo manual o automático.
- Botones con anti-rebote para avanzar o retroceder los pasos de la rutina automática.
- Switch para selector de modo.

## Componentes Utilizados:
- 4 x Servomotor
- 2 x Joysticks
- 1 x Pantalla LCD
- 2 x Pushbuttons
- 2 x LED
- 1 x Switch manual
- 1 x Arduino Nano

## Funcionamiento:
- **Modo Manual (LED Verde):**
Cada servomotor se controla con cada eje del joystick en tiempo real. Los ángulos de los 4 servomotores se presentan en la pantalla LCD.
- **Modo Automático (LED amarillo):**
Se ejecutan los 5 pasos o posiciones preprogramados controlados por los 2 pushbuttons. Los ángulos de los 4 servomotores se presentan en la pantalla LCD.

## Funciones a utilizar:
### "LecturaJoystick():"
lee los 2 ejes del joystick (4 ejes en total para 4 seromotores) y los mapea en ángulos de 0° a 180°. Guarda estas lecturas en el array 'angulos[]'.
### "():"
texto texto

## Notas adicionales:
- Se utiliza la librería Bounce2 que ayuda a evitar el rebote electrónico de los botones a la hora de presionarlos.
- Se utilizan arrays o arreglos para hacer menos redundante y resumido el código.


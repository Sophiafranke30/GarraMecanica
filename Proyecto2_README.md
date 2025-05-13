# Proyecto 2 de Electrónica Digital 1
**Sophia Franke (23030) y Dulce Ovando (23441)**

## Descripción del Proyecto:
Este proyecto implementa un sistema de control para cuatro servomotores utilizando un Arduino. El sistema puede funcionar en dos modos: manual, donde los servos son controlados por joysticks, y automático, donde se ejecutan configuraciones predefinidas. También incluye una pantalla LCD para visualizar el estado del sistema y botones físicos con control de rebote para cambiar configuraciones o modos de operación.

## Archivos
El código se encuentra en el archivo **Proyecto_GM**. Los demás archivos contienen drafts y versiones de cada funcionalidad antiguas.

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
- **LCD**
Demuestra los valores de los 4 servos, el modo en el que se encuentra actualmente y en caso del Modo Automático, la rutina predeterminada en la que se encuentra.
- **Cambio Mediante Botón**
Las configuraciones predeterminadas del Modo Automático se cambian con 2 pushbuttons
- **Sistema antirrebote para botones de Next y Previous**
Los botones utilizan la librería de Bounce2 para evitar el rebote eléctrico o falsos positivos.

## Funciones a utilizar:
### `void setup()`
Inicializa todos los dispositivos del sistema:
- LCD, servos, pines de entrada/salida, LEDs y botones con rebote.
- Determina el modo inicial y carga la configuración correspondiente.
- Muestra el estado inicial en pantalla.

### `void loop()`
Función principal que corre en bucle:
- Detecta pulsaciones de botones para cambiar de modo o configuración.
- Ejecuta las funciones según el modo actual (manual o automático).
- Actualiza servos y pantalla.

### `void LeerJoysticks()`
Lee el movimiento del joystick y ajusta los valores de los ángulos de los servos. Aplica una "centro" del joystick para evitar movimientos accidentales.

### `void MoverServos()`
Envía los valores actuales a cada uno de los cuatro servomotores a ellos y los mueve.

### `void MostrarenLCD()`
Decide qué mostrar en la pantalla LCD dependiendo del modo actual:
- Manual: llama a `MostrarenLCDModoManual()`
- Automático: llama a `MostrarenLCDModoAutomatico()`

### `void MostrarenLCDModoManual()`
Muestra en el LCD los ángulos de los servos y el modo "M".

### `void MostrarenLCDModoAutomatico()`
Muestra en el LCD los ángulos de los servos, el número de rutina cargada y el modo "A".

### `void ModoLED(bool manual)`
Controla qué LED se enciende según el modo actual.

### `void LoadConfig()`
Carga los valores de ángulos almacenados en el array `rutina` según la configuración actual.

### `void NextConfig()`
Avanza a la siguiente rutina automática.

### `void PrevConfig()`
Retrocede a la rutina anterior automática.

### `String formatAngle(int angle)`
Devuelve una cadena con el ángulo en formato de **tres dígitos** (ejemplo: `005`, `090`, `180`).

## Notas adicionales:
- Se utiliza la librería Bounce2 que ayuda a evitar el rebote electrónico de los botones a la hora de presionarlos.
- Se utilizan arrays o arreglos para hacer menos redundante y resumido el código.


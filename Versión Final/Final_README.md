Sophia Franke (23030) y Dulce Ovando (23441)
> [!IMPORTANT]
> Esta es la segunda versión del proyecto ya que la primera no funcionó y decidimos volver a realizar la programación del código. El original aún se encuentra en la carpeta llamada "Versión 1".

> [!NOTE]
> Link de [Wokwi](https://wokwi.com/projects/431972882495184897) es el adjuntado aquí.
> El archivo donde se encuentra la programación final es el llamado: ****.


# Control de Brazo Robótico/Garra Mecánica
El proyecto consiste en el control de un brazo robótico de 4 grados de libertad (base, brazo derecho, brazo izquierdo y pinza) mediante dos modos: **control manual** con joystick o **modo automático** basado en 5 rutinas predefinidas. Además, muestra información en tiempo real en una pantalla **LCD 20x4** del modo en que se encuentra y el ángulo de los 4 servomotores.

# Generalidades
## **1. Componentes Utilizados:**
  - 4 Servomotores
  - `servo1`: base (gira el brazo)
  - `servo2`: brazo derecho
  - `servo3`: brazo izquierdo
  - `servo4`: pinza
  - 2 Joysticks para modo manual
  - 2 Pushbuttons para cambiar de rutina preestablecida en modo automático.
  - 1 Switch para cambiar de modo de operación.
  - 1 LCD 20x4 para demostrar los ángulos y el modo.
  - Resistencias 220 Ohms
  - Potenciómetro 10K
  - 
## **2. Librerías utilizadas:**
  - **_Servo.h_**: para los servomotores.
  - **_LiquidCrystal.h_**: para la pantalla LCD.

## **3. Funciones a Utilizar:**
  - **_manualControl():_** lee los valores de los ejes de los joysticks y mapea los valores analógicos (0-1023) a rangos de 0° a 180° para enviarlo a los servomotores. Esta ajusta las posiciones de lo servomotores de 1 en 1 y se actuva cuando el switch está en **LOW**.
  
  - **_automatico():_** lee los dos botones para avanzar o retroceder en la rutina. Cada paso tiene una combinación de 4 ángulos para los servomotores y utiliza el _lastDebounceTime_ y _debounceDelay_ como método de antirrebote junto a la función *millis()*.
    
  - **_leerModo():_** detecta el modo del switch @@ LOW @@ para el modo manual y **HIGH** para el modo automático.
    
  - **_moverServos():_** es la función empleada para actualizar las posiciones de los servos.
    
  - **_updateLCD():_** es la encargada de actualizar y mostrar la infomación en la pantalla LCD. Esta demuestra el modo actual (**M** o **A**), las posiciones actuales de todos los servos, indica si está activo el joystick en modo manual o en que paso de la rutina se encuentra en modo automático. Solo se actualiza si hay cambios en algo, por lo que se evita el parpadeo de la pantalla. Utiliza **formatAngle(int angle)** para formatear el ángulo a 3 cifras y añadiendo el símbolo de grados **"°"**.

# Links Utilizados 
Los siguientes links son los que se consultaron durante la creación del código para ayuda de sintaxis y formato tanto de este README como del código.
* [Debounce del pushbutton](https://docs.arduino.cc/built-in-examples/digital/Debounce/).
* [Arrays](https://docs.arduino.cc/language-reference/en/variables/data-types/array/).
* Librería [LiquidCrystal](https://docs.arduino.cc/libraries/liquidcrystal/).
* [Joysticks](https://docs.arduino.cc/tutorials/generic/interfacing-a-joystick/).
* Variables solo disponible en una función y no las otras [Static](https://docs.arduino.cc/language-reference/en/variables/variable-scope-qualifiers/static/).
* [Transiciones](https://forum.arduino.cc/t/smooth-transition-between-new-and-old-value/492038) suaves entre los ángulos de los servomotores.
* [Arrays multidimensionales](https://forum.arduino.cc/t/how-to-initialize-or-declare-a-multidimensional-array/214582)
* Generalidades de [Arduino](https://www.youtube.com/watch?v=NazqZ3svrfs).
* [Formateo de GitHub](https://docs.github.com/en/get-started/writing-on-github/getting-started-with-writing-and-formatting-on-github/basic-writing-and-formatting-syntax#lists)

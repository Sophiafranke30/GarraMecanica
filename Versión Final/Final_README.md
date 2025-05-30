Sophia Franke (23030) y Dulce Ovando (23441)
> [!IMPORTANT]
> Esta es la segunda versión del proyecto ya que la primera no funcionó y decidimos volver a realizar la programación del código. El original aún se encuentra en la carpeta llamada "Versión 1".

> [!NOTE]
> Link de [Wokwi](https://wokwi.com/projects/431972882495184897) es el adjuntado aquí.
> El archivo donde se encuentra la programación final es el llamado: **Proyecto_2.ino**.
> Link del [video](https://www.canva.com/design/DAGozV7WFKk/znER21fBJ3m2nXFhi5JNfA/edit?utm_content=DAGozV7WFKk&utm_campaign=designshare&utm_medium=link2&utm_source=sharebutton) explicativo de la simulación, funcionamiento y el código.


# Control de Brazo Robótico/Garra Mecánica
El proyecto consiste en el control de un brazo robótico de 4 grados de libertad (base, brazo derecho, brazo izquierdo y pinza) mediante dos modos: **control manual** con joystick o **modo automático** basado en 5 rutinas predefinidas. Además, muestra información en tiempo real en una pantalla **LCD 20x4** del modo en que se encuentra y el ángulo de los 4 servomotores.

# Generalidades
## **1. Componentes Utilizados:**
  - 4 Servomotores
  - `servo1`: base (gira el brazo)
  - `servo2`: brazo derecho
  - `servo3`: brazo izquierdo
  - `servo4`: pinza
  - 4 Potenciómetros de 10K ohms.
  - 2 Pushbuttons para cambiar de rutina preestablecida en modo automático.
  - 2 LEDs para determinar el estado
  - 1 Switch para cambiar de modo de operación.
  - Resistencias 220 Ohms
  - 
## **2. Librerías utilizadas:**
  - **_Servo.h_**: para los servomotores.

## **3. Funciones a Utilizar:**
  - **_modoManual():_** lee los valores dados por los potenciómetros y los mapea en un rango de 0° a 180° para que estos sean escritos en cada uno de los servos.
  
  - **_modoAutomatico():_** lee cuando esté un botón en HIGH o en LOW para avanzar o retroceder en la rutina cíclica y utiliza case switch para escribir las posiciones en los potenciómetros.
    
  - **_imprimirEstado():_** imprime en el monitor serial el estado en el que se encuentra, la rutina actual y los ángulos de cada servo.

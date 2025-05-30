// Sophia Franke | 23030
// Dulce Ovando  | 23441
//Proyecto II
//Electrónica Digital I

#include <Servo.h>

Servo servoBase, servoBrazoIzquierdo, servoBrazoDerecho, servoGarra;

const int pinPotenciometroBase = A3;
const int pinPotenciometroBrazoIzq = A2;
const int pinPotenciometroBrazoDer = A1;
const int pinPotenciometroGarra = A4;

const int pinBotonSiguiente = 4;
const int pinBotonAnterior = 2;
const int pinInterruptorModo = 7;

const int pinLedManual = 8;
const int pinLedAutomatico = 9;

int rutinaActual = 0;

//Modo automático con rutinas preestablecidas mediante pushbuttons
void modoAutomatico() {
  digitalWrite(pinLedAutomatico, HIGH);
  digitalWrite(pinLedManual, LOW);

  // Cambio de rutina con botones cíclica
  if (digitalRead(pinBotonSiguiente) == LOW) {
    rutinaActual = (rutinaActual + 1) % 5;
    delay(300);  
  }

  if (digitalRead(pinBotonAnterior) == LOW) {
    rutinaActual = (rutinaActual - 1 + 5) % 5;
    delay(300);  
  }

  // Ejecutar rutina según el número actual
  switch (rutinaActual) {
    case 0:
      servoBase.write(10);
      servoBrazoIzquierdo.write(30);
      servoBrazoDerecho.write(30);
      servoGarra.write(100);
      break;
    case 1:
      servoBase.write(50);
      servoBrazoIzquierdo.write(80);
      servoBrazoDerecho.write(80);
      servoGarra.write(120);
      break;
    case 2:
      servoBase.write(70);
      servoBrazoIzquierdo.write(100);
      servoBrazoDerecho.write(100);
      servoGarra.write(45);
      break;
    case 3:
      servoBase.write(30);
      servoBrazoIzquierdo.write(150);
      servoBrazoDerecho.write(150);
      servoGarra.write(180);
      break;
    case 4:
      servoBase.write(10);
      servoBrazoIzquierdo.write(75);
      servoBrazoDerecho.write(75);
      servoGarra.write(20);
      break;
  }
}

//modo manual mediante potenciómetros
void modoManual() {
  digitalWrite(pinLedAutomatico, LOW);
  digitalWrite(pinLedManual, HIGH);

//mapeo de la lectura de los potencióemtros. Constrain para que no se pasen de 180°
  int posBase = constrain(map(analogRead(pinPotenciometroBase), 0, 1023, 0, 180), 0, 180);
  int posIzq = constrain(map(analogRead(pinPotenciometroBrazoIzq), 0, 1023, 0, 180), 0, 180);
  int posDer = constrain(map(analogRead(pinPotenciometroBrazoDer), 0, 1023, 0, 180), 0, 180);
  int posGarra = constrain(map(analogRead(pinPotenciometroGarra), 0, 1023, 0, 180), 0, 180);

//Cambio de los servos a la posición establecida por el potenciómetro
  servoBase.write(posBase);
  servoBrazoIzquierdo.write(posIzq);
  servoBrazoDerecho.write(posDer);
  servoGarra.write(posGarra);
}

//Impresión del estado en el monitor serial
void imprimirEstado() {
  static unsigned long ultimoTiempoImpresion = 0;
  const unsigned long intervaloImpresion = 2500; //impresión cada 2.5 segundos para que se vea más refinado.

  if (millis() - ultimoTiempoImpresion >= intervaloImpresion) {
    Serial.println("\n=== ESTADO ACTUAL ===");
    Serial.print("Modo: ");
    Serial.println(digitalRead(pinInterruptorModo) ? "Automático" : "Manual");

    if (digitalRead(pinInterruptorModo)) {
      Serial.print("Rutina actual: ");
      Serial.println(rutinaActual + 1);
    }

    Serial.println("Posiciones servos:");
    Serial.print("Servo 1 (Base): ");
    Serial.print(servoBase.read());
    Serial.println("°");

    Serial.print("Servo 2 (Brazo Izq): ");
    Serial.print(servoBrazoIzquierdo.read());
    Serial.println("°");

    Serial.print("Servo 3 (Brazo Der): ");
    Serial.print(servoBrazoDerecho.read());
    Serial.println("°");

    Serial.print("Servo 4 (Garra): ");
    Serial.print(servoGarra.read());
    Serial.println("°");

    Serial.println("___________.w._____________");

    ultimoTiempoImpresion = millis();
  }
}

void setup() {
  Serial.begin(9600);

  servoBase.attach(11);
  servoBrazoIzquierdo.attach(10);
  servoBrazoDerecho.attach(5);
  servoGarra.attach(3);

  pinMode(pinBotonSiguiente, INPUT_PULLUP);
  pinMode(pinBotonAnterior, INPUT_PULLUP);
  pinMode(pinInterruptorModo, INPUT_PULLUP);

  pinMode(pinLedManual, OUTPUT);
  pinMode(pinLedAutomatico, OUTPUT);
}

void loop() {
  if (digitalRead(pinInterruptorModo)) {
    modoAutomatico();
  } else {
    modoManual();
  }

  imprimirEstado();
  delay(10);
}

#include <Servo.h>

Servo servo1;

void setup() {
  servo1.attach(5);
}

void loop() {
  int lectura = analogRead(A0); // eje X
  int angulo = map(lectura, 0, 1023, 0, 180);
  servo1.write(angulo);
  delay(15);
}

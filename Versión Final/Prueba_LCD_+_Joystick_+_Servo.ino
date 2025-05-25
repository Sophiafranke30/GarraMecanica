#include <LiquidCrystal.h>
#include <Servo.h>

#define JOYSTICK_Y A0
#define SERVO_1 5

LiquidCrystal lcd(9, 10, 11, 12, 13, A4);
Servo servo1;

void setup()
{
  servo1.attach(SERVO_1);
  
  lcd.begin(20,4);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Prueba J+LCD");
}

void loop()
{
  int lectura = analogRead(JOYSTICK_Y);
  int angulo = map(lectura, 0, 1023, 0, 180);
  servo1.write(angulo);

  lcd.setCursor(0,2);  lcd.print("Angulo: ");
  lcd.print(formatAngle(angulo));
  delay(200);
}

String formatAngle(int angle)
{
  String texto = String(angle);
  while (txt.length() < 3) texto = "0" + texto;
  return texto + "\xDF";
}

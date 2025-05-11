#include <LiquidCrystal.h>
#include <Servo.h>

LiquidCrystal lcd(12,4,10,8,7,2);

Servo s1, s2, s3, s4;
int angle[4] ={90,90,90,90}; //*Esperar a que dulce termine la garra para establecer que estos son los ángulos iniciales de los servos.
const int jstick[4]={A0,A1,A2,A3};

void setup() {
  // put your setup code here, to run once:
lcd.begin(20,4);

s1.attach(9);
s2.attach(6);
s3.attach(5);
s4.attach(3);  
}

void loop() {
  // put your main code here, to run repeatedly:

}

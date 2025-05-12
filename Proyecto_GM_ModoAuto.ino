#include <LiquidCrystal.h>
#include <Servo.h>
#include <Bounce2.h>

LiquidCrystal lcd(12,4,10,8,7,2);

Servo servo1, servo2, servo3, servo4;
int angulos[4] ={90,90,90,90}; 
const int joystick[4]={A0,A1,A2,A4};

void Leerjoysticks();
void MoverServos();
void MostrarenLCD();

Bounce PBMode = Bounce();

const int PINMode = 11;
const int LEDMA = A3;
const int LEDMM = 13;

void setup() {
  // put your setup code here, to run once:
lcd.begin(20,4);
 pinMode(LEDMA, OUTPUT);
 pinMode(LEDMM, OUTPUT);
 pinMode(PINMode, INPUT);

servo1.attach(9);
servo2.attach(6);
servo3.attach(5);
servo4.attach(3);  
}

void loop() {}
  // put your main code here, to run repeatedly:
void LeerJoysticks(){
  for (int i=0; i<4; i++) {
    int lectura = analogRead(joystick[i]);
    if (lectura > 450 && lectura < 570) lectura =512; //512 tomado como el valor central del joystick 1024/2=512
    angulos[i] = map(lectura, 0, 1023, 0, 180);
  }
  }
void MoverServos() {
  servo1.write(angulos[0]);
  servo2.write(angulos[1]);
  servo3.write(angulos[2]);
  servo4.write(angulos[3]);
}
void MostrarenLCD() {
  lcd.setCursor(0,0) ; lcd.print("Servo 1: "); lcd.print(angulos[0]);
  lcd.setCursor(0,1) ; lcd.print("Servo 2: "); lcd.print(angulos[1]);
  lcd.setCursor(0,2) ; lcd.print("Servo 3: "); lcd.print(angulos[2]);
  lcd.setCursor(0,3) ; lcd.print("Servo 4: "); lcd.print(angulos[3]);
}

void ModoLED(bool manual){
  digitalWrite(LEDMM, manual ? HIGH:LOW); //OPeración ternario equivalente a if else if
  digitalWrite(LEDMA, manual ? LOW:HIGH);
}

#include <LiquidCrystal.h>
#include <Servo.h>
#include <Bounce2.h>

LiquidCrystal lcd(12,4,10,8,7,2);

Servo servo1, servo2, servo3, servo4;
int angulo={90,90,90,90};

const int PINNext = A5;
const int PINBefore = A4;
const int PINMode = 11;
const int LEDMA = 13;
const int LEDMM = A7;
bool modoManual = false;

Bounce PBNext = Bounce();
Bounce PBBefore = Bounce();
Bounce PBMode = Bounce();

const int configuraciones = 5;
int rutina[configuraciones][4] = {
{90,90,90,90}, {45,90,135,90},{90,45,90,180},{135,135,45,45},{180,90,90,45}
}

int ConfigActual = 0;

void ModoLED(bool manual);
void MoverServos();
void MostrarenLCD();
void NextConfig();
void PrevConfig();
void LoadConfig();

void setup() {
  // put your setup code here, to run once:
  lcd.begin(20,4);
  
  servo1.attach(9);
  servo2.attach(6);
  servo3.attach(5);
  servo4.attach(3);
  
  pinMode(LEDMA, OUTPUT);
  pinMode(LEDMM, OUTPUT);
  pinMode(PINNext, INPUT);
  pinMode(PINBefore, INPUT);
  pinMode(PINNext, INPUT);

  PBNext.attach(PINNext);
  PBNext.interval(25);
  PBBefore.attach(PINBefore);
  PBBefore.interval(25);
  PBMode.attach(PINMode);
  PBMode.interval(25);

  ModoLED(modoManual);
  MoverServos();
  MostrarenLCD();

}

void loop() {
  PBNext.update();
  PBBefore.update();
  PBMode.update();

  int evento = -1;
  if(PBMode.fell()) evento =0);
    else if (PBNext.fell()) evento = 1;
    else if (PBBefore.fell()) evento =2;

  switch (evento){
    case 0:
      modoManual = !modoManual;
      ModoLED(modomanual);
      break;
    case 1:
      if(modoManual){
        NextConfig();
        MoverServos();
        MostrarenLCD();
      }
      break;
    case 2:
     if(modoManual){
        BeforeConfig();
        MoverServos();
        MostrarenLCD();
     }
      break;
    delay (70);

    
}

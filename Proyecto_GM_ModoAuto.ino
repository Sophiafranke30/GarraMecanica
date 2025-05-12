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
const int LEDMM = A3;
bool modoManual = false;

Bounce PBNext = Bounce();
Bounce PBBefore = Bounce();
Bounce PBMode = Bounce();

const int configuraciones = 5;
int rutina[configuraciones][4] = {
{90,90,90,90}, 
{45,90,135,90},
{90,45,90,180},
{135,135,45,45},
{180,90,90,45}
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

 if (PBMode.fell()){
    modoManual = !modoManual;
    ModoLEC(modoManual);
 }
if (modoManual){
    if (PBNext,fell()){
      NextConfig();
      MoverServos();
      MostrarenLCD();
      }
    if (PBBefore.fell()){
      PrevConfig();
      MoverServos();
      MostrarenLCD();
      }
}
    
delay(75);

void LoadConfig(){
  for (int i=0; int < 4; i++){
  angulo[i] = rutina[ConfigActual][i];
  } }

void NextConfig() {
  ConfigActual=(ConfigActual + 1) % configuraciones;
  LoadConfig();
}

void PrevConfig(){
  ConfigActual=(ConfigActual - 1 + configuraciones) % configuraciones;
  LoadConfig();
} 
void MoverServos() {
  servo1.write(angulo[0]);
  servo2.write(angulo[1]);
  servo3.write(angulo[2]);
  servo4.write(angulo[3]);
}
void MostrarenLCD() {
  lcd.setCursor(0,0) ; lcd.print("Servo 1: "); lcd.print(angulo[0]);
  lcd.setCursor(0,1) ; lcd.print("Servo 2: "); lcd.print(angulo[1]);
  lcd.setCursor(0,2) ; lcd.print("Servo 3: "); lcd.print(angulo[2]);
  lcd.setCursor(0,3) ; lcd.print("Servo 4: "); lcd.print(angulo[3]);
}

void ModoLED(bool manual){
  digitalWrite(LEDMM, manual ? HIGH:LOW); //OPeración ternario equivalente a if else if
  digitalWrite(LEDMA, manual ? LOW:HIGH);
}


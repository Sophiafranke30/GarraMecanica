#include <LiquidCrystal.h>
#include <Servo.h>
#include <Bounce2.h>

LiquidCrystal lcd(12,4,10,8,7,2);

Servo servo1, servo2, servo3, servo4;
int angulos[4]={90,90,90,90};

const int PINNext = A5;
const int PINBefore = A4;
const int PINMode = 11;
const int LEDMA = A3;
const int LEDMM = 13;
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
};

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
  pinMode(PINMode, INPUT);

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
    ModoLED(modoManual);
 }
if (modoManual){
    if (PBNext.fell()){
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
delay(50);
}
    
void NextConfig() {
  ConfigActual=(ConfigActual + 1) % configuraciones;
  LoadConfig();
}

void PrevConfig(){
  ConfigActual=(ConfigActual - 1 + configuraciones) % configuraciones;
  LoadConfig();
} 

void LoadConfig(){
  for (int i=0; i < 4; i++){
  angulos[i] = rutina[ConfigActual][i];
  } }

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


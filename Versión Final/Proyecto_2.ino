//Sophia Franke 23030
//Dulce Ovando 23441
//PROYECTO 2 | Electrónica Digital I
#include <Servo.h>
#include <LiquidCrystal.h>

// Prototipado de funciones
void manualControl(); //Control manual con joysticks
void automatico();  //Control automático con rutina
void moverServos();  //Envía posiciones a los servos
void updateLCD();  // Actualiza información en pantalla LCD
void leerModo();  // Lee si el modo es manual o automático
String formatAngle(int angle);  // Da formato al ángulo (con ° y ceros a la izquierda)

Servo servo1, servo2, servo3, servo4;  
LiquidCrystal lcd(9, 10, 11, 12, 13, A4); // LCD: RS, E, D4, D5, D6, D7

// Definición de entradas joysticks
#define JSTK_1_X A0  // Servo1: Base
#define JSTK_1_Y A1  // Servo4: Pinza (limitada)
#define JSTK_2_X A2  // Servo2: Derecho
#define JSTK_2_Y A3  // Servo3: Izquierdo

// Definición de botones y switch de modo
#define BTN_SIG 2
#define BTN_ANT 7
#define SWITCH_MODE 8


int rutina[5][4] = {
  { 0, 45, 45, 90 },
  { 45, 90, 90, 60 },
  { 90, 0, 0, 75 },
  { 135, 120, 120, 45 },
  { 180, 45, 45, 80 }
};

int pos1 = 90, pos2 = 90, pos3 = 90, pos4 = 90;
int pasoActual = 0;
bool modoManual = true;

unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 200;

void setup() {
  servo1.attach(5);  // base
  servo2.attach(6);  // derecho
  servo3.attach(3);  // izquierdo
  servo4.attach(4);  // pinza

  pinMode(BTN_SIG, INPUT_PULLUP);
  pinMode(BTN_ANT, INPUT_PULLUP);
  pinMode(SWITCH_MODE, INPUT);

  lcd.begin(20, 4);
  lcd.clear();

  leerModo();
  moverServos();
  updateLCD();
}

void loop() {
  leerModo();
  if (modoManual) {
    manualControl();
  } else {
    automatico(); 
  }
  moverServos();
  updateLCD();
}

//Funciones Utilizadas
void leerModo() {
  int lectura = digitalRead(SWITCH_MODE);
  modoManual = (lectura == LOW);  // LOW = Manual
}

void manualControl() {
  static int t1 = 90, t2 = 90, t3 = 90, t4 = 90;

  int pos1Read = map(analogRead(JSTK_1_X), 0, 1023, 0, 180);
  int pos4Read = map(analogRead(JSTK_1_Y), 0, 1023, 45, 90);
  pos4Read = constrain(pos4Read, 45, 90);
  int pos2Read = map(analogRead(JSTK_2_X), 0, 1023, 0, 180);
  int pos3Read = map(analogRead(JSTK_2_Y), 0, 1023, 0, 180);

  if (t1 < pos1Read) t1++;
  else if (t1 > pos1Read) t1--;
  if (t2 < pos2Read) t2++;
  else if (t2 > pos2Read) t2--;
  if (t3 < pos3Read) t3++;
  else if (t3 > pos3Read) t3--;
  if (t4 < pos4Read) t4++;
  else if (t4 > pos4Read) t4--;

  pos1 = t1;
  pos2 = t2;
  pos3 = t3;
  pos4 = t4;
}

void automatico() {
  static int t1 = 90, t2 = 90, t3 = 90, t4 = 90;

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (digitalRead(BTN_SIG) == LOW) {
      pasoActual = (pasoActual + 1) % 5;
      lastDebounceTime = millis();
    }
    if (digitalRead(BTN_ANT) == LOW) {
      pasoActual = (pasoActual - 1 + 5) % 5;
      lastDebounceTime = millis();
    }
  }

  int pos1Read = rutina[pasoActual][0];
  int pos2Read = rutina[pasoActual][1];
  int pos3Read = rutina[pasoActual][2];
  int pos4Read = constrain(rutina[pasoActual][3], 45, 90);

  if (t1 < pos1Read) t1++;
  else if (t1 > pos1Read) t1--;
  if (t2 < pos2Read) t2++;
  else if (t2 > pos2Read) t2--;
  if (t3 < pos3Read) t3++;
  else if (t3 > pos3Read) t3--;
  if (t4 < pos4Read) t4++;
  else if (t4 > pos4Read) t4--;

  pos1 = t1;
  pos2 = t2;
  pos3 = t3;
  pos4 = t4;
}

void moverServos() {
  servo1.write(pos1);
  servo2.write(pos2);
  servo3.write(pos3);
  servo4.write(pos4);
}

String formatAngle(int angle) {
  String txt = String(angle);
  while (txt.length() < 3) txt = "0" + txt;
  return txt + "\xDF";  // ° símbolo
}

void updateLCD() {
  static int lastPos1 = -1, lastPos2 = -1, lastPos3 = -1, lastPos4 = -1;
  static bool lastModoManual = !modoManual;
  static int lastPaso = -1;

  if (pos1 != lastPos1 || pos2 != lastPos2 || pos3 != lastPos3 || pos4 != lastPos4 || modoManual != lastModoManual || (!modoManual && pasoActual != lastPaso)) {
    lcd.setCursor(0, 0);
    lcd.print("Modo: ");
    lcd.print(modoManual ? "M" : "A");
    lcd.print("        ");

    lcd.setCursor(0, 1);
    lcd.print("L:"); lcd.print(formatAngle(pos3));
    lcd.print(" R:"); lcd.print(formatAngle(pos2));
    lcd.print("     ");

    lcd.setCursor(0, 2);
    lcd.print("B:"); lcd.print(formatAngle(pos1));
    lcd.print(" G:"); lcd.print(formatAngle(pos4));
    lcd.print("     ");

    lcd.setCursor(0, 3);
    if (!modoManual) {
      lcd.print("Rutina actual: ");
      lcd.print(pasoActual + 1);
      lcd.print("   ");
    } else {
      lcd.print("Joystick activo     ");
    }

    // guarda las últimas lecturas.
    lastPos1 = pos1;
    lastPos2 = pos2;
    lastPos3 = pos3;
    lastPos4 = pos4;
    lastModoManual = modoManual;
    lastPaso = pasoActual;
  }
}

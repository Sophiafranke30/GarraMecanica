//Sophia Franke 23030
//Dulce Ovando 23441
//Proyecto 2 Electrónica Digital 1
//Pegado de WOKWI, Versión final del código
#include <LiquidCrystal.h> 
#include <Servo.h>
#include <Bounce2.h>

LiquidCrystal lcd(12,4,10,8,7,2);

Servo servo1, servo2, servo3, servo4; //declar los que se utilizarán.ración de los se
int angulos[4]={90,90,90,90}; //ángulos iniciales de los servos (corroborar con máquina)

int angulosPrevios[4]={-1,-1,-1,-1};
int configAnterior= -1;
bool modoManual =false;
bool modoManualPrevio= !modoManual; //guarda el estado previo en el modo manual o mecánico

//declaración de los pines que tienen a los joysticks, botones y LEDs
const int joystick[4]={A2,A3,A0,A1};

const int PINNext = A5;
const int PINBefore = 13;
const int PINMode = 11;
const int LEDMA = 0;
const int LEDMM = 13;

//Configuración de los botones para prevenir rebotes.
Bounce PBNext = Bounce();
Bounce PBBefore = Bounce();
Bounce PBMode = Bounce();

//declaración de las 5 configuraciones del modo automático
const int configuraciones = 5;
int rutina[configuraciones][4] = {
{90,90,90,90}, 
{45,90,135,90},
{90,45,90,180},
{135,135,45,45},
{180,90,90,45}
};

int ConfigActual = 0;

//Prototipeado de las funciones
void ModoLED(bool manual);
void MoverServos();
void MostrarenLCD();
void NextConfig();
void PrevConfig();
void LoadConfig();
void Leerjoysticks();
String formatAngle(int angle); //formateo de los ángulos para asegurar que se muestren los necesarios y 90° no se vuelva 900° si se usó esa línea para 180°.

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

  //configurar los botones para evitar el rebote
  PBNext.attach(PINNext);//asigna el pin designado para ir a la siguiente configuración a PBNext, que es de la librería Bounce2, y se encarga de manejar el el rebote de este pin.
  PBNext.interval(25);  // El interval ayuda a decirle a Arduino que ignore cualquier cambio dentro de los 25 milisegundos después de que se haya presionado el botón.
  PBBefore.attach(PINBefore); PBBefore.interval(25);
  PBMode.attach(PINMode); PBMode.interval(25);

  modoManual = !digitalRead(PINMode); //lee el estado en el que se encuentra el switch
  ModoLED(modoManual); //activa el LED correspondiente al estado

  //llama las funciones siguientes para cargar la configuración actual, mover los servos correspondientes y mostrar en el LCD lo que se le pida.
  LoadConfig(); 
  MoverServos();
  MostrarenLCD();

}

void loop() {
  //verifican si el botón asociado cambió de estado, aplica el tiempo de espera establecido en el .interval y sirve para que funcione el .fell().
  PBNext.update();
  PBBefore.update();
  PBMode.update();

  bool nuevoModoManual = !digitalRead(PINMode); //detecta si se cambió de modo en el switch
  if (nuevoModoManual != modoManual);{
    modoManual = nuevoModoManual;
    ModoLED(modoManual);
    if (!modoManual){
      LoadConfig();
      MoverServos();
      MostrarenLCD();
    }
    delay(200);
  }
  if (modoManual){ //si esta en modo manual o mecánico lee los joysticks 
    LeerJoysticks();
    MoverServos();
    MostrarenLCD(); 
  } else{
    if (PBNext.fell()){ //detecta si hubo cambio de HIGH a LOW (literalmente) y solo efectúa cambio si el botón NO se mantiene presionado
      NextConfig(); //cambia a la siguiente configuración pr4edeterminada
      MoverServos();
      MostrarenLCD();
      }
    if (PBBefore.fell()){
      PrevConfig(); //cambia a la configuración predetermianda anterior
      MoverServos();
      MostrarenLCD();
      }
  }
  delay(50);
}
//Función para lectura de joysticks y actualización de Servos si se encuentra en modo Manual
void LeerJoysticks(){
  for (int i=0; i<4; i++) {
    int lectura = analogRead(joystick[i]);
    if (lectura > 480 && lectura < 544) continue; //zona donde se establece el "0" del joystick-

    if(lectura <= 480){ //Movimeintos a la izquerda y abajo del joystick disminuyen.
      angulos[i]--;
      if (angulos[i] < 0) angulos[i] = 0; //asegura que no hayan ángulos negativos ya que son servos de 180°
    } else if (lectura >= 544){ //Movimeintos a la derecha y arriba del joystick aumentan.
      angulos[i]++;
      if (angulos[i] > 180) angulos[i] = 180; //asegura que no hayan ángulos mayores a 180°
    }
  }
}  

//Funciones para cambiar de configuración predeterminada
void NextConfig() {
  ConfigActual=(ConfigActual + 1) % configuraciones; //% se utiliza para crear el bucle de las configuraciones predeterminadas y asegurar que vaya 1-2-3-4-5-1...
  LoadConfig();
}

void PrevConfig(){
  ConfigActual=(ConfigActual - 1 + configuraciones) % configuraciones; // se le suman las configuraciones para asegurar que de 0 no vaya a -1, sino que regrese a 5 ya que esta es la última configuración.
  LoadConfig();
} 
//Carga la configuración actual de los servos.

void LoadConfig(){
  for (int i=0; i < 4; i++){ //array de 
  angulos[i] = rutina[ConfigActual][i];
  } }

//Mueve los servos a los ángulos establecidos en el array de ángulos.
void MoverServos() {
  servo1.write(angulos[0]);
  servo2.write(angulos[1]);
  servo3.write(angulos[2]);
  servo4.write(angulos[3]);
}
void MostrarenLCDModoManual() {
  //Imprime los 4 Servos con sus ángulos.
  lcd.setCursor(0,0) ; lcd.print("Servo 1: "); lcd.print(formatAngle(angulos[0]));
  lcd.setCursor(0,1) ; lcd.print("Servo 2: "); lcd.print(formatAngle(angulos[1]));
  lcd.setCursor(0,2) ; lcd.print("Servo 3: "); lcd.print(formatAngle(angulos[2]));
  lcd.setCursor(0,3) ; lcd.print("Servo 4: "); lcd.print(formatAngle(angulos[3]));
  lcd.setCursor(13,0); lcd.print("MODO: "); lcd.print("M");
  lcd.setCursor(13, 2); lcd.print("       ");
  lcd.setCursor(16, 3); lcd.print("  ");
  //Imprime el modo que se encuentra actualmente y imprime espacios en blanco donde se encuentra texto en el otro modo.
}

void MostrarenLCDModoAutomatico(){
  lcd.setCursor(0,0) ; lcd.print("Servo 1: "); lcd.print(formatAngle(angulos[0]));
  lcd.setCursor(0,1) ; lcd.print("Servo 2: "); lcd.print(formatAngle(angulos[1]));
  lcd.setCursor(0,2) ; lcd.print("Servo 3: "); lcd.print(formatAngle(angulos[2]));
  lcd.setCursor(0,3) ; lcd.print("Servo 4: "); lcd.print(formatAngle(angulos[3]));
  lcd.setCursor(13,0); lcd.print("MODO: "); lcd.print("A");
  lcd.setCursor(13, 2); lcd.print("RUTINA: "); //imprime la rutina predetermianda actual en la que se encuentra el Servo.
  lcd.setCursor(16, 3); 
  if (ConfigActual < 10) { //Imrpime un cero adelante del número para que siempre hayan dos dígitos
    lcd.print("0" + String(ConfigActual));
  } else { 
    lcd.print(String(ConfigActual)); }
}

void MostrarenLCD(){
if (modoManual){
  MostrarenLCDModoManual();} 
else { 
  MostrarenLCDModoAutomatico(); }
}

//Formaton del ángulo para mostrarlo como 3 dígitos
String formatAngle(int angle) {
if (angle < 10) return "00" + String(angle); // para npumeros menores a 10 los formatea como, por ejemplo, "005".
else if (angle < 100) return "0" + String(angle); //para números menorea a 100 los formatea como, por ejemplo, "075" 
else return String(angle); //para números mayores a 100 los formatea como, por ejemplo, "145"
}

//Cambia los LEDS según el modo en el que se encuentre
void ModoLED(bool manual){
  digitalWrite(LEDMM, manual ? HIGH:LOW); //OPeración ternario equivalente a if else if
  digitalWrite(LEDMA, manual ? LOW:HIGH);
}

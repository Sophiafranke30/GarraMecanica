#include <LiquidCrystal.h>
LiquidCrystal lcd(9, 10, 11, 12, 13, A4);

void setup()
{
  lcd.begin(20,4);
  lcd.clear();
  lcd.setCursor(0,0);  lcd.print("Linea 1");
  lcd.setCursor(0,1);  lcd.print("Linea 2");
  lcd.setCursor(0,2);  lcd.print("Linea 3");
  lcd.setCursor(0,3);  lcd.print("Linea 4");
}

void loop(){}



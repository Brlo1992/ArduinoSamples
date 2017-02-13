#include <Wire.h>   // standardowa biblioteka Arduino
#include <LiquidCrystal_I2C.h> // dolaczenie pobranej biblioteki I2C dla LCD

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Ustawienie adresu ukladu na 0x27
const int pompa = 8;
bool state = false;

 
void setup() {
  Serial.begin(9600);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(8, OUTPUT);
  
  lcd.begin(16,2);   // Inicjalizacja LCD 2x16
  lcd.backlight(); // zalaczenie podwietlenia 
  lcd.setCursor(0,0); // Ustawienie kursora w pozycji 0,0 (pierwszy wiersz, pierwsza kolumna)
  lcd.print("Hello, world!");
  delay(500);
  lcd.setCursor(0,1); //Ustawienie kursora w pozycji 0,0 (drugi wiersz, pierwsza kolumna)
  lcd.print("BOTLAND.com.pl");

}

void loop() {
  
  int on = digitalRead(2);
  int off = digitalRead(3);
  
  Serial.println(on);
  Serial.println(off);
  
  Serial.print(F("Wejscie cyfrowe 5 ma wartosc: "));
  
  if(off == 1) 
  {
    state = false;
  }
  if(on == 1)
  {
    state = true;
  }
  if(state == false)
  {
        Serial.println(F("LOW"));
        digitalWrite(pompa, LOW);
  }
  if(state == true)
  {
        Serial.println(F("HIGH"));
        digitalWrite(pompa, HIGH);
  }
  lcd.backlight(); // zalaczenie podswietlenia
   delay(5000);
  lcd.noBacklight(); // wylaczenie podswietlenia
   delay(5000);


}

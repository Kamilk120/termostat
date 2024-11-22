#include <max6675.h> // max6675.h file is part of the library that you should download from Robojax.com
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

int soPin = 12;// SO=Serial Out
int csPin = 10;// CS = chip select CS pin
int sckPin = 13;// SCK = Serial Clock pin
//enkoder piny
int CLKen = 3;
int DTen = 4;
int SWen = 2;
// przechowywanie stanów
int lastCLKState;
int encoderValue = 0;

// Stan przycisku
int buttonState;
int lastButtonState = HIGH;
// częstotliwość
unsigned long fLCD = 1000;
unsigned long fEN = 10;
//czas
unsigned long aktualnyCzas = 0;
unsigned long zapamietanyCzasLCD = 0;
unsigned long zapamietanyCzasENC = 0;

float temp; //zmienna do sredniej
MAX6675 robojax(sckPin, csPin, soPin);// create instance object of MAX6675
LiquidCrystal_I2C lcd(0x27,16,2); // create instance lcd

void temp_avr(); // function to read temperature wutch avr

void setup() {
  //inicjalizacja pinow
  pinMode(CLKen, INPUT);
  pinMode(DTen, INPUT);
  pinMode(SWen, INPUT_PULLUP);
  lastCLKState = digitalRead(CLKen);

  lcd.init();
  Serial.begin(9600);// initialize serial monitor with 9600 baud 
}

void loop() {
  //aktualnyCzas = millis(); //czas
  // basic readout test, just print the current temp
  // // Robojax.com MAX6675 Temperature reading on Serial monitor
  // if (aktualnyCzas - zapamietanyCzasLCD >= fLCD){
  //   zapamietanyCzasLCD = aktualnyCzas;
    temp_avr();
     Serial.print("C = "); 
     Serial.print(robojax.readCelsius());
    // Serial.print(" F = ");
    // Serial.println(robojax.readFahrenheit());
    // Print a message to the LCD.
    lcd.backlight();
    lcd.setCursor(3,0);
    lcd.print("C = ");
    lcd.print(temp);
  //}
  //enkoder
  // if (aktualnyCzas - zapamietanyCzasENC >= fEN){
  //   zapamietanyCzasENC = aktualnyCzas;

  //   int CLKState = digitalRead(CLKen);
  //   int DTState = digitalRead(DTen);

  //   // Sprawdzenie, czy nastąpiła zmiana stanu na CLK
  //   if (CLKState != lastCLKState){
  //     // Jeśli stan DT jest inny niż stan CLK, to kierunek jest CW
  //     if (DTState != CLKState) {
  //       encoderValue++;
  //     } else {
  //       encoderValue--;
  //     }
  //     Serial.print("Wartość enkodera: ");
  //     Serial.println(encoderValue);
  //   }

  //   lastCLKState = CLKState;

  //   // Sprawdzenie przycisku
  //   int readButton = digitalRead(SWen);
  //   if (readButton != lastButtonState) {
  //     if (readButton == LOW) {
  //       Serial.println("Przycisk naciśnięty!");
  //     }
  //     lastButtonState = readButton;
  //   }
  // }      
  delay(1000);
}
void temp_avr(){
    temp = 0;
    for(int i = 0; i < 10; i++){
        temp += robojax.readCelsius();
        delay(100);
      }
    temp /=10 ;
  }
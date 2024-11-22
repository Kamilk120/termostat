#include <Encoder.h>
#include <max6675.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Arduino.h>

//enkoder piny
int const CLKen = 6;
int const DTen = 5;
int const SWen = 4;

//thermopar pin
int const soPin = 12;// SO=Serial Out
int const csPin = 10;// CS = chip select CS pin
int const sckPin = 13;// SCK = Serial Clock pin

//lcd scale
int const rowLCD = 2;
int const collumnLCD = 16;

//actual time
unsigned long time_now = millis();

//remember time max6675
unsigned long remember_time_max6675 = 0;
unsigned long frecfency_max6675 = 1000;

Encoder myEnc(DTen, CLKen);
MAX6675 robojax(sckPin, csPin, soPin);
LiquidCrystal_I2C lcd(0x27,collumnLCD,rowLCD);

void setup() {
    lcd.init();
    lcd.backlight();
    Serial.begin(9600);
    Serial.println("Basic Encoder Test:");

}

long oldPosition  = -999;

void loop() {
    if(time_now - remember_time_max6675 >= frecfency_max6675){
        remember_time_max6675 = time_now;
        lcd.setCursor(3,0);
        lcd.print("C = ");
        lcd.print(robojax.readCelsius());
    }
    long newPosition = myEnc.read();
    if (newPosition != oldPosition) {
        oldPosition = newPosition;
        Serial.println(newPosition);
        lcd.setCursor(3,1);
        lcd.print("max = ");
        lcd.print(newPosition);
    }
    time_now = millis();
    Serial.print(time_now);
}
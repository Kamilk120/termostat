#include <Encoder.h>
#include <max6675.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Arduino.h>

//enkoder piny
int const CLKen = 3;
int const DTen = 2;
int const SWen = 4;

//thermopar pin
int const soPin = 12;// SO=Serial Out
int const csPin = 10;// CS = chip select CS pin
int const sckPin = 13;// SCK = Serial Clock pin

//relay pin
int const SPin = 6;

//lcd scale
int const rowLCD = 2;
int const collumnLCD = 16;

//actual time
unsigned long time_now = millis();

//remember time max6675
unsigned long remember_time_max6675 = 0;
unsigned long frecfency_max6675 = 1000;

//remember time max6675
unsigned long remember_time_relay = 0;
unsigned long delay_time = 5000;

//remember time display_off
unsigned long remember_time_displayoff = 0;
unsigned long display_turn_on_time = 10000;
unsigned long count_screen_off = 0;

Encoder myEnc(DTen, CLKen);
MAX6675 robojax(sckPin, csPin, soPin);
LiquidCrystal_I2C lcd(0x27,collumnLCD,rowLCD);



void menu_default(); //funcion for set temperature
void relay_switching();// switching heat
void temperature(); // read temperature
void screen_saver();// screen saver

void setup() {
    lcd.init();
    lcd.backlight();
    Serial.begin(9600);
    pinMode(SPin, OUTPUT); 
    
    Serial.println("Basic Encoder Test:");
}

long oldPosition  = -999;
long newPosition = myEnc.read();
long read_temperature;

void loop() {
    temperature();
    menu_default();
    relay_switching();
    time_now = millis();
    //Serial.print(robojax.readCelsius());
    }

void temperature(){
    if(time_now - remember_time_max6675 >= frecfency_max6675){
        remember_time_max6675 = time_now;
        read_temperature = robojax.readCelsius();
        lcd.setCursor(3,0);
        lcd.print("C = ");
        lcd.print(read_temperature);
    }
}

void menu_default(){
    newPosition = myEnc.read();
    if (newPosition != oldPosition) {
        oldPosition = newPosition;
        Serial.println(newPosition);
        lcd.setCursor(3,1);
        lcd.print("max = ");
        lcd.setCursor(9,1);
        lcd.print("      ");
        lcd.setCursor(9,1);
        lcd.print(newPosition);
    } 
}

void relay_switching(){
    if(time_now - remember_time_relay >= delay_time){
        remember_time_relay = time_now;
        if(read_temperature <= newPosition){
            digitalWrite(SPin, HIGH);
        }else{
            digitalWrite(SPin, LOW);
        }
    }
}

// void screen_saver(){
//     if(count_screen_off >= 1000){
//         lcd.noDisplay();

//     }else{
        
//         count_screen_off++;
//     }

// }
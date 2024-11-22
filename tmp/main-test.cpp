#include <max6675.h> // max6675.h file is part of the library that you should download from Robojax.com
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <string.h>
#include <Arduino.h>

int counter=0;
String dir="";
unsigned long last_run=0;

void shaft_moved();

void setup() {
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(3), shaft_moved, FALLING);
  pinMode(4,INPUT);
}

void shaft_moved(){
  if (millis()-last_run>5){
    if (digitalRead(4)==1){
      counter++;
      dir="CW";
      }
    if (digitalRead(4)==0){
      counter--; 
      dir="CCW";}
    last_run=millis();
  }
}

void loop() {
  Serial.print("counter : ");
  Serial.print(counter);
  Serial.print(" direction : ");
  Serial.println(dir);  
}
#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

int lcdColumns = 16;
int lcdRows = 2;
float voltage = 0;
float current = 0;
unsigned long previousMillis = 0, currentMillis = 0;
int current_ADC = 0;
int voltage_ADC = 0;
bool show_ADC = true;

LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);  

void LCDInitialization(){
    Wire.begin();
    lcd.init();                  
    lcd.backlight();
}

void displayLCD(
    float current, 
    float voltage, 
    int update, 
    bool show_ADC,
    int current_ADC, 
    int voltage_ADC
  ){
  currentMillis = millis();
  if (currentMillis - previousMillis >= update) {
      lcd.clear();
      previousMillis = currentMillis;
      lcd.setCursor(0, 0);
      lcd.print(String(voltage, 2) + " V");
      lcd.setCursor(0, 1);
      lcd.print(String(current, 2) + " A");
      lcd.setCursor(10, 0);
      lcd.print(String(voltage_ADC));
      lcd.setCursor(10, 1);
      lcd.print(String(current_ADC));
  }
}




void scanAddress(){
    byte error, address;
  int nDevices;
  Serial.println("Scanning...");
  nDevices = 0;
  for(address = 1; address < 127; address++ ) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    if (error == 0) {
      Serial.print("I2C device found at address 0x");
      if (address<16) {
        Serial.print("0");
      }
      Serial.println(address,HEX);
      nDevices++;
    }
    else if (error==4) {
      Serial.print("Unknow error at address 0x");
      if (address<16) {
        Serial.print("0");
      }
      Serial.println(address,HEX);
    }    
  }
  if (nDevices == 0) {
    Serial.println("No I2C devices found\n");
  }
  else {
    Serial.println("done\n");
  }
  delay(5000);   
}
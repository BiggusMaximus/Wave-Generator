#include <Arduino.h>
#include "lcd.h"
#include "voltage.h"
#include "current.h"


const long update_interval = 1000; 

void setup() {
  Serial.begin(115200);
  LCDInitialization();
  voltageSensorInitialization();
  currentSensorInitialization();
  // startCalibrationVoltage();
}

void loop() {
  // current = read_current();
  current = readCalibrationMeanCurrent(1000.00);
  current_ADC = read_avg_current_ADC(1000.00);
  voltage_ADC = read_voltage_ADC();
 
  displayLCD(current, voltage, update_interval, true, current_ADC, voltage_ADC);

  
}


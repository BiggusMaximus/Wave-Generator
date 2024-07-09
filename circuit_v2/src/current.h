#include <Arduino.h>
#define CURRENT_PIN 25

float R1 = 6800.0;
float R2 = 12000.0;

// Calibration constant value
float slope = 0.011;
float intercept = -31.475;

void currentSensorInitialization(){
    pinMode(CURRENT_PIN, INPUT);
}

float read_current(){
    int adc = analogRead(CURRENT_PIN);
    float adc_voltage = adc * (3.3 / 4096.0);
    float current_voltage = (adc_voltage * (R1+R2)/R2);
    float current = (current_voltage - 2.5) / 0.100;
    return current;
}

float readCalibratedCurrent(){
   return slope*analogRead(CURRENT_PIN) + intercept;
}

float readCalibrationMeanCurrent(float SAMPLES){
    float temp = 0;
    for (size_t i = 0; i < int(SAMPLES); i++)
    {
        temp += analogRead(CURRENT_PIN);
    }
    temp /= SAMPLES;
    temp = slope*temp + intercept;
    return temp;
}

int read_current_ADC(){
    return analogRead(CURRENT_PIN);
}

float read_avg_current_ADC(float SAMPLES){
    float temp = 0;
    for (size_t i = 0; i < int(SAMPLES); i++)
    {
        temp += analogRead(CURRENT_PIN);
    }
    temp /= SAMPLES;
    return temp;
}
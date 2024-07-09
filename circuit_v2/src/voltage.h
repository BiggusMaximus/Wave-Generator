#include <Arduino.h>
#include <ZMPT101B.h>

#define ACTUAL_VOLTAGE 209.0f 

#define START_VALUE 0.0f
#define STOP_VALUE 1000.0f
#define STEP_VALUE 0.25f
#define TOLLERANCE 1.0f

#define MAX_TOLLERANCE_VOLTAGE (ACTUAL_VOLTAGE + TOLLERANCE)
#define MIN_TOLLERANCE_VOLTAGE (ACTUAL_VOLTAGE - TOLLERANCE)
#define SENSITIVITY 215.75f
#define VOLTAGE_PIN 34

unsigned long count = 0;

ZMPT101B voltageSensor(VOLTAGE_PIN, 50.0);

bool INFO = true;


void voltageSensorInitialization() {
  voltageSensor.setSensitivity(SENSITIVITY);
}

void startCalibrationVoltage(){
    Serial.print("The Actual Voltage: ");
    Serial.println(ACTUAL_VOLTAGE);

    float senstivityValue = START_VALUE;
    voltageSensor.setSensitivity(senstivityValue);
    float voltageNow = voltageSensor.getRmsVoltage();

    Serial.println("Start calculate");

    while (voltageNow > MAX_TOLLERANCE_VOLTAGE || voltageNow < MIN_TOLLERANCE_VOLTAGE) {
        if (senstivityValue < STOP_VALUE) {
        senstivityValue += STEP_VALUE;
        voltageSensor.setSensitivity(senstivityValue);
        voltageNow = voltageSensor.getRmsVoltage();
        Serial.print(senstivityValue);
        Serial.print(" => ");
        Serial.println(voltageNow);
        } else {
        Serial.println("Unfortunately the sensitivity value cannot be determined");
        return;
        }
    }

    Serial.print("Closest voltage within tolerance: ");
    Serial.println(voltageNow);
    Serial.print("Sensitivity Value: ");
    Serial.println(senstivityValue, 10);
}

float readVoltage() {
  return voltageSensor.getRmsVoltage();
}

float read_mean_voltage(float SAMPLES, bool INFO){
    float mean_voltage = 0;
    for (size_t i = 0; i < SAMPLES; i++)
    {
        mean_voltage += voltageSensor.getRmsVoltage();
    }
    mean_voltage /= SAMPLES;

    if (INFO){
        Serial.println("Mean : " + String(mean_voltage) + " V" + " | N_SAMPLES : " + String(SAMPLES));
    }
    return mean_voltage;
}

int read_voltage_ADC(){
    return analogRead(VOLTAGE_PIN);
}

void read_ADC(){
    Serial.print("loop");
    Serial.println(count);

    Serial.print(">ADC:");
    Serial.println(analogRead(34));
    // wait 
    delay(50);
    count += 1;
}

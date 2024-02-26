#include <Arduino.h>
#include <pressureSensor/pressureSensor.h>
#include <configs.h>

PressureSensor PressureSensors[numPressureSensors];

void initPressureSensors()
{
    PressureSensors[0].setup(PRESS_SENSOR_1);
    PressureSensors[1].setup(PRESS_SENSOR_2);
    PressureSensors[2].setup(PRESS_SENSOR_3);
}



// ==================== PressureSensor Class ====================
PressureSensor::PressureSensor() {}

uint16_t PressureSensor::read()
{
    return analogRead(pin);
}

void PressureSensor::setup(int _pin)
{
    pin = _pin;
    pinMode(_pin, INPUT);
}

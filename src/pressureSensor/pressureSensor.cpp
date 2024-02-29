#include <Arduino.h>
#include <pressureSensor/pressureSensor.h>
#include <configs.h>

PressureSensor PressureSensors[numPressureSensors];

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

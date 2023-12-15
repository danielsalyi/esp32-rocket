#include <Arduino.h>
#include <sensors/pressureSensor/pressureSensor.h>

PressureSensor::PressureSensor(int pin)
{
    _pin = pin;
}

uint16_t PressureSensor::read()
{
    return analogRead(_pin);
}

void PressureSensor::begin()
{
    pinMode(_pin, INPUT);
}

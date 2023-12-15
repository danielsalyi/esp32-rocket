#include <Arduino.h>
#include <sensors/loadcell/loadcell.h>

LoadCell::LoadCell(int pin)
{
    _pin = pin;
}

uint16_t LoadCell::read()
{
    return analogRead(_pin);
}

void LoadCell::begin()
{
    pinMode(_pin, INPUT);
}

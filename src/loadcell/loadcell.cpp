#include <Arduino.h>
#include <loadcell/loadcell.h>

int _pin;

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

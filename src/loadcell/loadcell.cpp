#include <Arduino.h>
#include <loadcell/loadcell.h>

LoadCell loadCell;

LoadCell::LoadCell()
{
}

uint16_t LoadCell::read()
{
    return analogRead(pin);
}

void LoadCell::setup()
{
    // pinMode(pin, INPUT);
}

#ifndef LOADCELL_H
#define LOADCELL_H

#include <Arduino.h>

class LoadCell
{
private:
    int _pin;

public:
    LoadCell(int pin);

    void begin();
    uint16_t read();
};

#endif
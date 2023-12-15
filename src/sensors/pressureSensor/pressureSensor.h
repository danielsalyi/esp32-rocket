#ifndef PRESS_SENSOR_H
#define PRESS_SENSOR_H

#include <Arduino.h>

class PressureSensor
{
private:
    int _pin;

public:
    PressureSensor(int pin);

    void begin();
    uint16_t read();
};

#endif

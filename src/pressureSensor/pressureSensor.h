#ifndef PRESS_SENSOR_H
#define PRESS_SENSOR_H

#include <Arduino.h>

class PressureSensor; // Forward declaration
extern PressureSensor PressureSensors[3]; // Declare the array

void initPressureSensors();

class PressureSensor
{
private:
    int pin;

public:
    PressureSensor();
    void setup(int _pin);
    uint16_t read();
};

#endif

#ifndef PRESS_SENSOR_H
#define PRESS_SENSOR_H
#define numPressureSensors 3



class PressureSensor
{
private:
    int pin;

public:
    PressureSensor();
    void setup(int _pin);
    uint16_t read();
};

extern PressureSensor PressureSensors[3]; // Declare the array

#endif

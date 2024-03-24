#include "Arduino.h"
#include <ESP32Servo.h>
#include <configs.h>
#include <flowrate/flowrate.h>

FlowRate flowRate[5] = {FlowRate(), FlowRate(), FlowRate(), FlowRate(), FlowRate()};

FlowRate::FlowRate()
{
    servo = Servo();
}

void FlowRate::setup(int pinNum)
{
    pin = pinNum;
}

void FlowRate::set(int value)
{
    servo.write(value);
}

void FlowRate::attach()
{
    servo.attach(pin);
}

void FlowRate::detach()
{
    servo.detach();
}

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

void FlowRate::attach()
{
    servo.attach(pin);
}

void FlowRate::set(int value)
{
    servo.attach(pin);
    servo.write(value);
    vTaskDelay(500);
    servo.detach();
}

void FlowRate::set(int value, int speed)
{
    for (int i = servo.read(); i < value; i++)
    {
        this->set(i);
        vTaskDelay(speed / portTICK_PERIOD_MS);
    }
}

void FlowRate::detach()
{
    servo.detach();
}

int FlowRate::read()
{
    // min pulse 527 us
    // max is 2382 us

    // just custom map 527 -> 0, 2382 -> 270
    int useconds = servo.readMicroseconds();

    return -1;
}

void FlowRate::test()
{

    DEBUG("Flowrate: 0 to ON");
    flowRate[0].set(90);
    vTaskDelay(2000 / portTICK_PERIOD_MS);

    DEBUG("Flowrate: 1 to ON");
    flowRate[1].set(90);

    DEBUG("Flowrate: 2 to ON");
    flowRate[2].set(90);
    vTaskDelay(2000 / portTICK_PERIOD_MS);

    DEBUG("Flowrate: 3 to ON");
    flowRate[3].set(90);
    vTaskDelay(2000 / portTICK_PERIOD_MS);

    DEBUG("Flowrate: 4 to ON");
    flowRate[4].set(90);
    vTaskDelay(5000 / portTICK_PERIOD_MS);

    closeAll();
}

void FlowRate::closeAll()
{
    for (int i = 0; i < 5; i++)
    {
        flowRate[i].set(0);
    }
}
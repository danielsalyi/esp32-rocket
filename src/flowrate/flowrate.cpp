#include "Arduino.h"
#include <ESP32Servo.h>
#include <configs.h>
#include <flowrate/flowrate.h>

FlowRate flowRate[5] = {FlowRate(), FlowRate(), FlowRate(), FlowRate(), FlowRate()};

FlowRate::FlowRate() {
    servo = Servo();
}

void FlowRate::setup(int pinNum) {
    pin = pinNum;
}

void FlowRate::attach() {
    servo.attach(pin);
}

void FlowRate::set(int value) {
    servo.attach(pin);
    servo.write(value);
    vTaskDelay(500);
    servo.detach();
}

void FlowRate::set(int value, int speed) {
    for (int i = servo.read(); i < value; i++)
    {
        this->set(i);
        vTaskDelay(speed / portTICK_PERIOD_MS);
    }
}

void FlowRate::detach() {
    servo.detach();
}

int FlowRate::read() {
    // min pulse 527 us
    // max is 2382 us

    // just custom map 527 -> 0, 2382 -> 270
    int useconds = servo.readMicroseconds();


    return -1;
}

#include "Arduino.h"
#include <ESP32Servo.h>
#include <configs.h>
#include <flowrate/flowrate.h>

Servo servo;
FlowRate flowRate;

FlowRate::FlowRate() {
}

void FlowRate::setup() {
    servo.attach(SEVO_PIN);
}

void FlowRate::set(int value) {
    servo.write(value);
}

void FlowRate::set(int value, int speed) {
    for (int i = servo.read(); i < value; i++)
    {
        flowRate.set(i);
        vTaskDelay(speed / portTICK_PERIOD_MS);
    }
}

void FlowRate::set(int start, int end, int speed) {
    for (int i = start; i < end; i++)
    {
        flowRate.set(i);
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}

int FlowRate::read() {
    // min pulse 527 us
    // max is 2382 us

    // just custom map 527 -> 0, 2382 -> 270
    int useconds = servo.readMicroseconds();


    return -1;
}

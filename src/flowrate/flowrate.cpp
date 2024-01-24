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

int FlowRate::read() {
    return servo.read();
}

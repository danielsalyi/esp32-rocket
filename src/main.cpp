#include <Arduino.h>
#include <configs.h>
#include <led/led.h>
#include <webserver/webserver.h>
#include <flashWriter/flashWriter.h>
#include <pressureSensor/pressureSensor.h>
#include <flowrate/flowrate.h>
#include <loadcell/loadcell.h>

void setup()
{
    Serial0.begin(BAUD_RATE);
    DEBUG("====== ESP Setup ======");

    DEBUG("====== Pins Setup ======");
    pinMode(IGNITER_PIN, OUTPUT);
    pinMode(RELAY_PIN_1, OUTPUT);
    pinMode(RELAY_PIN_2, OUTPUT);
    pinMode(RELAY_PIN_3, OUTPUT);

    digitalWrite(IGNITER_PIN, HIGH);
    digitalWrite(RELAY_PIN_1, HIGH);
    digitalWrite(RELAY_PIN_2, LOW);
    digitalWrite(RELAY_PIN_3, LOW);

    DEBUG("====== LED ======");
    led.setup();

    DEBUG("====== Flash ======");
    flashWriter.setup();

    DEBUG("====== Press Setup======");
    PressureSensors[0].setup(PRESS_SENSOR_0);
    PressureSensors[1].setup(PRESS_SENSOR_1);
    PressureSensors[2].setup(PRESS_SENSOR_2);

    DEBUG("====== Flowrate setup ======");
    flowRate[0].setup(FLOWRATE_PIN_0);
    flowRate[1].setup(FLOWRATE_PIN_1);
    flowRate[2].setup(FLOWRATE_PIN_2);
    flowRate[3].setup(FLOWRATE_PIN_3);
    flowRate[4].setup(FLOWRATE_PIN_4);

    flowRate[0].closeAll();

    DEBUG("====== Load cell setup ======");
    loadCell[0].setup(LOADCELL_DT_0, LOADCELL_SCK_0);
    loadCell[1].setup(LOADCELL_DT_1, LOADCELL_SCK_1);

    DEBUG("====== Webserver setup ======");
    //webserver.setup();

    DEBUG("====== Setup DONE ======");
    // Hooks are in the webserver.cpp file
    // sequences are also gonna be somewhere there
    // vtastkschedular is already used so dont call
}

// https://freertos.org/Documentation/161204_Mastering_the_FreeRTOS_Real_Time_Kernel-A_Hands-On_Tutorial_Guide.pdf

void loop()
{
    // Loop is not used as everything is task or event based
    while (true) {
        DEBUG(loadCell[0].read());
        DEBUG(loadCell[1].read());
    }
    vTaskDelete(NULL);
}

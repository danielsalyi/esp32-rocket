#include <Arduino.h>
#include <configs.h>
#include <led/led.h>
#include <webserver/webserver.h>
#include <logger/logger.h>
#include <pressureSensor/pressureSensor.h> 


void setup()
{
    Serial0.begin(BAUD_RATE);

    // SETUP
    Serial0.println("======ESP Setup======");
    // LED 
    led.setup();

    // Pressure sensor
    initPressureSensors();
    Serial0.printf("Pressure sensor 1: %u\n", PressureSensors[0].read()); 

    // Flowrate 

    // Load cell

    // Webserver
    initWebserver();

    // Logger
    initLogger();
    Serial0.println("======Setup DONE======");


    // TASKS
    Serial0.println("Scheduling tasks...");
    vTaskStartScheduler();

    // Hook are in the webserver.cpp file
    // sequences are also gonna be there
}

// vTaskGetRunTimeStats
// uxTaskGetSystemState

// https://freertos.org/Documentation/161204_Mastering_the_FreeRTOS_Real_Time_Kernel-A_Hands-On_Tutorial_Guide.pdf

void loop()
{
    // Loop is not used as everything is task or event based
    vTaskDelete(NULL);
}

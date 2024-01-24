#include <Arduino.h>
#include <configs.h>
#include <led/led.h>
#include <webserver/webserver.h>
#include <flashWriter/flashWriter.h>
#include <pressureSensor/pressureSensor.h> 
#include <flowrate/flowrate.h> 
#include <loadCell/loadcell.h>

void setup()
{
    Serial0.begin(BAUD_RATE);

    Serial0.println("======ESP Setup======");

    // LED
    led.setup();
    
    // Flash writer
    flashWriter.setup();

    // Pressure sensors
    initPressureSensors();
    Serial0.printf("Pressure sensor 1: %u\n", PressureSensors[0].read()); 

    // Flowrate 
    flowRate.setup();
    Serial0.printf("Flowrate: %u\n", flowRate.read());    

    // Load cell
    loadCell.setup();

    // Webserver
    webserver.setup();

    Serial0.println("======Setup DONE======");


    // TASKS
    Serial0.println("Scheduling tasks...");
    vTaskStartScheduler();

    // Hooks are in the webserver.cpp file
    // sequences are also gonna be somewhere there
}


// https://freertos.org/Documentation/161204_Mastering_the_FreeRTOS_Real_Time_Kernel-A_Hands-On_Tutorial_Guide.pdf


void loop()
{
    // Loop is not used as everything is task or event based
    vTaskDelete(NULL);
}

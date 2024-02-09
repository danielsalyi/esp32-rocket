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

    Serial0.println("======ESP Setup======");

    // LED
    led.setup();

    Serial0.println("======LED======");
    
    // Flash writer
    flashWriter.setup();
    Serial0.println("======flash======");

    // Pressure sensors
    initPressureSensors();
    Serial0.println("======press setup======");
    Serial0.printf("Pressure sensor 1: %u\n", PressureSensors[0].read()); 

    // Flowrate 
    flowRate.setup();
    Serial0.println("======flowrate setup======");
    
    flowRate.set(0);
    // vTaskDelay(5000 / portTICK_PERIOD_MS);
    Serial0.printf("Flowrate: %u\n", flowRate.read());    

    flowRate.set(270);
    // vTaskDelay(5000 / portTICK_PERIOD_MS);
    Serial0.printf("Flowrate: %u\n", flowRate.read());    

    
    // Load cell
    loadCell.setup();

    // Webserver
    webserver.setup();

    Serial0.println("======Setup DONE======");

    Serial0.write('b\x03');
    
    // Hooks are in the webserver.cpp file
    // sequences are also gonna be somewhere there
    // vtastkschedular is already used so dont call
}


// https://freertos.org/Documentation/161204_Mastering_the_FreeRTOS_Real_Time_Kernel-A_Hands-On_Tutorial_Guide.pdf


void loop()
{
    // Loop is not used as everything is task or event based
    vTaskDelete(NULL);
}

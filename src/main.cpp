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
    

    DEBUG("====== LED ======");
    led.setup();


    DEBUG("====== Flash ======");
    flashWriter.setup();


    DEBUG("====== Press Setup======");
    PressureSensors[0].setup(PRESS_SENSOR_0);
    PressureSensors[1].setup(PRESS_SENSOR_1);
    PressureSensors[2].setup(PRESS_SENSOR_2);


    DEBUG("======flowrate setup======");
    // set up the first 3 valves 
    flowRate[0].setup(FLOWRATE_PIN_0);
    flowRate[1].setup(FLOWRATE_PIN_1);
    flowRate[3].setup(FLOWRATE_PIN_3);

    
    DEBUG("motor 3 to 0");
    flowRate[3].set(0);
    delay(2000);
    flowRate[3].detach();
    delay(2000);

    flowRate[4].setup(FLOWRATE_PIN_4);
    flowRate[4].set(0);
    DEBUG("motor 4 to 0");
    delay(2000);
    flowRate[4].detach();
    delay(2000);

    flowRate[0].setup(FLOWRATE_PIN_0);
    DEBUG("motor 0 to 90");
    flowRate[0].set(90);
    delay(2000);
    flowRate[0].detach();
    delay(2000);

    flowRate[1].setup(FLOWRATE_PIN_1);
    DEBUG("motor 1 to 90");
    flowRate[1].set(90);
    delay(2000);
    flowRate[1].detach();

    flowRate[2].setup(FLOWRATE_PIN_2);
    DEBUG("motor 2 to 90");
    flowRate[2].set(90);
    delay(2000);
    flowRate[2].detach();
    delay(2000);

    flowRate[3].setup(FLOWRATE_PIN_3);
    DEBUG("motor 3 to 90");
    flowRate[3].set(90);
    delay(2000);
    flowRate[3].detach();
    delay(2000);

    flowRate[4].setup(FLOWRATE_PIN_4);
    DEBUG("motor 4 to 90");
    flowRate[4].set(90);
    delay(2000);
    flowRate[4].detach();
    delay(2000);

    DEBUG("====== Load cell setup ======");
    loadCell[0].setup(LOADCELL_DT_0, LOADCELL_SCK_0);
    loadCell[1].setup(LOADCELL_DT_1, LOADCELL_SCK_1);


    DEBUG("====== Webserver setup ======");
    webserver.setup();

    DEBUG("======Setup DONE======");    
    // Hooks are in the webserver.cpp file
    // sequences are also gonna be somewhere there
    // vtastkschedular is already used so dont call
}

// wait t ms
void vTaskDelayMS(int t) 
{
    TickType_t xDelay = t / portTICK_PERIOD_MS;
    vTaskDelay(xDelay);
}

void sequence() 
{
    //const 
    // t -5
    flowRate[0].set(OPEN_VALVE);
    vTaskDelayMS(4000);

    // t -2
    // start ignition coil

    // t -1
    flowRate[1].set(OPEN_VALVE);
    flowRate[3].set(OPEN_VALVE);

    vTaskDelayMS(6000);


    // t 4
    // stop ignition coil

    // t 5
    // close valves
    flowRate[0].set(CLOSE_VALVE);
    flowRate[1].set(CLOSE_VALVE);
    flowRate[3].set(CLOSE_VALVE);
    // detach them
    flowRate[0].detach();
    flowRate[1].detach();
    flowRate[3].detach();
    // attach the other 2 valves
    flowRate[2].setup(FLOWRATE_PIN_2);
    flowRate[4].setup(FLOWRATE_PIN_4);
    // open valves
    flowRate[2].set(OPEN_VALVE);
    flowRate[4].set(OPEN_VALVE);

    vTaskDelayMS(5000);

    // t 10
    flowRate[2].set(CLOSE_VALVE);
    flowRate[4].set(CLOSE_VALVE);
}

// https://freertos.org/Documentation/161204_Mastering_the_FreeRTOS_Real_Time_Kernel-A_Hands-On_Tutorial_Guide.pdf


void loop()
{
    // Loop is not used as everything is task or event based
    vTaskDelete(NULL);
}

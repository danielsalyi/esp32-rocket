#include <Arduino.h>
#include <actuators/actuators.h>
#include <sensors/sensors.h>
#include <utils/configs.h>
#include <utils/webserver/webserver.h>
#include <utils/logger/logger.h>

void setup()
{
    Serial0.begin(BAUD_RATE);
    Serial0.println("======ESP Setup======");

    initActuators();
    initSensors();
    ASADASDASD

    initWebserver();

    initLogger();
}

// uxTaskGetSystemState
// vTaskGetRunTimeStats

// https://freertos.org/Documentation/161204_Mastering_the_FreeRTOS_Real_Time_Kernel-A_Hands-On_Tutorial_Guide.pdf

void loop()
{
    // Loop is not used as everything is task or event based
    vTaskDelete(NULL);
}

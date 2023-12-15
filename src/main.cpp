#include <Arduino.h>
#include <actuators/actuators.h>
#include <sensors/sensors.h>
#include <utils/configs.h>
#include <utils/webserver/webserver.h>
#include <utils/logger/logger.h>
#include <ArduinoLog.h>

void setup()
{
    initLogger();

    // move this to logger
    Serial0.begin(BAUD_RATE);
    Log.begin(LOG_LEVEL_VERBOSE, &Serial);
    Log.verbose("======ESP Setup======");

    initActuators();
    initSensors();

    initWebserver();

    // schedule tasks?
    // xtaskcreate(...)
    vTaskStartScheduler(); // ????
}

void loop()
{
    // Loop is not used as everything is task or event based
    vTaskDelete(NULL);
}

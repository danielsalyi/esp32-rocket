#include <Arduino.h>
#include <WiFi.h>
#include <webserver/webserver.h>
#include <config/config.h>
#include <led/led.h>

void setup()
{
    Serial0.begin(BAUD_RATE);
    initLED();
    initWebserver();
    createEndpoints();
}

void loop()
{
}

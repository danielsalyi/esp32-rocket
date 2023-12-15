#include <ESPAsyncWebServer.h>
#include <actuators/led/led.h>
#include "AsyncJson.h"
#include <ArduinoJson.h>

void onLedRequest(AsyncWebServerRequest *request)
{
    request->send(200, "OK");
}

void onLedBody(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total)
{
    DynamicJsonDocument doc(1024);
    deserializeJson(doc, data);

    setLED(doc["red"], doc["green"], doc["blue"]);

    Serial0.printf("body=%s\n", (char *)data);
    request->send(200, "OK");
}
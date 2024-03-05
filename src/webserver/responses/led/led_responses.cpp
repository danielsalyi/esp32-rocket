#include <ESPAsyncWebServer.h>
#include <led/led.h>
#include "AsyncJson.h"
#include <ArduinoJson.h>
#include <configs.h>
#include <webserver/responses/led/led_responses.h>


void createLedEndpoints(AsyncWebServer *server)
{
    server->on("/led", HTTP_GET, [](AsyncWebServerRequest *request) 
    { 
        request->send(200, "OK");
    },
    NULL, 
    [](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total)
    {
        DynamicJsonDocument doc(1024);
        deserializeJson(doc, data);

        led.set(doc["red"], doc["green"], doc["blue"]);

        DEBUG_F("body=%s\n", (char *)data);
        request->send(200, "OK");
    });

}

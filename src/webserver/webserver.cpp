#include <ESPAsyncWebServer.h>
#include <led/led.h>
#include <configs.h>
#include <webserver/responses/led_responses.h>
#include <LittleFS.h>
#include "logger/logger.h"

#define SPIFFS LittleFS

AsyncWebServer server(80);

void createWifiConnection()
{
    WiFi.begin(SSID, PASSWORD);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial0.println("Connecting to WiFi..");
    }
    Serial0.println(WiFi.localIP());

    led.set(0, 255, 0);
}

void createEndpoints()
{
    server.on("/led", HTTP_GET, onLedRequest, NULL, onLedBody);

    server.on("/read", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                  request->send(SPIFFS, "/data1.csv", "text/plain");
                  //
              });

    server.on("/flush", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                  flushFile();
                  request->send(200, "OK");
                  //
              });

    server.on("/status", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                  Serial0.println(ESP.getFreeHeap());
                  request->send(200, "OK");
                  //
              });

    server.on("/write", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                  const char *mesage = "1, 2, 3, 4, 5;";
                  appendToFile(mesage);

                  request->send(200, "OK");
                  //
              });

    server.begin(); // has a priority 3
}

void initWebserver()
{
    createWifiConnection();
    createEndpoints();
}

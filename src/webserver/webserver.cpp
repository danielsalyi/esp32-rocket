#include <ESPAsyncWebServer.h>
#include <webserver/webserver.h>
#include <led/led.h>
#include <configs.h>
#include <webserver/responses/led_responses.h>
#include <LittleFS.h>
#include "flashWriter/flashWriter.h"
#include <cstdint> 

#define SPIFFS LittleFS

// arming bool
bool armed = false;

AsyncWebServer server(80);
Webserver webserver; // singleton
//https://stackoverflow.com/questions/1008019/how-do-you-implement-the-singleton-design-pattern/1008289#1008289
// maybe do it with a legit singleton pattern?


// public
Webserver::Webserver()
{
    // cannot call setup here, it will crash it
}

void Webserver::setup()
{
    initWebserver();
}


// private
void Webserver::initWebserver()
{
    createWifiConnection();

    createEndpoints();
    createFlashWriterEndpoints();

    server.begin(); // has a priority 3
}

void Webserver::createSequenceEndpoints()
{
    server.on("/arm", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                  armed = true;
                  request->send(200, "OK");
                  //
              });

    server.on("/sequence", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                if (armed){
                    // create task for sequence 

                    // xTaskCreate()...;

                    armed = false;
                }
                  request->send(200, "OK");
                  //
              });
}

void Webserver::createWifiConnection()
{
    WiFi.begin(SSID, PASSWORD);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial0.println("Connecting to WiFi..");
    }
    Serial0.println(WiFi.localIP());

    // LED indication of connection
    led.set(0, 255, 0); // green
}

// LED endpoints
void Webserver::createEndpoints(){
    server.on("/led", HTTP_GET, onLedRequest, NULL, onLedBody);
}

// Flash writer endpoints
void Webserver::createFlashWriterEndpoints()
{
    server.on("/read", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                  request->send(SPIFFS, "/data1.csv", "text/plain");
                  //
              });

    server.on("/flush", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                  flashWriter.flush();
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
                  flashWriter.write(mesage);

                  request->send(200, "OK");
                  //
              });
    
    server.on("/writeSensor", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                  sensorReadings readings = {1, 2, 3, 456, 789};
                  flashWriter.write(readings);

                  request->send(200, "OK");
                  //
              });
}

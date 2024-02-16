#include <ESPAsyncWebServer.h>
#include <webserver/webserver.h>
#include <led/led.h>
#include <configs.h>
#include <webserver/responses/led_responses.h>
#include <LittleFS.h>
#include "flashWriter/flashWriter.h"
#include "pressureSensor/pressureSensor.h"
#include "flowrate/flowrate.h"
#include "loadcell/loadcell.h"
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
                  request->send(SPIFFS, flashWriter.pathToFile(), "text/plain");
                  //
              });

    server.on("/flush", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                  sendResponse(request, [](){
                    flashWriter.flush();
                  });
                  //
              });

    server.on("/status", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                  sendResponse(request, [](){
                    Serial0.println(ESP.getFreeHeap());
                  });
                  //
              });

    server.on("/write", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                  const char *mesage = "1, 2, 3, 4, 5;";
                  flashWriter.append(mesage);

                  request->send(200, "OK");
                  //
              });
    
    server.on("/writeSensor", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                  sendResponse(request, []() {
                    sensorReadings readings;
                    readSensors(readings);
                    flashWriter.writeSensors(readings);
                  });
                  //
              });
}

template<typename Func>
void sendResponse(AsyncWebServerRequest *request, Func func) {
    try {
        func();
        request->send(200, "OK");
    } catch (...) { // can add more errors here
        request->send(400, "bad request");
    }
}

void readSensors(sensorReadings& readings) {
    // read the pressure sensors
    for (int i = 0; i < numPressureSensors; i++) {
        readings.pressureSensorReadings[i] = PressureSensors[i].read();
    }
    // read the load cell
    readings.loadCellReading = loadCell.read();
}
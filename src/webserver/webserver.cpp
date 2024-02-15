#include <ESPAsyncWebServer.h>
#include <webserver/webserver.h>
#include "configs.h"
#include <led/led.h>
#include <webserver/responses/led/led_responses.h>
#include <LittleFS.h>
#include "flashWriter/flashWriter.h"
#include <flowrate/flowrate.h>

#define SPIFFS LittleFS

AsyncWebServer server(80);
Webserver webserver; 

//https://stackoverflow.com/questions/1008019/how-do-you-implement-the-singleton-design-pattern/1008289#1008289
// maybe do it with a legit singleton pattern?

static bool armed; // idk why but I cannot make it private

// public
Webserver::Webserver()
{

}

void Webserver::setup()
{
    createWifiConnection();

    createEndpoints();

    server.begin(); // has a priority 3
}


void ignitionSequence(void *pvParameters){
    // do something here
    flashWriter.appendSensorData(NULL);
}

void createSequenceEndpoints()
{
    server.on("/arm", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                    led.set(255, 0, 0); // red
                  armed = true;
                  request->send(200, "ARMED!");
                  //
              });

    server.on("/disarm", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                    led.set(0, 255, 0); // green
                  armed = false;
                  request->send(200, "DISARMED!");
                  //
              });

    server.on("/armstatus", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                    String status = armed ? "ARMED!" : "DISARMED!";
                  request->send(200, status.c_str());
                  //
              });

    server.on("/ignition", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                if (armed){
                    // create task for sequence 
                    xTaskCreate(ignitionSequence,
                                "ignitionSequence",
                                10000,
                                NULL,
                                1,
                                NULL); // instead of null u need a handler

                    armed = false;
                } else {
                    request->send(200, "Not armed!");
                }
                  //
              });

    server.on("/abort", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                if (armed){
                    // create task for sequence 
                    // vTaskSuspend(ignitionSequence);
                    // here u need a handler 

                    // flowrate[0].set(0);
                    
                    armed = false;
                } else {
                    request->send(200, "Not armed!");
                }
                  //
              });
}

void Webserver::createWifiConnection()
{
    WiFi.begin(SSID, PASSWORD);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        DEBUG("Connecting to WiFi..");
    }
    Serial0.println(WiFi.localIP());

    // LED indication of connection
    led.set(0, 255, 0); // green
}

// LED endpoints
void Webserver::createEndpoints(){


    createLedEndpoints(&server);
    // createFlashWriterEndpoints();
    // createFlashWriterEndpoints();
    // createSequenceEndpoints();
}

// Flash writer endpoints
void createFlashWriterEndpoints()
{
    server.on("/read", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                  request->send(SPIFFS, flashWriter.pathToFile(), "text/plain");
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
                  flashWriter.append(mesage);

                  request->send(200, "OK");
                  //
              });
}

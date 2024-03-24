#include <LittleFS.h>
#include "flashWriter/flashWriter.h"
#include <ESPAsyncWebServer.h>

#include <pressureSensor/pressureSensor.h>
#include <loadcell/loadcell.h>

#define SPIFFS LittleFS

void createFlashWriterEndpoints(AsyncWebServer *server)
{
    server->on("/read", HTTP_GET, [](AsyncWebServerRequest *request)
               {
                   request->send(SPIFFS, flashWriter.pathToFile(), "text/plain");
                   //
               });

    server->on("/flush", HTTP_GET, [](AsyncWebServerRequest *request)
               {
                   flashWriter.flush();
                   request->send(200, "OK");
                   //
               });

    server->on("/write", HTTP_GET, [](AsyncWebServerRequest *request)
               {
                   const char *mesage = "1, 2, 3, 4, 5;";
                   flashWriter.append(mesage);

                   request->send(200, "OK");
                   //
               });

    server->on("/writeSensor", HTTP_GET, [](AsyncWebServerRequest *request)
               {
                   struct sensorReadings sensorReadings;

                   sensorReadings.pressureSensor1 = PressureSensors[0].read();
                   sensorReadings.pressureSensor2 = PressureSensors[1].read();
                   sensorReadings.loadCellReading = loadCell[1].read();

                   flashWriter.appendSensorData(&sensorReadings);
                   flashWriter.flush();

                   request->send(SPIFFS, flashWriter.pathToFile(), "text/plain"); });
}

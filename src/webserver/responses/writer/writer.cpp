#include <LittleFS.h>
#include "flashWriter/flashWriter.h"
#include <ESPAsyncWebServer.h>

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
}

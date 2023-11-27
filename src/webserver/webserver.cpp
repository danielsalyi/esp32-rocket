#include "ESPAsyncWebServer.h"
#include "led/led.h"
#include "config/config.h"

AsyncWebServer server(80);

void initWebserver()
{
    WiFi.begin(SSID, PASSWORD);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial0.println("Connecting to WiFi..");
    }
    Serial0.println(WiFi.localIP());
}

void createEndpoints()
{
    server.on("/green", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                  request->send_P(200, "text/plain", "ok");

                  setLED(0, 255, 0);
                  //
              });

    server.on("/red", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                  request->send_P(200, "text/plain", "ok");

                  setLED(255, 0, 0);
                  //
              });

    server.begin();
}
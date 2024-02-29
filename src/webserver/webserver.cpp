#include <ESPAsyncWebServer.h>
#include <webserver/webserver.h>
#include "configs.h"
#include <led/led.h>
#include <webserver/responses/led/led_responses.h>
#include <webserver/responses/writer/writer.h>
#include <webserver/responses/sequences/sequences.h>

#define SPIFFS LittleFS

// arming bool
bool armed = false;

AsyncWebServer server(80);
Webserver webserver;

Webserver::Webserver()
{
}

void Webserver::setup()
{
    createWifiConnection();

    createEndpoints();

    server.begin(); // has a priority 3
}

void Webserver::createWifiConnection()
{
    WiFi.begin(SSID_WIFI, PASSWORD_WIFI);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        DEBUG("Connecting to WiFi..");
    }
    Serial0.println(WiFi.localIP());

    // LED indication of connection
    led.set(0, 255, 0); // green
}

void Webserver::createEndpoints()
{
    createLedEndpoints(&server);
    createFlashWriterEndpoints(&server);
    createSequenceEndpoints(&server);
}

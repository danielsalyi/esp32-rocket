#include <ESPAsyncWebServer.h>
#include <webserver/webserver.h>
#include "configs.h"
#include <led/led.h>
#include <webserver/responses/led/led_responses.h>
#include <webserver/responses/writer/writer.h>
#include <webserver/responses/sequences/sequences.h>

AsyncWebServer server(80);
Webserver webserver;

Webserver::Webserver()
{
}

void checkWifiConnection(void *pvParameters)
{
    while (1)
    {

        vTaskDelay(3000 / portTICK_PERIOD_MS); // 1s delay
        // wifi reconnects by default, but we want to change the led

        if (WiFi.status() != WL_CONNECTED)
        {
            led.set(255, 255, 255); // white
            DEBUG_F("wifi satus: %s \n", WiFi.status());
        }
    }

    vTaskDelete(NULL);
}

void Webserver::setup()
{
    createWifiConnection();

    createEndpoints();

    server.begin(); // has a priority 3
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

    xTaskCreate(checkWifiConnection, "checkWifiConnection", 10000, NULL, 4, NULL);

    // LED indication of connection
    led.set(0, 255, 0); // green
}

void Webserver::createEndpoints()
{
    createLedEndpoints(&server);
    createFlashWriterEndpoints(&server);
    createSequenceEndpoints(&server);
}

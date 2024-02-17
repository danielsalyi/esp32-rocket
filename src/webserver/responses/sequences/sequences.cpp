#include <ESPAsyncWebServer.h>
#include <webserver/responses/sequences/sequences.h>
#include "flashWriter/flashWriter.h"
#include <led/led.h>
#include <flowrate/flowrate.h>
#include <configs.h>

static bool armed;
TaskHandle_t ignitionSequenceHandle;
TaskHandle_t readSensorHandle;

void cleanUpIgnitionSequence()
{
    vTaskDelete(ignitionSequenceHandle); // delete ignitionSequenceTask

    digitalWrite(IGNITER_PIN, LOW); // turn off the igniter

    vTaskDelete(readSensorHandle); // delete the readSensorTask
    flashWriter.flush();           // flush the data to the flash

    // close the valves
    flowRate[0].set(0);
    flowRate[1].set(0);
    flowRate[2].set(0);
    flowRate[3].set(0);
    flowRate[4].set(0);
}

void ignitionSequenceTask(void *pvParameters)
{
    // 1. Open the valve
    // waoit 5 seconds
    // 2. open vale
    // wait 5 seconds
    // ...

    // ...

    // Clean up
    cleanUpIgnitionSequence();
}

void readSensorTask(void *pvParameters)
{
    for (;;)
    {
        // read data...

        // flashwriter.write(data);

        vTaskDelay(100 / portTICK_PERIOD_MS); // 100 delay in ms
    }
}

void createSequenceEndpoints(AsyncWebServer *server)
{
    server->on("/heapstatus", HTTP_GET, [](AsyncWebServerRequest *request)
               {
                   Serial0.println(ESP.getFreeHeap());
                   request->send(200, String(ESP.getFreeHeap()), "text/plain");
                   //
               });

    server->on("/arm", HTTP_GET, [](AsyncWebServerRequest *request)
               {
                   led.set(255, 0, 0); // red
                   armed = true;
                   request->send(200, "ARMED!");
                   //
               });

    server->on("/disarm", HTTP_GET, [](AsyncWebServerRequest *request)
               {
                   led.set(0, 255, 0); // green
                   armed = false;
                   request->send(200, "DISARMED!");
                   //
               });

    server->on("/armstatus", HTTP_GET, [](AsyncWebServerRequest *request)
               {
                   String status = armed ? "ARMED!" : "DISARMED!";
                   request->send(200, status.c_str());
                   //
               });

    server->on("/ignition", HTTP_GET, [](AsyncWebServerRequest *request)
               {
                   if (armed)
                   {

                       // start with the reading
                       xTaskCreate(readSensorTask,
                                   "readSensorTask",
                                   10000,
                                   NULL,
                                   1,
                                   &readSensorHandle); // pass the address

                       // Turn on the igniter
                       pinMode(IGNITER_PIN, OUTPUT);
                       digitalWrite(IGNITER_PIN, HIGH);

                       // create task for ignition sequence
                       xTaskCreate(ignitionSequenceTask,
                                   "ignitionSequenceTask",
                                   10000,
                                   NULL,
                                   1,
                                   &ignitionSequenceHandle); // pass the address of ignitionSequenceHandle

                       request->send(200, "Ignition sequence started!");
                   }
                   else
                   {
                       request->send(200, "Not armed!");
                   }
                   //
               });

    server->on("/abort", HTTP_GET, [](AsyncWebServerRequest *request)
               {
                   if (armed)
                   {
                       cleanUpIgnitionSequence();

                       request->send(200, "Aborted!");
                   }
                   else
                   {
                       request->send(200, "Not armed!");
                   }
                   //
               });
}

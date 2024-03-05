#include <ESPAsyncWebServer.h>
#include <webserver/responses/sequences/sequences.h>
#include "flashWriter/flashWriter.h"
#include <led/led.h>
#include <flowrate/flowrate.h>
#include <configs.h>

#include <atomic>

static std::atomic<bool> isArmed(false);
static std::atomic<bool> isIgnitionSequenceRunning(false);
TaskHandle_t ignitionSequenceHandle = NULL;
TaskHandle_t readSensorHandle = NULL;

void readSensorTask(void *pvParameters)
{
    while (isIgnitionSequenceRunning)
    {
        // read data...

        flashWriter.append("0,1,2,3,4,5,6,7,8,9,10; \n");
        flashWriter.flush();

        vTaskDelay(100 / portTICK_PERIOD_MS); // 100 delay in ms
    }

    // u need this for the task to delete itself if it jumps stacks?
    vTaskDelete(NULL);
}

void cleanUpIgnitionSequence()
{
    DEBUG("Cleaning up ignition sequence...");

    digitalWrite(IGNITER_PIN, LOW); // turn off the igniter

    DEBUG("Cleaning up flow rate...");

    // close the valves
    flowRate[0].set(0);
    flowRate[1].set(0);
    flowRate[2].set(0);
    flowRate[3].set(0);
    flowRate[4].set(0);

    isIgnitionSequenceRunning = false;
}

void ignitionSequenceTask(void *pvParameters)
{
    // 1. Open the valve
    // waoit 5 seconds
    // 2. open vale
    // wait 5 seconds
    // ...

    vTaskDelay(5000 / portTICK_PERIOD_MS);
    // ...

    // Clean up
    cleanUpIgnitionSequence();
    vTaskDelete(NULL);
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
                   DEBUG("ARMED!");
                   led.set(255, 0, 0); // red
                   isArmed = true;
                   request->send(200, "ARMED!");
                   //
               });

    server->on("/disarm", HTTP_GET, [](AsyncWebServerRequest *request)
               {
                   DEBUG("DISARMED!");
                   led.set(0, 255, 0); // green
                   isArmed = false;
                   request->send(200, "DISARMED!");
                   //
               });

    server->on("/armstatus", HTTP_GET, [](AsyncWebServerRequest *request)
               {
                   String status = isArmed ? "ARMED!" : "DISARMED!";
                   DEBUG(status);
                   request->send(200, status.c_str());
                   //
               });

    server->on("/ignition", HTTP_GET, [](AsyncWebServerRequest *request)
               {
                   if (!isArmed)
                   {
                       request->send(200, "Not armed!");
                       return;
                   }

                   if (isIgnitionSequenceRunning)
                   {
                       request->send(200, "Ignition sequence already running!");
                       return;
                   }

                   DEBUG("Starting ignition sequence...");
                   isIgnitionSequenceRunning = true;

                   // start with the reading
                   xTaskCreate(readSensorTask,
                               "readSensorTask",
                               10000,
                               NULL,
                               2,
                               &readSensorHandle); // pass the address

                   // Turn on the igniter
                   //    pinMode(IGNITER_PIN, OUTPUT);
                   //    digitalWrite(IGNITER_PIN, HIGH);

                   // create task for ignition sequence
                   xTaskCreate(ignitionSequenceTask,
                               "ignitionSequenceTask",
                               10000,
                               NULL,
                               1,
                               &ignitionSequenceHandle); // pass the address of ignitionSequenceHandle

                   request->send(200, "Ignition sequence started!");
                   //
               });

    server->on("/abort", HTTP_GET, [](AsyncWebServerRequest *request)
               {
                   DEBUG("Aborting ignition sequence...");

                   vTaskSuspend(ignitionSequenceHandle);
                   cleanUpIgnitionSequence();

                   request->send(200, "Cleaned up!");
                   //
               });
}

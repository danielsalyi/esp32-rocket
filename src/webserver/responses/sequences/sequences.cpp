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

// wait t ms
void vTaskDelayMS(int t)
{
    TickType_t xDelay = t / portTICK_PERIOD_MS;
    vTaskDelay(xDelay);
}

void readSensorTask(void *pvParameters)
{
    while (isIgnitionSequenceRunning)
    {
        // read data...

        flashWriter.append("0,1,2,3,4,5,6,7,8,9,10; \n");
        flashWriter.flush();

        vTaskDelayMS(100); // 100 delay in ms
    }

    // u need this for the task to delete itself if it jumps stacks?
    vTaskDelete(NULL);
}

void finishIgintion()
{
    DEBUG("Cleaning up ignition sequence...");

    digitalWrite(IGNITER_PIN, LOW); // turn off the igniter

    DEBUG("Cleaning up flow rate...");
    flowRate[0].closeAll();

    isIgnitionSequenceRunning = false;
}

void ignitionSequenceTask(void *pvParameters)
{
    // t -5
    flowRate[0].set(OPEN_VALVE);
    vTaskDelayMS(3000);

    // t -2
    // start ignition coil
    digitalWrite(IGNITER_PIN, HIGH); // ! DOUBLE CHECK THIS IF THIS MEANS OFF
    vTaskDelayMS(1000);

    // t -1
    flowRate[1].set(OPEN_VALVE);
    flowRate[3].set(OPEN_VALVE);

    vTaskDelayMS(6000);
    // t 4
    // stop ignition coil
    digitalWrite(IGNITER_PIN, LOW); // ! DOUBLE CHECK THIS IF THIS MEANS OFF

    // t 5
    // close valves
    flowRate[0].set(CLOSE_VALVE);
    flowRate[1].set(CLOSE_VALVE);
    flowRate[3].set(CLOSE_VALVE);

    // open valves
    flowRate[2].set(OPEN_VALVE);
    flowRate[4].set(OPEN_VALVE);

    vTaskDelayMS(5000);

    // t 10
    flowRate[2].set(CLOSE_VALVE);
    flowRate[4].set(CLOSE_VALVE);

    DEBUG("IGNITION OVER");

    finishIgintion();

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
                   finishIgintion();

                   request->send(200, "Cleaned up!");
                   //
               });

    server->on("/test", HTTP_GET, [](AsyncWebServerRequest *request)
               {
                   DEBUG("Test endpoint hit!");

                   request->send(200, "Testing...");

                   flowRate[0].test();
                   //
               });
}

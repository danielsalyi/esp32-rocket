#include <ESPAsyncWebServer.h>
#include <webserver/responses/sequences/sequences.h>
#include <configs.h>
#include <atomic>

#include <pressureSensor/pressureSensor.h>
#include "flashWriter/flashWriter.h"
#include <led/led.h>
#include <flowrate/flowrate.h>
#include <loadcell/loadcell.h>

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
    struct sensorReadings sensorReadings;

    while (isIgnitionSequenceRunning)
    {
        sensorReadings.pressureSensor1 = PressureSensors[0].read();
        sensorReadings.pressureSensor2 = PressureSensors[1].read();
        sensorReadings.loadCellReading = loadCell[1].read();

        flashWriter.appendSensorData(&sensorReadings);
        flashWriter.flush();

        vTaskDelayMS(75); // 75 delay in ms
    }

    // u need this for the task to delete itself if it jumps stacks?
    vTaskDelete(NULL);
}

void ignitionSequenceTask(void *pvParameters)
{
    DEBUG("IGNITION STARTED");

#if FUEL_PRIORITY
    // FUEL PRIORITY SEQUENCE
    // t-0
    flowRate[0].attach();
    flowRate[0].set(OPEN_VALVE);
    vTaskDelayMS(1000); // t+1
    flowRate[0].detach();

    // t+1
    digitalWrite(IGNITER_PIN, RELAY_ON);
    vTaskDelayMS(300); // t+1.3

    // t+1.3
    flowRate[3].attach();
    flowRate[3].set(25); // 25% open
    vTaskDelayMS(200);   // t+1.5

    // t+1.5
    flowRate[1].attach();
    flowRate[1].set(25); // 25% open
    vTaskDelayMS(500);   // t+2

    // t+2
    flowRate[1].set(OPEN_VALVE); // 100% open
    flowRate[3].set(OPEN_VALVE); // 100% open
    vTaskDelayMS(1000);          // t+3

    // t+3
    digitalWrite(RELAY_PIN_1, RELAY_OFF);
    vTaskDelayMS(4000); // t+7

    // t+7
    flowRate[1].set(CLOSE_VALVE);
    flowRate[3].set(CLOSE_VALVE);
    vTaskDelayMS(1000); // t+8
    flowRate[1].detach();
    flowRate[3].detach();

    // t+8
    flowRate[2].attach();
    flowRate[4].attach();
    flowRate[2].set(OPEN_VALVE);
    flowRate[4].set(OPEN_VALVE);
    vTaskDelayMS(7000); // t+15

    // t+15
    flowRate[2].set(CLOSE_VALVE);
    flowRate[4].set(CLOSE_VALVE);
#else
    // OXIGEN PRIORITY SEQUENCE
    // t-0
    flowRate[0].attach();
    flowRate[0].set(OPEN_VALVE);
    vTaskDelayMS(1000); // t+1
    flowRate[0].detach();

    // t+1
    digitalWrite(IGNITER_PIN, RELAY_ON);
    vTaskDelayMS(300); // t+1.3

    // t+1.3
    flowRate[1].attach();
    flowRate[1].set(25); // 25% open
    vTaskDelayMS(700);   // t+2

    // t+2
    flowRate[3].attach();
    flowRate[3].set(25); // 25% open
    vTaskDelayMS(300);   // t+2.3

    // t+2.3
    flowRate[1].set(OPEN_VALVE); // 100% open
    flowRate[3].set(OPEN_VALVE); // 100% open
    vTaskDelayMS(700);           // t+3

    // t+3
    digitalWrite(RELAY_PIN_1, RELAY_OFF);
    vTaskDelayMS(4300); // t+7.3

    // t+7.3
    flowRate[1].set(CLOSE_VALVE);
    flowRate[3].set(CLOSE_VALVE);
    vTaskDelayMS(700); // t+8
    flowRate[1].detach();
    flowRate[3].detach();

    // t+8
    flowRate[2].attach();
    flowRate[4].attach();
    flowRate[2].set(OPEN_VALVE);
    flowRate[4].set(OPEN_VALVE);
    vTaskDelayMS(7000); // t+15

    // t+15
    flowRate[2].set(CLOSE_VALVE);
    flowRate[4].set(CLOSE_VALVE);
#endif

    isIgnitionSequenceRunning = false;
    DEBUG("IGNITION OVER");

    vTaskDelete(NULL);
}

void testServosTask(void *pvParameters)
{
    for (int i = 0; i < 5; i++)
    {
        flowRate[i].attach();
        flowRate[i].set(OPEN_VALVE);
        vTaskDelayMS(1000);
        flowRate[i].set(CLOSE_VALVE);
        vTaskDelayMS(1000);
        flowRate[i].detach();
    }

    vTaskDelete(NULL);
}

void abortSequenceTask(void *pvParameters)
{
    // DETACH ALL
    flowRate[0].detach();
    flowRate[1].detach();
    flowRate[2].detach();
    flowRate[3].detach();
    flowRate[4].detach();

    // CLOSE 3 AND 1
    flowRate[3].attach();
    flowRate[1].attach();
    flowRate[3].set(CLOSE_VALVE);
    flowRate[1].set(CLOSE_VALVE);

    vTaskDelayMS(1000); // wait until they close

    flowRate[3].detach();
    flowRate[1].detach();

    // open 2 and 4
    flowRate[2].attach();
    flowRate[4].attach();
    flowRate[2].set(OPEN_VALVE);
    flowRate[4].set(OPEN_VALVE);

    // CLOSE 2 and 4
    vTaskDelayMS(3000);
    flowRate[2].set(CLOSE_VALVE);
    flowRate[4].set(CLOSE_VALVE);

    vTaskDelayMS(1000); // wait until they open

    flowRate[2].detach();
    flowRate[4].detach();

    isIgnitionSequenceRunning = false;
    DEBUG("IGNITION ABORTED");

    vTaskDelete(NULL);
}

// ================================================================
// ========================= END OF TASKS =========================
// ================================================================

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

    server->on("/testServos", HTTP_GET, [](AsyncWebServerRequest *request)
               {
                   DEBUG("Testing servos...");

                   xTaskCreate(testServosTask,
                               "testServosTask",
                               10000,
                               NULL,
                               1,
                               NULL);

                   request->send(200, "Testing servos...");
                   //
               });

    server->on("/abort", HTTP_GET, [](AsyncWebServerRequest *request)
               {
                   DEBUG("Aborting ignition sequence...");

                   vTaskSuspend(ignitionSequenceHandle);

                   // abort sequence
                   xTaskCreate(abortSequenceTask,
                               "abortSequenceTask",
                               10000,
                               NULL,
                               1,
                               NULL);

                   request->send(200, "Aborted...");
                   //
               });
}

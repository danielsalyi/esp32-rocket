#include "sequences/sequences.h"
#include <Arduino.h>
#include <flowrate/flowrate.h>
#include "flashWriter/flashWriter.h"
#include "pressureSensor/pressureSensor.h"
#include "flowrate/flowrate.h"
#include "loadcell/loadcell.h"

bool arm = false;

Sequences::Sequences()
{
    arm = false;
}

void Sequences::armSequence()
{
    arm = true;
}

void Sequences::disarmSequence()
{
    arm = false;
}

void Sequences::launchSequence()
{
    if(arm == true)
    {
        return;
    }


    // flowRate.set(90);
    // vTaskDelay(1000 / portTICK_PERIOD_MS);
    

}

void Sequences::abortSequence()
{
    // do something
}

void readSensors(sensorReadings& readings) {
    // read the pressure sensors
    for (int i = 0; i < numPressureSensors; i++) {
        readings.pressureSensorReadings[i] = PressureSensors[i].read();
    }
    // read the load cell
    readings.loadCellReading = loadCell.read();
}
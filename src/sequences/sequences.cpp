#include "sequences/sequences.h"
#include <Arduino.h>
#include <flowrate/flowrate.h>

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


    flowRate.set(90);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    

}

void Sequences::abortSequence()
{
    // do something
}


#ifndef SEQUENCES_H
#define SEQUENCES_H
#include "flashWriter/flashWriter.h"
#include "pressureSensor/pressureSensor.h"
#include "flowrate/flowrate.h"
#include "loadcell/loadcell.h"

class Sequences
{
    private:
    bool arm;

    public:
    Sequences();

    void armSequence();
    void disarmSequence();

    void launchSequence();
    void abortSequence();
};

Sequences extern sequences;

void readSensors(sensorReadings& readings);


#endif
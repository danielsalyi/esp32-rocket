#include <sensors/sensors.h>
#include "pressureSensor/pressureSensor.h"
#include "loadcell/loadcell.h"

LoadCell loadCell(11);

PressureSensor press_1(12);
PressureSensor press_2(11);
PressureSensor press_3(13);

void initSensors()
{
    press_1.begin();
    press_2.begin();
    press_3.begin();

    loadCell.begin();
}

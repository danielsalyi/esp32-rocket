#include <Arduino.h>
#include <loadcell/loadcell.h>
#include <HX711.h>
#include <configs.h>

LoadCell loadCell[2] = {LoadCell(), LoadCell()};

LoadCell::LoadCell()
{
}

uint16_t LoadCell::read()
{
    return scale.get_units(10);
}

void LoadCell::setup(int LOADCELL_DT, int LOADCELL_SCK)
{
    scale.begin(LOADCELL_DT, LOADCELL_SCK);

    // it will be "ready" even if its not connected so idk
    if (scale.is_ready())
    {
        DEBUG("Scale is ready");
        scale.set_scale(CALIBRATION_FACTOR); // calibrating
        scale.tare();                        // tare
    }
    else
    {
        DEBUG("Scale is not ready");
    }
}

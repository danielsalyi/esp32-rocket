#include <Arduino.h>
#include <loadcell/loadcell.h>
#include <HX711.h>
#include <configs.h>

LoadCell loadCell;

LoadCell::LoadCell()
{
}

uint16_t LoadCell::read()
{
    return scale.get_units(10);
}

void LoadCell::setup()
{
    scale.begin(LOADCELL_DT, LOADCELL_SCK);

    // it will be "ready" even if its not connected so idk
    if(scale.is_ready())
    {
        scale.set_scale();
        Serial0.println("Scale is ready");
    }
    else
    {
        Serial0.println("Scale is not ready");
    }

    scale.tare(10); // calibration
}

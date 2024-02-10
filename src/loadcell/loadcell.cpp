#include <Arduino.h>
#include <loadcell/loadcell.h>
#include <HX711.h>
#include <configs.h>

LoadCell loadCell;

HX711 scale;

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

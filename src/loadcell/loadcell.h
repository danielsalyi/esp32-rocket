#ifndef LOADCELL_H
#define LOADCELL_H

#include "HX711.h"

class LoadCell {

public:
    LoadCell();

    void setup();
    uint16_t read();

private:
    HX711 scale;
};

extern LoadCell loadCell;

#endif
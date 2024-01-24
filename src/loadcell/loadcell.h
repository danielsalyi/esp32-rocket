#ifndef LOADCELL_H
#define LOADCELL_H

class LoadCell {

public:
    LoadCell();

    void setup();
    uint16_t read();

private:
    int pin;
};

extern LoadCell loadCell;

#endif
#ifndef LED_H
#define LED_H

#include "Adafruit_NeoPixel.h"
#include "configs.h"

class LED{
    public:
        LED();
        void set(int r, int g, int b);
        void setup();
};

extern LED led; // make it global

#endif // LED_H
#include <Adafruit_NeoPixel.h>
#include "config/config.h"

Adafruit_NeoPixel WS2812B(1, LED_PIN, NEO_GRB + NEO_KHZ800);

void initLED()
{
    WS2812B.begin();
    WS2812B.setPixelColor(0, WS2812B.Color(100, 100, 100));
    WS2812B.setBrightness(50);
}

void setLED(int r, int g, int b)
{
    WS2812B.setPixelColor(0, WS2812B.Color(r, g, b));
}

void showLED()
{
    WS2812B.show();
}

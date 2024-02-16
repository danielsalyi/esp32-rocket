#include <led/led.h>
#include <configs.h>
#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel WS2812B(1, LED_PIN, NEO_GRB + NEO_KHZ800); // Spent hours making this private, just let this be

LED led; // initialize as global led object

void LED::setup()
{
    WS2812B.begin();
    set(255, 255, 255);
}

void LED::set(int r, int g, int b)
{
    WS2812B.setPixelColor(0, WS2812B.Color(r, g, b));
    WS2812B.show();
}


LED::LED() {
}

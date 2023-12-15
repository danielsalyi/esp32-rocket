#include <Adafruit_NeoPixel.h>
#include <utils/configs.h>

Adafruit_NeoPixel WS2812B(1, LED_PIN, NEO_GRB + NEO_KHZ800);

void setLED(int r, int g, int b)
{
    WS2812B.setPixelColor(0, WS2812B.Color(r, g, b));
    WS2812B.show();
}

void initLED()
{
    WS2812B.begin();
    WS2812B.setBrightness(LED_BRIGHTNESS);
    setLED(255, 255, 255);
}

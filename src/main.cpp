#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <FS.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

#define LED_PIN 38

const char *ssid = "PIT-Y29ZHR0ZJA7";
const char *password = "PMOLN9609FY";

Adafruit_NeoPixel WS2812B(1, LED_PIN, NEO_GRB + NEO_KHZ800);
AsyncWebServer server(80);

void setup()
{
    Serial0.begin(115200);

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial0.println("Connecting to WiFi..");
    }

    // Print ESP Local IP Address
    Serial0.println(WiFi.localIP());

    // Route for root / web page
    server.on("/fish", HTTP_GET, [](AsyncWebServerRequest *request)
              {
        request->send_P(200, "text/plain", "ok");
            WS2812B.setPixelColor(0, WS2812B.Color(100, 0, 0));
            WS2812B.show(); });

    server.on("/food", HTTP_GET, [](AsyncWebServerRequest *request)
              {
        request->send_P(200, "text/plain", "ok");
        WS2812B.setPixelColor(0, WS2812B.Color(0, 100, 0));
        WS2812B.show(); });

    server.begin();
    WS2812B.begin();
    WS2812B.setPixelColor(0, WS2812B.Color(100, 100, 100));
    WS2812B.setBrightness(10);
    WS2812B.show();
}

void loop()
{
    WS2812B.show();
}

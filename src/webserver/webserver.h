#ifndef ESP_WEBSERVER_H
#define ESP_WEBSERVER_H
#include "flashWriter/flashWriter.h"
#include <ESPAsyncWebServer.h>

class Webserver
{
public:
    Webserver();
    void setup();

private:
    void initWebserver();
    void createEndpoints();
    void createWifiConnection();
};

extern Webserver webserver;

#endif
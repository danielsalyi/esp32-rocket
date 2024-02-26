#ifndef ESP_WEBSERVER_H
#define ESP_WEBSERVER_H
#include "flashWriter/flashWriter.h"
#include <ESPAsyncWebServer.h>

class Webserver{
    public:
        Webserver();
        void setup();
    
    private:
        void initWebserver();
        void createEndpoints();
        void createWifiConnection();
        void createFlashWriterEndpoints();
        void createSequenceEndpoints();
};
template<typename Func>
void sendResponse(AsyncWebServerRequest *request, Func func);


extern Webserver webserver;

#endif
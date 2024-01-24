#ifndef WEBSERVER_H
#define WEBSERVER_H

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

extern Webserver webserver;

#endif
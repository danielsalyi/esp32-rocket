#ifndef LED_H
#define LED_H

class LED{
    public:
        LED();
        void set(int r, int g, int b);
        void setup();
};

extern LED led; // make it global

#endif // LED_H
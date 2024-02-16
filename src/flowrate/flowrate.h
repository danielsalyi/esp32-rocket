#ifndef FLOWRATE_H_
#define FLOWRATE_H_

#include <ESP32Servo.h>

class FlowRate {
  private:
    Servo servo;
  public:
    FlowRate();
    void setup();
    void set(int value);
    void set(int value, int speed);
    int read();

};

extern FlowRate flowRate[];

#endif /* FLOWRATE_H_ */


#ifndef FLOWRATE_H_
#define FLOWRATE_H_

#include <ESP32Servo.h>

class FlowRate
{
private:
  Servo servo;
  int pin;

public:
  FlowRate();
  void setup(int pin);
  void attach();
  void detach();
  void set(int value);
  void set(int value, int speed);
  int read();
  void test();
  void closeAll();
};

extern FlowRate flowRate[5];

#endif /* FLOWRATE_H_ */

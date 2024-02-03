#ifndef FLOWRATE_H_
#define FLOWRATE_H_


class FlowRate {
  public:
    FlowRate();
    void setup();
    void set(int value);
    void set(int value, int speed);
    void set(int start, int end, int speed);
    int read();

};

extern FlowRate flowRate;

#endif /* FLOWRATE_H_ */


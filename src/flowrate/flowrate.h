#ifndef FLOWRATE_H_
#define FLOWRATE_H_


class FlowRate {
  public:
    FlowRate();
    void setup();
    void set(int value);
    int read();

};

extern FlowRate flowRate;

#endif /* FLOWRATE_H_ */


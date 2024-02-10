#ifndef FLASH_WRITER_H
#define FLASH_WRITER_H
#include <cstdint> 

#define FORMAT_LITTLEFS_IF_FAILED true
// https://randomnerdtutorials.com/esp32-write-data-littlefs-arduino/

struct sensorReadings {
  uint16_t pressureSensor1;
  uint16_t pressureSensor2;
  uint16_t pressureSensor3;
  uint16_t loadCellReading;
  int flowRateReading;
};

class FlashWriter {
  public:
    FlashWriter();
    void setup();
    void write(const char *message);
    void writeSensors(const sensorReadings &readings);
    void flush();
  private:
    void initLogger();
    void appendToFile(const char *message);
    void flushFile();
};

extern FlashWriter flashWriter; // make it global

#endif // FLASH_WRITER_H

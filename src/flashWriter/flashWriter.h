#ifndef FLASH_WRITER_H
#define FLASH_WRITER_H
#include <cstdint> 
#define FORMAT_LITTLEFS_IF_FAILED true

#include "FS.h"

// https://randomnerdtutorials.com/esp32-write-data-littlefs-arduino/

#define numPressureSensors 3

struct sensorReadings {
  uint16_t pressureSensorReadings[numPressureSensors];
  uint16_t loadCellReading;
};

class FlashWriter {
  public:
    FlashWriter();
    void setup();
    void append(const char *message);
    void appendSensorData(struct SensorData *sensorData);
    String pathToFile();
    void flush();
  private:
    File file;
    void initLogger();
    void appendToFile(const char *message);
    void flushFile();
};

extern FlashWriter flashWriter; // make it global

#endif // FLASH_WRITER_H

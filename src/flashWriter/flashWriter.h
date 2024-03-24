#ifndef FLASH_WRITER_H
#define FLASH_WRITER_H
#include <cstdint>
#define FORMAT_LITTLEFS_IF_FAILED true

#define PAGE_SIZE 516

#include "FS.h"

// https://randomnerdtutorials.com/esp32-write-data-littlefs-arduino/

#define numPressureSensors 3

struct sensorReadings
{
  uint16_t pressureSensor1;
  uint16_t pressureSensor2;
  uint16_t loadCellReading;
};

class FlashWriter
{
public:
  FlashWriter();
  void setup();
  void append(const char *message);
  void appendSensorData(struct sensorReadings *sensorReadings);
  String pathToFile();
  void flush();

private:
  File file;
  int counter;
  void initLogger();
  void appendToFile(const char *message);
  void flushFile();
};

extern FlashWriter flashWriter; // make it global

#endif // FLASH_WRITER_H

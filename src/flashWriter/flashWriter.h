#ifndef FLASH_WRITER_H
#define FLASH_WRITER_H

#define FORMAT_LITTLEFS_IF_FAILED true

#include <LittleFS.h>

// https://randomnerdtutorials.com/esp32-write-data-littlefs-arduino/


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
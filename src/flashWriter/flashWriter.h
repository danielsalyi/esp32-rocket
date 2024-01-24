#ifndef FLASH_WRITER_H
#define FLASH_WRITER_H

#define FORMAT_LITTLEFS_IF_FAILED true
// https://randomnerdtutorials.com/esp32-write-data-littlefs-arduino/


class FlashWriter {
  public:
    FlashWriter();
    void setup();
    void write(const char *message);
    void flush();
  private:
    void initLogger();
    void appendToFile(const char *message);
    void flushFile();
};

extern FlashWriter flashWriter; // make it global

#endif // FLASH_WRITER_H
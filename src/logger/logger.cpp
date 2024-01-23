#include "FS.h"
#include <LittleFS.h>
#include <logger/logger.h>

#define FORMAT_LITTLEFS_IF_FAILED true

// https://randomnerdtutorials.com/esp32-write-data-littlefs-arduino/

File file;

void initLogger()
{
    if (!LittleFS.begin(FORMAT_LITTLEFS_IF_FAILED))
    {
        Serial0.println("LittleFS Mount Failed");
        return;
    }

    file = LittleFS.open("/data1.csv", FILE_APPEND, true);
}

void appendToFile(const char *message)
{
    unsigned long start = micros();
    file.print(message);
    unsigned long delta = micros() - start;
    Serial0.print("write time - ");
    Serial0.println(delta);
}

void flushFile()
{
    unsigned long start = micros();
    file.flush();
    unsigned long delta = micros() - start;
    Serial0.print("flush time - ");
    Serial0.println(delta);
}

#include "FS.h"
#include <LittleFS.h>
#include <flashWriter/flashWriter.h>
#include <configs.h>

File file;
FlashWriter flashWriter; // singleton

FlashWriter::FlashWriter()
{
    // cannot call setup here, it will crash it
}

// public
void FlashWriter::setup()
{
    initLogger();
}

void FlashWriter::write(const char *message)
{
    // maybe some logs around here
    appendToFile(message);
    
    // other logs
}

void FlashWriter::write(const sensorReadings &s) 
{
    appendToFile(reinterpret_cast<const char*>(&s));
}

void FlashWriter::flush()
{
    // maybe some logs around here
    flushFile();

    // other logs
}


// private
void FlashWriter::initLogger()
{
    if (!LittleFS.begin(FORMAT_LITTLEFS_IF_FAILED))
    {
        Serial0.println("LittleFS Mount Failed");
        return;
    }

    file = LittleFS.open("/data1.csv", FILE_APPEND, true);
}

void FlashWriter::appendToFile(const char *message)
{
    unsigned long start = micros();
    file.print(message);
    unsigned long delta = micros() - start;
    Serial0.print("write time - ");
    Serial0.println(delta);
}

void FlashWriter::flushFile()
{
    unsigned long start = micros();
    file.flush();
    unsigned long delta = micros() - start;
    Serial0.print("flush time - ");
    Serial0.println(delta);
}

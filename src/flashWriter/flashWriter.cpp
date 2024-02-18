#include "FS.h"
#include <LittleFS.h>
#include <flashWriter/flashWriter.h>
#include <configs.h>

FlashWriter flashWriter; // singleton

FlashWriter::FlashWriter()
{
    file = File();
}

void FlashWriter::setup()
{
    initLogger();
}

void FlashWriter::append(const char *message)
{
    appendToFile(message);
}

void FlashWriter::flush()
{
    flushFile();
}

String FlashWriter::pathToFile()
{
    return file.path();
}

void FlashWriter::appendSensorData(struct SensorData *sensorData)
{

    // here u need some counter to keep track of the number of data points

    // package it
    // appendToFile(sensorData);

    // if counter reached, flush?
}

// =================== private===================

void FlashWriter::initLogger()
{
    if (!LittleFS.begin(FORMAT_LITTLEFS_IF_FAILED))
    {
        DEBUG("LittleFS Mount Failed - Formatting after restart...");
        return;
    }

    // Create a new file to write the data everytime
    for (int i = 0;; i++)
    {
        if (LittleFS.exists("/data" + String(i) + ".csv")) // exists will throw an error, but u can just ignore it probably
        {
            // file exists, just continue
            continue;
        }

        // file does not exist, create it
        DEBUG("Creating new file...");
        file = LittleFS.open("/data" + String(i) + ".csv", FILE_APPEND, true);
        DEBUG_F("File opened %s\n", file.name());
        break;
    }

    // idk why but works with the API but not with serial xd
    String message = "VERIFY WRITE for file: " + String(file.path()) + "\n";
    append(message.c_str());
    flush(); // if u dont flush, it wont write to the file :'D
}

void FlashWriter::appendToFile(const char *message)
{
    unsigned long start = micros();
    file.print(message);
    unsigned long delta = micros() - start;
    DEBUG_F("Write time: %u \n", delta);
}

void FlashWriter::flushFile()
{
    unsigned long start = micros();
    file.flush();
    unsigned long delta = micros() - start;
    DEBUG_F("Flush time: %u \n", delta);
}

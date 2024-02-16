#include "FS.h"
#include <LittleFS.h>
#include <flashWriter/flashWriter.h>
#include <configs.h>

FlashWriter flashWriter; // singleton

FlashWriter::FlashWriter()
{
    file = File();
    counter = 0;
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

void FlashWriter::appendSensorData(struct sensorReadings *sensorReadings)
{

    // here u need some counter to keep track of the number of data points

    // package it
    if (!sensorReadings) return;

    // Append pressure sensor readings
    String dataString = "Pressure sensor readings: ";
    for (int i = 0; i < numPressureSensors; ++i) {
        dataString += String(sensorReadings->pressureSensorReadings[i]);
        if (i < numPressureSensors - 1) {
            dataString += ", "; 
        }
    }

    // Append load cell reading
    dataString += ",\n load cell reading: " + String(sensorReadings->loadCellReading) + "\n";

    appendToFile(dataString.c_str());
    counter += sizeof(dataString.c_str());

    // if counter reached, flush?
    if (counter >= PAGE_SIZE) flush();
}



// =================== private===================

void FlashWriter::initLogger()
{
    if (!LittleFS.begin(FORMAT_LITTLEFS_IF_FAILED))
    {
        Serial0.println("LittleFS Mount Failed");
        return;
    }

    // Create a new file to write the data everytime
    for(int i = 0; ; i++)
    {
        if(LittleFS.exists("/data" + String(i) + ".csv")) // exists will throw an error, but u can just ignore it probably
        {
            // file exists, just continue
            continue;
        }

        // file does not exist, create it
        Serial0.println("Creating new file...");
        file = LittleFS.open("/data" + String(i) + ".csv", FILE_APPEND, true);
        Serial0.printf("File opened %s\n", file.name());
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

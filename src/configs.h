#ifndef CONFIGS_H
#define CONFIGS_H

// CONTENT: Configurations for the project
// ===============================================

// ============== Passwords and SSID =============
#define SSID_WIFI "PIT-Y29ZHR0ZJA7"
#define PASSWORD_WIFI "PMOLN9609FY"

// ============== LOGGING CONFIGURATIONS =============
#define BAUD_RATE 115200

#define DEBUG_LVL 1

#if DEBUG_LVL
#define DEBUG(...) Serial0.println(__VA_ARGS__)
#define DEBUG_F(...) Serial0.printf(__VA_ARGS__)
#else
#define DEBUG(...)
#define DEBUG_F(...)
#endif

// ===============================================
// ============== PIN CONFIGURATIONS =============
// ===============================================

#define LED_PIN 38

// Pressure sensors
#define PRESS_SENSOR_0 15
#define PRESS_SENSOR_1 7
#define PRESS_SENSOR_2 6

// Flowrate sensors
#define FLOWRATE_PIN_0 16
#define FLOWRATE_PIN_1 17
#define FLOWRATE_PIN_2 18
#define FLOWRATE_PIN_3 8
#define FLOWRATE_PIN_4 3

// Load cell0
#define LOADCELL_DT_0 4
#define LOADCELL_SCK_0 5

// Load cell1
#define LOADCELL_DT_1 46
#define LOADCELL_SCK_1 9

// relay - GPIO
#define IGNITER_PIN 48 // RELAY_PIN_0 is the pin for the igniter
#define RELAY_PIN_1 47
#define RELAY_PIN_2 21
#define RELAY_PIN_3 14

#endif
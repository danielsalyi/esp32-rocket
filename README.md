# esp32-rocket

## Parts in the cirtcuit:
pinout: https://docs.google.com/spreadsheets/d/1gh6bkqz8IQwBzecCjn6oTz4n6H4Um9rVM5zOhNv6iq0/edit#gid=0

- Esp32
- Relay 
    - 3 valves
    - Ignition 
- 2 Load cells
- Servo (flowrate)
<!-- - Big Button -->
- 3 Pressure sensor

## Modules to implement
- Esp32 
    - Communication [x]
    - Data storage [x]
- Firing sequence [ ]
    - Ignition [ ]
    - Arming [ ]
- Relay Board [x]
- Load cells [ ]
- Pressure sensors [ ]
- 1 servo (flow rate) [ ]

## Things to consider 
- For the datastorage 
    - consider sampling rate (50ms?)
    - size of 1 package: 32 + 16bit x 5 = 14 bytes
        - time (32 bit)
        - 3 pressure
        - 1-2 load


https://docs.espressif.com/projects/esp-idf/en/latest/esp32s3/api-reference/system/freertos_idf.html#critical-sections

https://microcontrollerslab.com/arduino-freertos-structure-queue-receive-data-multiple-resources/
https://forums.freertos.org/t/usage-of-freertos-in-a-simple-data-logging-communication-system/12115/13
https://www.freertos.org/FreeRTOS_Support_Forum_Archive/December_2014/freertos_Passing_elements_to_task_for_writing_SD_Card_dba9ba27j.html
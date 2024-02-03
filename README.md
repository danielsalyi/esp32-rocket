# esp32-rocket

Welcome to our repository!

If you are stuck, ask somebody more experienced in the team. But do not worry, you are safe to play around, as its impossible to break anything. If you made changes in the code, tests are running automatically to maintain the quality, and you cannot merge bad code. Additionally, we are reviewing your code before merging.

## Getting started

1. Clone the repository 
2. Create a new branch
3. Check Todo List https://github.com/users/danielsalyi/projects/2
4. Start working

You are also free to add libaries to a reasonable extent.

## Parts in the cirtcuit:

- Esp32
- Relay 
    - 3 valves
    - Ignition 
- 2 Load cells
- Servo (flowrate)
<!-- - Big Button -->
- 3 Pressure sensor

pinout: https://docs.google.com/spreadsheets/d/1gh6bkqz8IQwBzecCjn6oTz4n6H4Um9rVM5zOhNv6iq0/edit#gid=0

## Modules to implement
- Esp32 
    - Communication [x]
    - Data storage [x]
- Firing sequence [ ]
    - Ignition [ ]
    - Arming [ ]
- Pressure Valves [x]
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

some links:
https://docs.espressif.com/projects/esp-idf/en/latest/esp32s3/api-reference/system/freertos_idf.html#critical-sections

https://microcontrollerslab.com/arduino-freertos-structure-queue-receive-data-multiple-resources/
https://forums.freertos.org/t/usage-of-freertos-in-a-simple-data-logging-communication-system/12115/13
https://www.freertos.org/FreeRTOS_Support_Forum_Archive/December_2014/freertos_Passing_elements_to_task_for_writing_SD_Card_dba9ba27j.html


## Setting up environment:

### toolbar - nice to have
https://docs.platformio.org/en/stable/integration/ide/vscode.html#ide-vscode-settings

go to vscode settings -> platformio -> toolbar - settings.json

add somewhere between the where u want it: ( u can also edit it)
```
{
            "text": "$(arrow-up)",
            "tooltip": "PlatformIO: Remote Upload",
            "commands": [{
                "id": "platformio-ide.runPIOCoreCommand",
                "args": "pio remote run --target upload --environment ${command:platformio-ide.activeEnvironment}"
            }]
        },
        {
            "text": "$(plug)",
            "tooltip": "PlatformIO: Remote monitor",
            "commands": [{
                "id": "platformio-ide.runPIOCoreCommand",
                "args": "pio remote device monitor -b 115200"
            }]
        },
```


### pre and post scripts (for later)
https://docs.platformio.org/en/latest/scripting/actions.html
## Embedded System Course project based on STM32 and FreeRTOS 

>Prerequest: STM32CubeIDE, STM32CubeMX are installed

1. Here is group project for the course of embedded system design. 

2. The STM32 and FreeRTOS system initial configuration are fully based on STM32CubeMX.

3. In the FreeRTOS system of this project, we set up three tasks, which are responsible for DS18B20 and MPU6050 sensor data collection, sensor data is written to the external EEPROM 24CXX, and screen refresh to display data in real time respectively.

## Team Members
- **Zucheng Han** (Responsible for: STM32 peripheral settings, FreeRTOS system configuration and tasks allocation, sensor drivers migaration)
- **Tianshuai Chen** (Responsible for: embedded device testing, final report summarizing and writing)


## Reference
1. Some device(24CXX, DS18B20, MPU6050) drivers and microsecond delay configuration refer to the ALIENTEK official STM32 product drivers. https://github.com/alientek-openedv/Products 

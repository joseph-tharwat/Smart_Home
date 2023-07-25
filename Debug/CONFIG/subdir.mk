################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CONFIG/DIO_LCFG.c \
../CONFIG/ExEEPROM_LCFG.c \
../CONFIG/I2C_LCFG.c \
../CONFIG/KEYPAD_LCFG.c \
../CONFIG/LCD_LCFH.c \
../CONFIG/LED_LCFG.c \
../CONFIG/PORT_LCFG.c \
../CONFIG/UART_LCFG.c 

OBJS += \
./CONFIG/DIO_LCFG.o \
./CONFIG/ExEEPROM_LCFG.o \
./CONFIG/I2C_LCFG.o \
./CONFIG/KEYPAD_LCFG.o \
./CONFIG/LCD_LCFH.o \
./CONFIG/LED_LCFG.o \
./CONFIG/PORT_LCFG.o \
./CONFIG/UART_LCFG.o 

C_DEPS += \
./CONFIG/DIO_LCFG.d \
./CONFIG/ExEEPROM_LCFG.d \
./CONFIG/I2C_LCFG.d \
./CONFIG/KEYPAD_LCFG.d \
./CONFIG/LCD_LCFH.d \
./CONFIG/LED_LCFG.d \
./CONFIG/PORT_LCFG.d \
./CONFIG/UART_LCFG.d 


# Each subdirectory must supply rules for building sources it contributes
CONFIG/%.o: ../CONFIG/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"D:\Programe_Project\AVR\SmartHome_V2\APP" -I"D:\Programe_Project\AVR\SmartHome_V2\CONFIG" -I"D:\Programe_Project\AVR\SmartHome_V2\HAL" -I"D:\Programe_Project\AVR\SmartHome_V2\HAL\EXTERNAL_EEPROM" -I"D:\Programe_Project\AVR\SmartHome_V2\HAL\FINGER_PRINT" -I"D:\Programe_Project\AVR\SmartHome_V2\HAL\KEYPAD" -I"D:\Programe_Project\AVR\SmartHome_V2\HAL\LCD" -I"D:\Programe_Project\AVR\SmartHome_V2\HAL\LED" -I"D:\Programe_Project\AVR\SmartHome_V2\HAL\RTC" -I"D:\Programe_Project\AVR\SmartHome_V2\LIB" -I"D:\Programe_Project\AVR\SmartHome_V2\MCAL" -I"D:\Programe_Project\AVR\SmartHome_V2\MCAL\DIO" -I"D:\Programe_Project\AVR\SmartHome_V2\MCAL\GENERAL_INTERRUPT" -I"D:\Programe_Project\AVR\SmartHome_V2\MCAL\I2C" -I"D:\Programe_Project\AVR\SmartHome_V2\MCAL\PORT" -I"D:\Programe_Project\AVR\SmartHome_V2\MCAL\UART" -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



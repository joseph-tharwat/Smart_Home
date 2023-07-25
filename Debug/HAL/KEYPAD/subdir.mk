################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/KEYPAD/KEYPAD_PROG.c 

OBJS += \
./HAL/KEYPAD/KEYPAD_PROG.o 

C_DEPS += \
./HAL/KEYPAD/KEYPAD_PROG.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/KEYPAD/%.o: ../HAL/KEYPAD/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"D:\Programe_Project\AVR\SmartHome_V2\APP" -I"D:\Programe_Project\AVR\SmartHome_V2\CONFIG" -I"D:\Programe_Project\AVR\SmartHome_V2\HAL" -I"D:\Programe_Project\AVR\SmartHome_V2\HAL\EXTERNAL_EEPROM" -I"D:\Programe_Project\AVR\SmartHome_V2\HAL\FINGER_PRINT" -I"D:\Programe_Project\AVR\SmartHome_V2\HAL\KEYPAD" -I"D:\Programe_Project\AVR\SmartHome_V2\HAL\LCD" -I"D:\Programe_Project\AVR\SmartHome_V2\HAL\LED" -I"D:\Programe_Project\AVR\SmartHome_V2\HAL\RTC" -I"D:\Programe_Project\AVR\SmartHome_V2\LIB" -I"D:\Programe_Project\AVR\SmartHome_V2\MCAL" -I"D:\Programe_Project\AVR\SmartHome_V2\MCAL\DIO" -I"D:\Programe_Project\AVR\SmartHome_V2\MCAL\GENERAL_INTERRUPT" -I"D:\Programe_Project\AVR\SmartHome_V2\MCAL\I2C" -I"D:\Programe_Project\AVR\SmartHome_V2\MCAL\PORT" -I"D:\Programe_Project\AVR\SmartHome_V2\MCAL\UART" -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



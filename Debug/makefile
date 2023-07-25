################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include MCAL/UART/subdir.mk
-include MCAL/PORT/subdir.mk
-include MCAL/I2C/subdir.mk
-include MCAL/GENERAL_INTERRUPT/subdir.mk
-include MCAL/DIO/subdir.mk
-include HAL/RTC/subdir.mk
-include HAL/LED/subdir.mk
-include HAL/LCD/subdir.mk
-include HAL/KEYPAD/subdir.mk
-include HAL/FINGER_PRINT/subdir.mk
-include HAL/EXTERNAL_EEPROM/subdir.mk
-include CONFIG/subdir.mk
-include APP/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
SmartHome_V2.lss \

FLASH_IMAGE += \
SmartHome_V2.hex \

SIZEDUMMY += \
sizedummy \


# All Target
all: SmartHome_V2.elf secondary-outputs

# Tool invocations
SmartHome_V2.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,SmartHome_V2.map -mmcu=atmega32 -o "SmartHome_V2.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

SmartHome_V2.lss: SmartHome_V2.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S SmartHome_V2.elf  >"SmartHome_V2.lss"
	@echo 'Finished building: $@'
	@echo ' '

SmartHome_V2.hex: SmartHome_V2.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex SmartHome_V2.elf  "SmartHome_V2.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: SmartHome_V2.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 SmartHome_V2.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) SmartHome_V2.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

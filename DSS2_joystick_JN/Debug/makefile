################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Drivers/STM32L4xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include CANopenNode_STM32/subdir.mk
-include CANopenNode-master/storage/subdir.mk
-include CANopenNode-master/extra/subdir.mk
-include CANopenNode-master/309/subdir.mk
-include CANopenNode-master/305/subdir.mk
-include CANopenNode-master/304/subdir.mk
-include CANopenNode-master/303/subdir.mk
-include CANopenNode-master/301/subdir.mk
-include CANopenNode-master/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
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

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := DSS2_joystick_JN
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
DSS2_joystick_JN.elf \

MAP_FILES += \
DSS2_joystick_JN.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
DSS2_joystick_JN.list \


# All Target
all: main-build

# Main-build Target
main-build: DSS2_joystick_JN.elf secondary-outputs

# Tool invocations
DSS2_joystick_JN.elf DSS2_joystick_JN.map: $(OBJS) $(USER_OBJS) C:\Users\Public\STM32CubeIDE\workspace_1.18.1\DSS2_joystick_JN\STM32L432KCUX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "DSS2_joystick_JN.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"C:\Users\Public\STM32CubeIDE\workspace_1.18.1\DSS2_joystick_JN\STM32L432KCUX_FLASH.ld" --specs=nosys.specs -Wl,-Map="DSS2_joystick_JN.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

DSS2_joystick_JN.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "DSS2_joystick_JN.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) DSS2_joystick_JN.elf DSS2_joystick_JN.list DSS2_joystick_JN.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets

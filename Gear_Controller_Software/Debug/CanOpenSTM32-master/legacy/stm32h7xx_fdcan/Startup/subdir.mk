################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../CanOpenSTM32-master/legacy/stm32h7xx_fdcan/Startup/startup_stm32h735igkx.s 

OBJS += \
./CanOpenSTM32-master/legacy/stm32h7xx_fdcan/Startup/startup_stm32h735igkx.o 

S_DEPS += \
./CanOpenSTM32-master/legacy/stm32h7xx_fdcan/Startup/startup_stm32h735igkx.d 


# Each subdirectory must supply rules for building sources it contributes
CanOpenSTM32-master/legacy/stm32h7xx_fdcan/Startup/startup_stm32h735igkx.o: C:/Users/alessio.ciardo/Documents/GIT/DSS2/Joystick_Controller_Software/CanOpenSTM32-master/legacy/stm32h7xx_fdcan/Startup/startup_stm32h735igkx.s CanOpenSTM32-master/legacy/stm32h7xx_fdcan/Startup/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -DDEBUG -c -I"C:/Users/alessio.ciardo/Documents/GIT/DSS2/Joystick_Controller_Software/CanOpenSTM32-master/CANopenNode_STM32" -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

clean: clean-CanOpenSTM32-2d-master-2f-legacy-2f-stm32h7xx_fdcan-2f-Startup

clean-CanOpenSTM32-2d-master-2f-legacy-2f-stm32h7xx_fdcan-2f-Startup:
	-$(RM) ./CanOpenSTM32-master/legacy/stm32h7xx_fdcan/Startup/startup_stm32h735igkx.d ./CanOpenSTM32-master/legacy/stm32h7xx_fdcan/Startup/startup_stm32h735igkx.o

.PHONY: clean-CanOpenSTM32-2d-master-2f-legacy-2f-stm32h7xx_fdcan-2f-Startup


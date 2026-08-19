################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CanOpenSTM32-master/legacy/libs/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.c 

OBJS += \
./CanOpenSTM32-master/legacy/libs/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.o 

C_DEPS += \
./CanOpenSTM32-master/legacy/libs/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.d 


# Each subdirectory must supply rules for building sources it contributes
CanOpenSTM32-master/legacy/libs/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.o: C:/Users/alessio.ciardo/Documents/GIT/DSS2/Joystick_Controller_Software/CanOpenSTM32-master/legacy/libs/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.c CanOpenSTM32-master/legacy/libs/FreeRTOS/Source/portable/GCC/ARM_CM4F/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L432xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../PROJECT_LOC/CanOpenSTM32-master -I../PROJECT_LOC/CANopenNode-master -I"C:/Users/alessio.ciardo/Documents/GIT/DSS2/Joystick_Controller_Software/CanOpenSTM32-master/CANopenNode_STM32" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-CanOpenSTM32-2d-master-2f-legacy-2f-libs-2f-FreeRTOS-2f-Source-2f-portable-2f-GCC-2f-ARM_CM4F

clean-CanOpenSTM32-2d-master-2f-legacy-2f-libs-2f-FreeRTOS-2f-Source-2f-portable-2f-GCC-2f-ARM_CM4F:
	-$(RM) ./CanOpenSTM32-master/legacy/libs/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.cyclo ./CanOpenSTM32-master/legacy/libs/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.d ./CanOpenSTM32-master/legacy/libs/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.o ./CanOpenSTM32-master/legacy/libs/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.su

.PHONY: clean-CanOpenSTM32-2d-master-2f-legacy-2f-libs-2f-FreeRTOS-2f-Source-2f-portable-2f-GCC-2f-ARM_CM4F


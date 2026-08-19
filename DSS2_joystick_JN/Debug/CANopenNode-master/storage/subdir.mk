################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CANopenNode-master/storage/CO_storage.c \
../CANopenNode-master/storage/CO_storageEeprom.c 

OBJS += \
./CANopenNode-master/storage/CO_storage.o \
./CANopenNode-master/storage/CO_storageEeprom.o 

C_DEPS += \
./CANopenNode-master/storage/CO_storage.d \
./CANopenNode-master/storage/CO_storageEeprom.d 


# Each subdirectory must supply rules for building sources it contributes
CANopenNode-master/storage/%.o CANopenNode-master/storage/%.su CANopenNode-master/storage/%.cyclo: ../CANopenNode-master/storage/%.c CANopenNode-master/storage/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L432xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../CANopenNode-master -I../CANopenNode_STM32 -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-CANopenNode-2d-master-2f-storage

clean-CANopenNode-2d-master-2f-storage:
	-$(RM) ./CANopenNode-master/storage/CO_storage.cyclo ./CANopenNode-master/storage/CO_storage.d ./CANopenNode-master/storage/CO_storage.o ./CANopenNode-master/storage/CO_storage.su ./CANopenNode-master/storage/CO_storageEeprom.cyclo ./CANopenNode-master/storage/CO_storageEeprom.d ./CANopenNode-master/storage/CO_storageEeprom.o ./CANopenNode-master/storage/CO_storageEeprom.su

.PHONY: clean-CANopenNode-2d-master-2f-storage


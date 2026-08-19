################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CanOpenSTM32-master/legacy/stm32h7xx_fdcan/Src/main.c \
../CanOpenSTM32-master/legacy/stm32h7xx_fdcan/Src/stm32h7xx_it.c \
../CanOpenSTM32-master/legacy/stm32h7xx_fdcan/Src/syscalls.c \
../CanOpenSTM32-master/legacy/stm32h7xx_fdcan/Src/sysmem.c \
../CanOpenSTM32-master/legacy/stm32h7xx_fdcan/Src/system_stm32h7xx.c 

OBJS += \
./CanOpenSTM32-master/legacy/stm32h7xx_fdcan/Src/main.o \
./CanOpenSTM32-master/legacy/stm32h7xx_fdcan/Src/stm32h7xx_it.o \
./CanOpenSTM32-master/legacy/stm32h7xx_fdcan/Src/syscalls.o \
./CanOpenSTM32-master/legacy/stm32h7xx_fdcan/Src/sysmem.o \
./CanOpenSTM32-master/legacy/stm32h7xx_fdcan/Src/system_stm32h7xx.o 

C_DEPS += \
./CanOpenSTM32-master/legacy/stm32h7xx_fdcan/Src/main.d \
./CanOpenSTM32-master/legacy/stm32h7xx_fdcan/Src/stm32h7xx_it.d \
./CanOpenSTM32-master/legacy/stm32h7xx_fdcan/Src/syscalls.d \
./CanOpenSTM32-master/legacy/stm32h7xx_fdcan/Src/sysmem.d \
./CanOpenSTM32-master/legacy/stm32h7xx_fdcan/Src/system_stm32h7xx.d 


# Each subdirectory must supply rules for building sources it contributes
CanOpenSTM32-master/legacy/stm32h7xx_fdcan/Src/main.o: C:/Users/alessio.ciardo/Documents/GIT/DSS2/Joystick_Controller_Software/CanOpenSTM32-master/legacy/stm32h7xx_fdcan/Src/main.c CanOpenSTM32-master/legacy/stm32h7xx_fdcan/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L432xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../PROJECT_LOC/CanOpenSTM32-master -I../PROJECT_LOC/CANopenNode-master -I"C:/Users/alessio.ciardo/Documents/GIT/DSS2/Joystick_Controller_Software/CanOpenSTM32-master/CANopenNode_STM32" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
CanOpenSTM32-master/legacy/stm32h7xx_fdcan/Src/stm32h7xx_it.o: C:/Users/alessio.ciardo/Documents/GIT/DSS2/Joystick_Controller_Software/CanOpenSTM32-master/legacy/stm32h7xx_fdcan/Src/stm32h7xx_it.c CanOpenSTM32-master/legacy/stm32h7xx_fdcan/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L432xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../PROJECT_LOC/CanOpenSTM32-master -I../PROJECT_LOC/CANopenNode-master -I"C:/Users/alessio.ciardo/Documents/GIT/DSS2/Joystick_Controller_Software/CanOpenSTM32-master/CANopenNode_STM32" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
CanOpenSTM32-master/legacy/stm32h7xx_fdcan/Src/syscalls.o: C:/Users/alessio.ciardo/Documents/GIT/DSS2/Joystick_Controller_Software/CanOpenSTM32-master/legacy/stm32h7xx_fdcan/Src/syscalls.c CanOpenSTM32-master/legacy/stm32h7xx_fdcan/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L432xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../PROJECT_LOC/CanOpenSTM32-master -I../PROJECT_LOC/CANopenNode-master -I"C:/Users/alessio.ciardo/Documents/GIT/DSS2/Joystick_Controller_Software/CanOpenSTM32-master/CANopenNode_STM32" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
CanOpenSTM32-master/legacy/stm32h7xx_fdcan/Src/sysmem.o: C:/Users/alessio.ciardo/Documents/GIT/DSS2/Joystick_Controller_Software/CanOpenSTM32-master/legacy/stm32h7xx_fdcan/Src/sysmem.c CanOpenSTM32-master/legacy/stm32h7xx_fdcan/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L432xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../PROJECT_LOC/CanOpenSTM32-master -I../PROJECT_LOC/CANopenNode-master -I"C:/Users/alessio.ciardo/Documents/GIT/DSS2/Joystick_Controller_Software/CanOpenSTM32-master/CANopenNode_STM32" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
CanOpenSTM32-master/legacy/stm32h7xx_fdcan/Src/system_stm32h7xx.o: C:/Users/alessio.ciardo/Documents/GIT/DSS2/Joystick_Controller_Software/CanOpenSTM32-master/legacy/stm32h7xx_fdcan/Src/system_stm32h7xx.c CanOpenSTM32-master/legacy/stm32h7xx_fdcan/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L432xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../PROJECT_LOC/CanOpenSTM32-master -I../PROJECT_LOC/CANopenNode-master -I"C:/Users/alessio.ciardo/Documents/GIT/DSS2/Joystick_Controller_Software/CanOpenSTM32-master/CANopenNode_STM32" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-CanOpenSTM32-2d-master-2f-legacy-2f-stm32h7xx_fdcan-2f-Src

clean-CanOpenSTM32-2d-master-2f-legacy-2f-stm32h7xx_fdcan-2f-Src:
	-$(RM) ./CanOpenSTM32-master/legacy/stm32h7xx_fdcan/Src/main.cyclo ./CanOpenSTM32-master/legacy/stm32h7xx_fdcan/Src/main.d ./CanOpenSTM32-master/legacy/stm32h7xx_fdcan/Src/main.o ./CanOpenSTM32-master/legacy/stm32h7xx_fdcan/Src/main.su ./CanOpenSTM32-master/legacy/stm32h7xx_fdcan/Src/stm32h7xx_it.cyclo ./CanOpenSTM32-master/legacy/stm32h7xx_fdcan/Src/stm32h7xx_it.d ./CanOpenSTM32-master/legacy/stm32h7xx_fdcan/Src/stm32h7xx_it.o ./CanOpenSTM32-master/legacy/stm32h7xx_fdcan/Src/stm32h7xx_it.su ./CanOpenSTM32-master/legacy/stm32h7xx_fdcan/Src/syscalls.cyclo ./CanOpenSTM32-master/legacy/stm32h7xx_fdcan/Src/syscalls.d ./CanOpenSTM32-master/legacy/stm32h7xx_fdcan/Src/syscalls.o ./CanOpenSTM32-master/legacy/stm32h7xx_fdcan/Src/syscalls.su ./CanOpenSTM32-master/legacy/stm32h7xx_fdcan/Src/sysmem.cyclo ./CanOpenSTM32-master/legacy/stm32h7xx_fdcan/Src/sysmem.d ./CanOpenSTM32-master/legacy/stm32h7xx_fdcan/Src/sysmem.o ./CanOpenSTM32-master/legacy/stm32h7xx_fdcan/Src/sysmem.su ./CanOpenSTM32-master/legacy/stm32h7xx_fdcan/Src/system_stm32h7xx.cyclo ./CanOpenSTM32-master/legacy/stm32h7xx_fdcan/Src/system_stm32h7xx.d ./CanOpenSTM32-master/legacy/stm32h7xx_fdcan/Src/system_stm32h7xx.o ./CanOpenSTM32-master/legacy/stm32h7xx_fdcan/Src/system_stm32h7xx.su

.PHONY: clean-CanOpenSTM32-2d-master-2f-legacy-2f-stm32h7xx_fdcan-2f-Src


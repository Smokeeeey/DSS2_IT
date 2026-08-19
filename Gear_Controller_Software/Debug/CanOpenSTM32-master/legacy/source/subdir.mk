################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CanOpenSTM32-master/legacy/source/CO_driver_stm32h735g-dk.c \
../CanOpenSTM32-master/legacy/source/OD.c \
../CanOpenSTM32-master/legacy/source/comm_stm32h735g-dk.c 

OBJS += \
./CanOpenSTM32-master/legacy/source/CO_driver_stm32h735g-dk.o \
./CanOpenSTM32-master/legacy/source/OD.o \
./CanOpenSTM32-master/legacy/source/comm_stm32h735g-dk.o 

C_DEPS += \
./CanOpenSTM32-master/legacy/source/CO_driver_stm32h735g-dk.d \
./CanOpenSTM32-master/legacy/source/OD.d \
./CanOpenSTM32-master/legacy/source/comm_stm32h735g-dk.d 


# Each subdirectory must supply rules for building sources it contributes
CanOpenSTM32-master/legacy/source/CO_driver_stm32h735g-dk.o: C:/Users/alessio.ciardo/Documents/GIT/DSS2/Joystick_Controller_Software/CanOpenSTM32-master/legacy/source/CO_driver_stm32h735g-dk.c CanOpenSTM32-master/legacy/source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L432xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../PROJECT_LOC/CanOpenSTM32-master -I../PROJECT_LOC/CANopenNode-master -I"C:/Users/alessio.ciardo/Documents/GIT/DSS2/Joystick_Controller_Software/CanOpenSTM32-master/CANopenNode_STM32" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
CanOpenSTM32-master/legacy/source/OD.o: C:/Users/alessio.ciardo/Documents/GIT/DSS2/Joystick_Controller_Software/CanOpenSTM32-master/legacy/source/OD.c CanOpenSTM32-master/legacy/source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L432xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../PROJECT_LOC/CanOpenSTM32-master -I../PROJECT_LOC/CANopenNode-master -I"C:/Users/alessio.ciardo/Documents/GIT/DSS2/Joystick_Controller_Software/CanOpenSTM32-master/CANopenNode_STM32" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
CanOpenSTM32-master/legacy/source/comm_stm32h735g-dk.o: C:/Users/alessio.ciardo/Documents/GIT/DSS2/Joystick_Controller_Software/CanOpenSTM32-master/legacy/source/comm_stm32h735g-dk.c CanOpenSTM32-master/legacy/source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L432xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../PROJECT_LOC/CanOpenSTM32-master -I../PROJECT_LOC/CANopenNode-master -I"C:/Users/alessio.ciardo/Documents/GIT/DSS2/Joystick_Controller_Software/CanOpenSTM32-master/CANopenNode_STM32" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-CanOpenSTM32-2d-master-2f-legacy-2f-source

clean-CanOpenSTM32-2d-master-2f-legacy-2f-source:
	-$(RM) ./CanOpenSTM32-master/legacy/source/CO_driver_stm32h735g-dk.cyclo ./CanOpenSTM32-master/legacy/source/CO_driver_stm32h735g-dk.d ./CanOpenSTM32-master/legacy/source/CO_driver_stm32h735g-dk.o ./CanOpenSTM32-master/legacy/source/CO_driver_stm32h735g-dk.su ./CanOpenSTM32-master/legacy/source/OD.cyclo ./CanOpenSTM32-master/legacy/source/OD.d ./CanOpenSTM32-master/legacy/source/OD.o ./CanOpenSTM32-master/legacy/source/OD.su ./CanOpenSTM32-master/legacy/source/comm_stm32h735g-dk.cyclo ./CanOpenSTM32-master/legacy/source/comm_stm32h735g-dk.d ./CanOpenSTM32-master/legacy/source/comm_stm32h735g-dk.o ./CanOpenSTM32-master/legacy/source/comm_stm32h735g-dk.su

.PHONY: clean-CanOpenSTM32-2d-master-2f-legacy-2f-source


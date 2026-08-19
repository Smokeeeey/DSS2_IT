################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CanOpenSTM32-master/legacy/libs/FreeRTOS/Source/croutine.c \
../CanOpenSTM32-master/legacy/libs/FreeRTOS/Source/event_groups.c \
../CanOpenSTM32-master/legacy/libs/FreeRTOS/Source/list.c \
../CanOpenSTM32-master/legacy/libs/FreeRTOS/Source/queue.c \
../CanOpenSTM32-master/legacy/libs/FreeRTOS/Source/stream_buffer.c \
../CanOpenSTM32-master/legacy/libs/FreeRTOS/Source/tasks.c \
../CanOpenSTM32-master/legacy/libs/FreeRTOS/Source/timers.c 

OBJS += \
./CanOpenSTM32-master/legacy/libs/FreeRTOS/Source/croutine.o \
./CanOpenSTM32-master/legacy/libs/FreeRTOS/Source/event_groups.o \
./CanOpenSTM32-master/legacy/libs/FreeRTOS/Source/list.o \
./CanOpenSTM32-master/legacy/libs/FreeRTOS/Source/queue.o \
./CanOpenSTM32-master/legacy/libs/FreeRTOS/Source/stream_buffer.o \
./CanOpenSTM32-master/legacy/libs/FreeRTOS/Source/tasks.o \
./CanOpenSTM32-master/legacy/libs/FreeRTOS/Source/timers.o 

C_DEPS += \
./CanOpenSTM32-master/legacy/libs/FreeRTOS/Source/croutine.d \
./CanOpenSTM32-master/legacy/libs/FreeRTOS/Source/event_groups.d \
./CanOpenSTM32-master/legacy/libs/FreeRTOS/Source/list.d \
./CanOpenSTM32-master/legacy/libs/FreeRTOS/Source/queue.d \
./CanOpenSTM32-master/legacy/libs/FreeRTOS/Source/stream_buffer.d \
./CanOpenSTM32-master/legacy/libs/FreeRTOS/Source/tasks.d \
./CanOpenSTM32-master/legacy/libs/FreeRTOS/Source/timers.d 


# Each subdirectory must supply rules for building sources it contributes
CanOpenSTM32-master/legacy/libs/FreeRTOS/Source/croutine.o: C:/Users/alessio.ciardo/Documents/GIT/DSS2/Joystick_Controller_Software/CanOpenSTM32-master/legacy/libs/FreeRTOS/Source/croutine.c CanOpenSTM32-master/legacy/libs/FreeRTOS/Source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L432xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../PROJECT_LOC/CanOpenSTM32-master -I../PROJECT_LOC/CANopenNode-master -I"C:/Users/alessio.ciardo/Documents/GIT/DSS2/Joystick_Controller_Software/CanOpenSTM32-master/CANopenNode_STM32" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
CanOpenSTM32-master/legacy/libs/FreeRTOS/Source/event_groups.o: C:/Users/alessio.ciardo/Documents/GIT/DSS2/Joystick_Controller_Software/CanOpenSTM32-master/legacy/libs/FreeRTOS/Source/event_groups.c CanOpenSTM32-master/legacy/libs/FreeRTOS/Source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L432xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../PROJECT_LOC/CanOpenSTM32-master -I../PROJECT_LOC/CANopenNode-master -I"C:/Users/alessio.ciardo/Documents/GIT/DSS2/Joystick_Controller_Software/CanOpenSTM32-master/CANopenNode_STM32" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
CanOpenSTM32-master/legacy/libs/FreeRTOS/Source/list.o: C:/Users/alessio.ciardo/Documents/GIT/DSS2/Joystick_Controller_Software/CanOpenSTM32-master/legacy/libs/FreeRTOS/Source/list.c CanOpenSTM32-master/legacy/libs/FreeRTOS/Source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L432xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../PROJECT_LOC/CanOpenSTM32-master -I../PROJECT_LOC/CANopenNode-master -I"C:/Users/alessio.ciardo/Documents/GIT/DSS2/Joystick_Controller_Software/CanOpenSTM32-master/CANopenNode_STM32" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
CanOpenSTM32-master/legacy/libs/FreeRTOS/Source/queue.o: C:/Users/alessio.ciardo/Documents/GIT/DSS2/Joystick_Controller_Software/CanOpenSTM32-master/legacy/libs/FreeRTOS/Source/queue.c CanOpenSTM32-master/legacy/libs/FreeRTOS/Source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L432xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../PROJECT_LOC/CanOpenSTM32-master -I../PROJECT_LOC/CANopenNode-master -I"C:/Users/alessio.ciardo/Documents/GIT/DSS2/Joystick_Controller_Software/CanOpenSTM32-master/CANopenNode_STM32" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
CanOpenSTM32-master/legacy/libs/FreeRTOS/Source/stream_buffer.o: C:/Users/alessio.ciardo/Documents/GIT/DSS2/Joystick_Controller_Software/CanOpenSTM32-master/legacy/libs/FreeRTOS/Source/stream_buffer.c CanOpenSTM32-master/legacy/libs/FreeRTOS/Source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L432xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../PROJECT_LOC/CanOpenSTM32-master -I../PROJECT_LOC/CANopenNode-master -I"C:/Users/alessio.ciardo/Documents/GIT/DSS2/Joystick_Controller_Software/CanOpenSTM32-master/CANopenNode_STM32" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
CanOpenSTM32-master/legacy/libs/FreeRTOS/Source/tasks.o: C:/Users/alessio.ciardo/Documents/GIT/DSS2/Joystick_Controller_Software/CanOpenSTM32-master/legacy/libs/FreeRTOS/Source/tasks.c CanOpenSTM32-master/legacy/libs/FreeRTOS/Source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L432xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../PROJECT_LOC/CanOpenSTM32-master -I../PROJECT_LOC/CANopenNode-master -I"C:/Users/alessio.ciardo/Documents/GIT/DSS2/Joystick_Controller_Software/CanOpenSTM32-master/CANopenNode_STM32" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
CanOpenSTM32-master/legacy/libs/FreeRTOS/Source/timers.o: C:/Users/alessio.ciardo/Documents/GIT/DSS2/Joystick_Controller_Software/CanOpenSTM32-master/legacy/libs/FreeRTOS/Source/timers.c CanOpenSTM32-master/legacy/libs/FreeRTOS/Source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L432xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../PROJECT_LOC/CanOpenSTM32-master -I../PROJECT_LOC/CANopenNode-master -I"C:/Users/alessio.ciardo/Documents/GIT/DSS2/Joystick_Controller_Software/CanOpenSTM32-master/CANopenNode_STM32" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-CanOpenSTM32-2d-master-2f-legacy-2f-libs-2f-FreeRTOS-2f-Source

clean-CanOpenSTM32-2d-master-2f-legacy-2f-libs-2f-FreeRTOS-2f-Source:
	-$(RM) ./CanOpenSTM32-master/legacy/libs/FreeRTOS/Source/croutine.cyclo ./CanOpenSTM32-master/legacy/libs/FreeRTOS/Source/croutine.d ./CanOpenSTM32-master/legacy/libs/FreeRTOS/Source/croutine.o ./CanOpenSTM32-master/legacy/libs/FreeRTOS/Source/croutine.su ./CanOpenSTM32-master/legacy/libs/FreeRTOS/Source/event_groups.cyclo ./CanOpenSTM32-master/legacy/libs/FreeRTOS/Source/event_groups.d ./CanOpenSTM32-master/legacy/libs/FreeRTOS/Source/event_groups.o ./CanOpenSTM32-master/legacy/libs/FreeRTOS/Source/event_groups.su ./CanOpenSTM32-master/legacy/libs/FreeRTOS/Source/list.cyclo ./CanOpenSTM32-master/legacy/libs/FreeRTOS/Source/list.d ./CanOpenSTM32-master/legacy/libs/FreeRTOS/Source/list.o ./CanOpenSTM32-master/legacy/libs/FreeRTOS/Source/list.su ./CanOpenSTM32-master/legacy/libs/FreeRTOS/Source/queue.cyclo ./CanOpenSTM32-master/legacy/libs/FreeRTOS/Source/queue.d ./CanOpenSTM32-master/legacy/libs/FreeRTOS/Source/queue.o ./CanOpenSTM32-master/legacy/libs/FreeRTOS/Source/queue.su ./CanOpenSTM32-master/legacy/libs/FreeRTOS/Source/stream_buffer.cyclo ./CanOpenSTM32-master/legacy/libs/FreeRTOS/Source/stream_buffer.d ./CanOpenSTM32-master/legacy/libs/FreeRTOS/Source/stream_buffer.o ./CanOpenSTM32-master/legacy/libs/FreeRTOS/Source/stream_buffer.su ./CanOpenSTM32-master/legacy/libs/FreeRTOS/Source/tasks.cyclo ./CanOpenSTM32-master/legacy/libs/FreeRTOS/Source/tasks.d ./CanOpenSTM32-master/legacy/libs/FreeRTOS/Source/tasks.o ./CanOpenSTM32-master/legacy/libs/FreeRTOS/Source/tasks.su ./CanOpenSTM32-master/legacy/libs/FreeRTOS/Source/timers.cyclo ./CanOpenSTM32-master/legacy/libs/FreeRTOS/Source/timers.d ./CanOpenSTM32-master/legacy/libs/FreeRTOS/Source/timers.o ./CanOpenSTM32-master/legacy/libs/FreeRTOS/Source/timers.su

.PHONY: clean-CanOpenSTM32-2d-master-2f-legacy-2f-libs-2f-FreeRTOS-2f-Source


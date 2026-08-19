################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CANopenNode-master/301/CO_Emergency.c \
../CANopenNode-master/301/CO_HBconsumer.c \
../CANopenNode-master/301/CO_NMT_Heartbeat.c \
../CANopenNode-master/301/CO_Node_Guarding.c \
../CANopenNode-master/301/CO_ODinterface.c \
../CANopenNode-master/301/CO_PDO.c \
../CANopenNode-master/301/CO_SDOclient.c \
../CANopenNode-master/301/CO_SDOserver.c \
../CANopenNode-master/301/CO_SYNC.c \
../CANopenNode-master/301/CO_TIME.c \
../CANopenNode-master/301/CO_fifo.c \
../CANopenNode-master/301/crc16-ccitt.c 

OBJS += \
./CANopenNode-master/301/CO_Emergency.o \
./CANopenNode-master/301/CO_HBconsumer.o \
./CANopenNode-master/301/CO_NMT_Heartbeat.o \
./CANopenNode-master/301/CO_Node_Guarding.o \
./CANopenNode-master/301/CO_ODinterface.o \
./CANopenNode-master/301/CO_PDO.o \
./CANopenNode-master/301/CO_SDOclient.o \
./CANopenNode-master/301/CO_SDOserver.o \
./CANopenNode-master/301/CO_SYNC.o \
./CANopenNode-master/301/CO_TIME.o \
./CANopenNode-master/301/CO_fifo.o \
./CANopenNode-master/301/crc16-ccitt.o 

C_DEPS += \
./CANopenNode-master/301/CO_Emergency.d \
./CANopenNode-master/301/CO_HBconsumer.d \
./CANopenNode-master/301/CO_NMT_Heartbeat.d \
./CANopenNode-master/301/CO_Node_Guarding.d \
./CANopenNode-master/301/CO_ODinterface.d \
./CANopenNode-master/301/CO_PDO.d \
./CANopenNode-master/301/CO_SDOclient.d \
./CANopenNode-master/301/CO_SDOserver.d \
./CANopenNode-master/301/CO_SYNC.d \
./CANopenNode-master/301/CO_TIME.d \
./CANopenNode-master/301/CO_fifo.d \
./CANopenNode-master/301/crc16-ccitt.d 


# Each subdirectory must supply rules for building sources it contributes
CANopenNode-master/301/CO_Emergency.o: C:/Users/alessio.ciardo/Documents/GIT/DSS2/Joystick_Controller_Software/CANopenNode-master/301/CO_Emergency.c CANopenNode-master/301/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L432xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../PROJECT_LOC/CanOpenSTM32-master -I../PROJECT_LOC/CANopenNode-master -I"C:/Users/alessio.ciardo/Documents/GIT/DSS2/Joystick_Controller_Software/CanOpenSTM32-master/CANopenNode_STM32" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
CANopenNode-master/301/CO_HBconsumer.o: C:/Users/alessio.ciardo/Documents/GIT/DSS2/Joystick_Controller_Software/CANopenNode-master/301/CO_HBconsumer.c CANopenNode-master/301/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L432xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../PROJECT_LOC/CanOpenSTM32-master -I../PROJECT_LOC/CANopenNode-master -I"C:/Users/alessio.ciardo/Documents/GIT/DSS2/Joystick_Controller_Software/CanOpenSTM32-master/CANopenNode_STM32" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
CANopenNode-master/301/CO_NMT_Heartbeat.o: C:/Users/alessio.ciardo/Documents/GIT/DSS2/Joystick_Controller_Software/CANopenNode-master/301/CO_NMT_Heartbeat.c CANopenNode-master/301/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L432xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../PROJECT_LOC/CanOpenSTM32-master -I../PROJECT_LOC/CANopenNode-master -I"C:/Users/alessio.ciardo/Documents/GIT/DSS2/Joystick_Controller_Software/CanOpenSTM32-master/CANopenNode_STM32" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
CANopenNode-master/301/CO_Node_Guarding.o: C:/Users/alessio.ciardo/Documents/GIT/DSS2/Joystick_Controller_Software/CANopenNode-master/301/CO_Node_Guarding.c CANopenNode-master/301/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L432xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../PROJECT_LOC/CanOpenSTM32-master -I../PROJECT_LOC/CANopenNode-master -I"C:/Users/alessio.ciardo/Documents/GIT/DSS2/Joystick_Controller_Software/CanOpenSTM32-master/CANopenNode_STM32" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
CANopenNode-master/301/CO_ODinterface.o: C:/Users/alessio.ciardo/Documents/GIT/DSS2/Joystick_Controller_Software/CANopenNode-master/301/CO_ODinterface.c CANopenNode-master/301/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L432xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../PROJECT_LOC/CanOpenSTM32-master -I../PROJECT_LOC/CANopenNode-master -I"C:/Users/alessio.ciardo/Documents/GIT/DSS2/Joystick_Controller_Software/CanOpenSTM32-master/CANopenNode_STM32" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
CANopenNode-master/301/CO_PDO.o: C:/Users/alessio.ciardo/Documents/GIT/DSS2/Joystick_Controller_Software/CANopenNode-master/301/CO_PDO.c CANopenNode-master/301/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L432xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../PROJECT_LOC/CanOpenSTM32-master -I../PROJECT_LOC/CANopenNode-master -I"C:/Users/alessio.ciardo/Documents/GIT/DSS2/Joystick_Controller_Software/CanOpenSTM32-master/CANopenNode_STM32" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
CANopenNode-master/301/CO_SDOclient.o: C:/Users/alessio.ciardo/Documents/GIT/DSS2/Joystick_Controller_Software/CANopenNode-master/301/CO_SDOclient.c CANopenNode-master/301/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L432xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../PROJECT_LOC/CanOpenSTM32-master -I../PROJECT_LOC/CANopenNode-master -I"C:/Users/alessio.ciardo/Documents/GIT/DSS2/Joystick_Controller_Software/CanOpenSTM32-master/CANopenNode_STM32" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
CANopenNode-master/301/CO_SDOserver.o: C:/Users/alessio.ciardo/Documents/GIT/DSS2/Joystick_Controller_Software/CANopenNode-master/301/CO_SDOserver.c CANopenNode-master/301/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L432xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../PROJECT_LOC/CanOpenSTM32-master -I../PROJECT_LOC/CANopenNode-master -I"C:/Users/alessio.ciardo/Documents/GIT/DSS2/Joystick_Controller_Software/CanOpenSTM32-master/CANopenNode_STM32" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
CANopenNode-master/301/CO_SYNC.o: C:/Users/alessio.ciardo/Documents/GIT/DSS2/Joystick_Controller_Software/CANopenNode-master/301/CO_SYNC.c CANopenNode-master/301/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L432xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../PROJECT_LOC/CanOpenSTM32-master -I../PROJECT_LOC/CANopenNode-master -I"C:/Users/alessio.ciardo/Documents/GIT/DSS2/Joystick_Controller_Software/CanOpenSTM32-master/CANopenNode_STM32" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
CANopenNode-master/301/CO_TIME.o: C:/Users/alessio.ciardo/Documents/GIT/DSS2/Joystick_Controller_Software/CANopenNode-master/301/CO_TIME.c CANopenNode-master/301/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L432xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../PROJECT_LOC/CanOpenSTM32-master -I../PROJECT_LOC/CANopenNode-master -I"C:/Users/alessio.ciardo/Documents/GIT/DSS2/Joystick_Controller_Software/CanOpenSTM32-master/CANopenNode_STM32" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
CANopenNode-master/301/CO_fifo.o: C:/Users/alessio.ciardo/Documents/GIT/DSS2/Joystick_Controller_Software/CANopenNode-master/301/CO_fifo.c CANopenNode-master/301/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L432xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../PROJECT_LOC/CanOpenSTM32-master -I../PROJECT_LOC/CANopenNode-master -I"C:/Users/alessio.ciardo/Documents/GIT/DSS2/Joystick_Controller_Software/CanOpenSTM32-master/CANopenNode_STM32" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
CANopenNode-master/301/crc16-ccitt.o: C:/Users/alessio.ciardo/Documents/GIT/DSS2/Joystick_Controller_Software/CANopenNode-master/301/crc16-ccitt.c CANopenNode-master/301/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L432xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../PROJECT_LOC/CanOpenSTM32-master -I../PROJECT_LOC/CANopenNode-master -I"C:/Users/alessio.ciardo/Documents/GIT/DSS2/Joystick_Controller_Software/CanOpenSTM32-master/CANopenNode_STM32" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-CANopenNode-2d-master-2f-301

clean-CANopenNode-2d-master-2f-301:
	-$(RM) ./CANopenNode-master/301/CO_Emergency.cyclo ./CANopenNode-master/301/CO_Emergency.d ./CANopenNode-master/301/CO_Emergency.o ./CANopenNode-master/301/CO_Emergency.su ./CANopenNode-master/301/CO_HBconsumer.cyclo ./CANopenNode-master/301/CO_HBconsumer.d ./CANopenNode-master/301/CO_HBconsumer.o ./CANopenNode-master/301/CO_HBconsumer.su ./CANopenNode-master/301/CO_NMT_Heartbeat.cyclo ./CANopenNode-master/301/CO_NMT_Heartbeat.d ./CANopenNode-master/301/CO_NMT_Heartbeat.o ./CANopenNode-master/301/CO_NMT_Heartbeat.su ./CANopenNode-master/301/CO_Node_Guarding.cyclo ./CANopenNode-master/301/CO_Node_Guarding.d ./CANopenNode-master/301/CO_Node_Guarding.o ./CANopenNode-master/301/CO_Node_Guarding.su ./CANopenNode-master/301/CO_ODinterface.cyclo ./CANopenNode-master/301/CO_ODinterface.d ./CANopenNode-master/301/CO_ODinterface.o ./CANopenNode-master/301/CO_ODinterface.su ./CANopenNode-master/301/CO_PDO.cyclo ./CANopenNode-master/301/CO_PDO.d ./CANopenNode-master/301/CO_PDO.o ./CANopenNode-master/301/CO_PDO.su ./CANopenNode-master/301/CO_SDOclient.cyclo ./CANopenNode-master/301/CO_SDOclient.d ./CANopenNode-master/301/CO_SDOclient.o ./CANopenNode-master/301/CO_SDOclient.su ./CANopenNode-master/301/CO_SDOserver.cyclo ./CANopenNode-master/301/CO_SDOserver.d ./CANopenNode-master/301/CO_SDOserver.o ./CANopenNode-master/301/CO_SDOserver.su ./CANopenNode-master/301/CO_SYNC.cyclo ./CANopenNode-master/301/CO_SYNC.d ./CANopenNode-master/301/CO_SYNC.o ./CANopenNode-master/301/CO_SYNC.su ./CANopenNode-master/301/CO_TIME.cyclo ./CANopenNode-master/301/CO_TIME.d ./CANopenNode-master/301/CO_TIME.o ./CANopenNode-master/301/CO_TIME.su ./CANopenNode-master/301/CO_fifo.cyclo ./CANopenNode-master/301/CO_fifo.d ./CANopenNode-master/301/CO_fifo.o ./CANopenNode-master/301/CO_fifo.su ./CANopenNode-master/301/crc16-ccitt.cyclo ./CANopenNode-master/301/crc16-ccitt.d ./CANopenNode-master/301/crc16-ccitt.o ./CANopenNode-master/301/crc16-ccitt.su

.PHONY: clean-CANopenNode-2d-master-2f-301


################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CANopenNode-master/304/CO_GFC.c \
../CANopenNode-master/304/CO_SRDO.c 

OBJS += \
./CANopenNode-master/304/CO_GFC.o \
./CANopenNode-master/304/CO_SRDO.o 

C_DEPS += \
./CANopenNode-master/304/CO_GFC.d \
./CANopenNode-master/304/CO_SRDO.d 


# Each subdirectory must supply rules for building sources it contributes
CANopenNode-master/304/CO_GFC.o: C:/Users/alessio.ciardo/Documents/GIT/DSS2/Joystick_Controller_Software/CANopenNode-master/304/CO_GFC.c CANopenNode-master/304/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L432xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../PROJECT_LOC/CanOpenSTM32-master -I../PROJECT_LOC/CANopenNode-master -I"C:/Users/alessio.ciardo/Documents/GIT/DSS2/Joystick_Controller_Software/CanOpenSTM32-master/CANopenNode_STM32" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
CANopenNode-master/304/CO_SRDO.o: C:/Users/alessio.ciardo/Documents/GIT/DSS2/Joystick_Controller_Software/CANopenNode-master/304/CO_SRDO.c CANopenNode-master/304/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L432xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../PROJECT_LOC/CanOpenSTM32-master -I../PROJECT_LOC/CANopenNode-master -I"C:/Users/alessio.ciardo/Documents/GIT/DSS2/Joystick_Controller_Software/CanOpenSTM32-master/CANopenNode_STM32" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-CANopenNode-2d-master-2f-304

clean-CANopenNode-2d-master-2f-304:
	-$(RM) ./CANopenNode-master/304/CO_GFC.cyclo ./CANopenNode-master/304/CO_GFC.d ./CANopenNode-master/304/CO_GFC.o ./CANopenNode-master/304/CO_GFC.su ./CANopenNode-master/304/CO_SRDO.cyclo ./CANopenNode-master/304/CO_SRDO.d ./CANopenNode-master/304/CO_SRDO.o ./CANopenNode-master/304/CO_SRDO.su

.PHONY: clean-CANopenNode-2d-master-2f-304


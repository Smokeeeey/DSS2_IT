################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CANopenNode-master/extra/CO_trace.c 

OBJS += \
./CANopenNode-master/extra/CO_trace.o 

C_DEPS += \
./CANopenNode-master/extra/CO_trace.d 


# Each subdirectory must supply rules for building sources it contributes
CANopenNode-master/extra/CO_trace.o: C:/Users/alessio.ciardo/Documents/GIT/DSS2/Joystick_Controller_Software/CANopenNode-master/extra/CO_trace.c CANopenNode-master/extra/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L432xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../PROJECT_LOC/CanOpenSTM32-master -I../PROJECT_LOC/CANopenNode-master -I"C:/Users/alessio.ciardo/Documents/GIT/DSS2/Joystick_Controller_Software/CanOpenSTM32-master/CANopenNode_STM32" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-CANopenNode-2d-master-2f-extra

clean-CANopenNode-2d-master-2f-extra:
	-$(RM) ./CANopenNode-master/extra/CO_trace.cyclo ./CANopenNode-master/extra/CO_trace.d ./CANopenNode-master/extra/CO_trace.o ./CANopenNode-master/extra/CO_trace.su

.PHONY: clean-CANopenNode-2d-master-2f-extra


################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CANopenNode-master/309/CO_gateway_ascii.c 

OBJS += \
./CANopenNode-master/309/CO_gateway_ascii.o 

C_DEPS += \
./CANopenNode-master/309/CO_gateway_ascii.d 


# Each subdirectory must supply rules for building sources it contributes
CANopenNode-master/309/%.o CANopenNode-master/309/%.su CANopenNode-master/309/%.cyclo: ../CANopenNode-master/309/%.c CANopenNode-master/309/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L432xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../CANopenNode-master -I../CANopenNode_STM32 -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-CANopenNode-2d-master-2f-309

clean-CANopenNode-2d-master-2f-309:
	-$(RM) ./CANopenNode-master/309/CO_gateway_ascii.cyclo ./CANopenNode-master/309/CO_gateway_ascii.d ./CANopenNode-master/309/CO_gateway_ascii.o ./CANopenNode-master/309/CO_gateway_ascii.su

.PHONY: clean-CANopenNode-2d-master-2f-309


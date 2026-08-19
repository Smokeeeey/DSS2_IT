################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CANopenNode-master/305/CO_LSSmaster.c \
../CANopenNode-master/305/CO_LSSslave.c 

OBJS += \
./CANopenNode-master/305/CO_LSSmaster.o \
./CANopenNode-master/305/CO_LSSslave.o 

C_DEPS += \
./CANopenNode-master/305/CO_LSSmaster.d \
./CANopenNode-master/305/CO_LSSslave.d 


# Each subdirectory must supply rules for building sources it contributes
CANopenNode-master/305/%.o CANopenNode-master/305/%.su CANopenNode-master/305/%.cyclo: ../CANopenNode-master/305/%.c CANopenNode-master/305/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L432xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../CANopenNode-master -I../CANopenNode_STM32 -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-CANopenNode-2d-master-2f-305

clean-CANopenNode-2d-master-2f-305:
	-$(RM) ./CANopenNode-master/305/CO_LSSmaster.cyclo ./CANopenNode-master/305/CO_LSSmaster.d ./CANopenNode-master/305/CO_LSSmaster.o ./CANopenNode-master/305/CO_LSSmaster.su ./CANopenNode-master/305/CO_LSSslave.cyclo ./CANopenNode-master/305/CO_LSSslave.d ./CANopenNode-master/305/CO_LSSslave.o ./CANopenNode-master/305/CO_LSSslave.su

.PHONY: clean-CANopenNode-2d-master-2f-305


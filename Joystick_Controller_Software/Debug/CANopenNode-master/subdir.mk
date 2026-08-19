################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CANopenNode-master/CANopen.c 

OBJS += \
./CANopenNode-master/CANopen.o 

C_DEPS += \
./CANopenNode-master/CANopen.d 


# Each subdirectory must supply rules for building sources it contributes
CANopenNode-master/CANopen.o: C:/Users/alessio.ciardo/Documents/GIT/DSS2/Joystick_Controller_Software/CANopenNode-master/CANopen.c CANopenNode-master/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L432xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../PROJECT_LOC/CanOpenSTM32-master -I../PROJECT_LOC/CANopenNode-master -I"C:/Users/alessio.ciardo/Documents/GIT/DSS2/Joystick_Controller_Software/CanOpenSTM32-master/CANopenNode_STM32" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-CANopenNode-2d-master

clean-CANopenNode-2d-master:
	-$(RM) ./CANopenNode-master/CANopen.cyclo ./CANopenNode-master/CANopen.d ./CANopenNode-master/CANopen.o ./CANopenNode-master/CANopen.su

.PHONY: clean-CANopenNode-2d-master


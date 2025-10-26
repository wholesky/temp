################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/mydocument/mylib/mystmlib/c/sys/mystrop.c 

OBJS += \
./sys/mystrop.o 

C_DEPS += \
./sys/mystrop.d 


# Each subdirectory must supply rules for building sources it contributes
sys/mystrop.o: D:/mydocument/mylib/mystmlib/c/sys/mystrop.c sys/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"D:/mydocument/mylib/mystmlib/c/sys" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-sys

clean-sys:
	-$(RM) ./sys/mystrop.cyclo ./sys/mystrop.d ./sys/mystrop.o ./sys/mystrop.su

.PHONY: clean-sys


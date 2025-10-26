################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/hhSerial/hhSerial.c 

OBJS += \
./Core/hhSerial/hhSerial.o 

C_DEPS += \
./Core/hhSerial/hhSerial.d 


# Each subdirectory must supply rules for building sources it contributes
Core/hhSerial/%.o Core/hhSerial/%.su Core/hhSerial/%.cyclo: ../Core/hhSerial/%.c Core/hhSerial/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"D:/mydocument/mylib/mystmlib/c/sys" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-hhSerial

clean-Core-2f-hhSerial:
	-$(RM) ./Core/hhSerial/hhSerial.cyclo ./Core/hhSerial/hhSerial.d ./Core/hhSerial/hhSerial.o ./Core/hhSerial/hhSerial.su

.PHONY: clean-Core-2f-hhSerial


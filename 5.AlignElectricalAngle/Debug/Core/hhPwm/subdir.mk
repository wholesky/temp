################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/hhPwm/hhPwm.c 

OBJS += \
./Core/hhPwm/hhPwm.o 

C_DEPS += \
./Core/hhPwm/hhPwm.d 


# Each subdirectory must supply rules for building sources it contributes
Core/hhPwm/%.o Core/hhPwm/%.su Core/hhPwm/%.cyclo: ../Core/hhPwm/%.c Core/hhPwm/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-hhPwm

clean-Core-2f-hhPwm:
	-$(RM) ./Core/hhPwm/hhPwm.cyclo ./Core/hhPwm/hhPwm.d ./Core/hhPwm/hhPwm.o ./Core/hhPwm/hhPwm.su

.PHONY: clean-Core-2f-hhPwm


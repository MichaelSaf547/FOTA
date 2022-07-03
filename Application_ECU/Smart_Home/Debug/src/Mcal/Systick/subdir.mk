################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Mcal/Systick/Systick.c \
../src/Mcal/Systick/Systick_cfg.c \
../src/Mcal/Systick/Systick_prv.c 

OBJS += \
./src/Mcal/Systick/Systick.o \
./src/Mcal/Systick/Systick_cfg.o \
./src/Mcal/Systick/Systick_prv.o 

C_DEPS += \
./src/Mcal/Systick/Systick.d \
./src/Mcal/Systick/Systick_cfg.d \
./src/Mcal/Systick/Systick_prv.d 


# Each subdirectory must supply rules for building sources it contributes
src/Mcal/Systick/%.o: ../src/Mcal/Systick/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Arm Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DUSE_FULL_ASSERT -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -DSTM32F401xC -DUSE_HAL_DRIVER -DHSE_VALUE=25000000 -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f4-hal" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



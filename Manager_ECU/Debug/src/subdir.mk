################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/App.c \
../src/DMA.c \
../src/ESP_program.c \
../src/Gpio.c \
../src/Nvic.c \
../src/RCC.c \
../src/UART_program.c \
../src/Usart.c \
../src/main.c 

OBJS += \
./src/App.o \
./src/DMA.o \
./src/ESP_program.o \
./src/Gpio.o \
./src/Nvic.o \
./src/RCC.o \
./src/UART_program.o \
./src/Usart.o \
./src/main.o 

C_DEPS += \
./src/App.d \
./src/DMA.d \
./src/ESP_program.d \
./src/Gpio.d \
./src/Nvic.d \
./src/RCC.d \
./src/UART_program.d \
./src/Usart.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Arm Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DUSE_FULL_ASSERT -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -DSTM32F401xC -DUSE_HAL_DRIVER -DHSE_VALUE=25000000 -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f4-hal" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



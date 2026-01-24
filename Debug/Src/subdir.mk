################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/adc.c \
../Src/clock.c \
../Src/controller.c \
../Src/fpu.c \
../Src/gpio.c \
../Src/iwdg.c \
../Src/main.c \
../Src/pwm.c \
../Src/syscalls.c \
../Src/sysmem.c \
../Src/systick.c \
../Src/timer.c 

OBJS += \
./Src/adc.o \
./Src/clock.o \
./Src/controller.o \
./Src/fpu.o \
./Src/gpio.o \
./Src/iwdg.o \
./Src/main.o \
./Src/pwm.o \
./Src/syscalls.o \
./Src/sysmem.o \
./Src/systick.o \
./Src/timer.o 

C_DEPS += \
./Src/adc.d \
./Src/clock.d \
./Src/controller.d \
./Src/fpu.d \
./Src/gpio.d \
./Src/iwdg.d \
./Src/main.d \
./Src/pwm.d \
./Src/syscalls.d \
./Src/sysmem.d \
./Src/systick.d \
./Src/timer.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F411RETx -DSTM32F411xE -c -I../Inc -I"C:/Users/hgholab/OneDrive/Source Code/Embedded Systems/Modules/forward_converter_controller/chip_headers/CMSIS/Include" -I"C:/Users/hgholab/OneDrive/Source Code/Embedded Systems/Modules/forward_converter_controller/chip_headers/CMSIS/Device/ST/STM32F4xx/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/adc.cyclo ./Src/adc.d ./Src/adc.o ./Src/adc.su ./Src/clock.cyclo ./Src/clock.d ./Src/clock.o ./Src/clock.su ./Src/controller.cyclo ./Src/controller.d ./Src/controller.o ./Src/controller.su ./Src/fpu.cyclo ./Src/fpu.d ./Src/fpu.o ./Src/fpu.su ./Src/gpio.cyclo ./Src/gpio.d ./Src/gpio.o ./Src/gpio.su ./Src/iwdg.cyclo ./Src/iwdg.d ./Src/iwdg.o ./Src/iwdg.su ./Src/main.cyclo ./Src/main.d ./Src/main.o ./Src/main.su ./Src/pwm.cyclo ./Src/pwm.d ./Src/pwm.o ./Src/pwm.su ./Src/syscalls.cyclo ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.cyclo ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su ./Src/systick.cyclo ./Src/systick.d ./Src/systick.o ./Src/systick.su ./Src/timer.cyclo ./Src/timer.d ./Src/timer.o ./Src/timer.su

.PHONY: clean-Src


################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ADC.c \
../PWM.c \
../gpio.c \
../lcd.c \
../lm35.c \
../motor.c \
../project.c 

OBJS += \
./ADC.o \
./PWM.o \
./gpio.o \
./lcd.o \
./lm35.o \
./motor.o \
./project.o 

C_DEPS += \
./ADC.d \
./PWM.d \
./gpio.d \
./lcd.d \
./lm35.d \
./motor.d \
./project.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



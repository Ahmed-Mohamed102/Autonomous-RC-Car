################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ANALOG_program.c \
../CLCD_program.c \
../DIO_program.c \
../EEPROM_program.c \
../EXTI_program.c \
../GI_program.c \
../SERVO_program.c \
../TIMER0_program.c \
../TIMER1_program.c \
../TIMER2_program.c \
../TWI_program.c \
../UART_program.c \
../US_program.c \
../main.c 

OBJS += \
./ANALOG_program.o \
./CLCD_program.o \
./DIO_program.o \
./EEPROM_program.o \
./EXTI_program.o \
./GI_program.o \
./SERVO_program.o \
./TIMER0_program.o \
./TIMER1_program.o \
./TIMER2_program.o \
./TWI_program.o \
./UART_program.o \
./US_program.o \
./main.o 

C_DEPS += \
./ANALOG_program.d \
./CLCD_program.d \
./DIO_program.d \
./EEPROM_program.d \
./EXTI_program.d \
./GI_program.d \
./SERVO_program.d \
./TIMER0_program.d \
./TIMER1_program.d \
./TIMER2_program.d \
./TWI_program.d \
./UART_program.d \
./US_program.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



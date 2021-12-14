################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/accelerometer.c \
../source/cbfifo.c \
../source/command_process.c \
../source/i2c.c \
../source/led.c \
../source/line_accumulate.c \
../source/main.c \
../source/mtb.c \
../source/semihost_hardfault.c \
../source/sysclock.c \
../source/systick.c \
../source/test_modules.c \
../source/touch.c \
../source/uart.c 

OBJS += \
./source/accelerometer.o \
./source/cbfifo.o \
./source/command_process.o \
./source/i2c.o \
./source/led.o \
./source/line_accumulate.o \
./source/main.o \
./source/mtb.o \
./source/semihost_hardfault.o \
./source/sysclock.o \
./source/systick.o \
./source/test_modules.o \
./source/touch.o \
./source/uart.o 

C_DEPS += \
./source/accelerometer.d \
./source/cbfifo.d \
./source/command_process.d \
./source/i2c.d \
./source/led.d \
./source/line_accumulate.d \
./source/main.d \
./source/mtb.d \
./source/semihost_hardfault.d \
./source/sysclock.d \
./source/systick.d \
./source/test_modules.d \
./source/touch.d \
./source/uart.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MKL25Z128VLK4 -DCPU_MKL25Z128VLK4_cm0plus -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\tanma\Documents\MCUXpressoIDE_11.2.0_4120\workspace\ECEN5813-Course-Project\board" -I"C:\Users\tanma\Documents\MCUXpressoIDE_11.2.0_4120\workspace\ECEN5813-Course-Project\source" -I"C:\Users\tanma\Documents\MCUXpressoIDE_11.2.0_4120\workspace\ECEN5813-Course-Project" -I"C:\Users\tanma\Documents\MCUXpressoIDE_11.2.0_4120\workspace\ECEN5813-Course-Project\drivers" -I"C:\Users\tanma\Documents\MCUXpressoIDE_11.2.0_4120\workspace\ECEN5813-Course-Project\CMSIS" -I"C:\Users\tanma\Documents\MCUXpressoIDE_11.2.0_4120\workspace\ECEN5813-Course-Project\utilities" -I"C:\Users\tanma\Documents\MCUXpressoIDE_11.2.0_4120\workspace\ECEN5813-Course-Project\startup" -O0 -fno-common -g3 -Wall -Werror -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



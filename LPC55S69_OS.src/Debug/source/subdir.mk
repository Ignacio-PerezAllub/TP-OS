################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/main.c \
../source/oslib.c \
../source/semihost_hardfault.c 

C_DEPS += \
./source/main.d \
./source/oslib.d \
./source/semihost_hardfault.d 

OBJS += \
./source/main.o \
./source/oslib.o \
./source/semihost_hardfault.o 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_LPC55S69JBD100 -DCPU_LPC55S69JBD100_cm33 -DCPU_LPC55S69JBD100_cm33_core0 -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DSERIAL_PORT_TYPE_UART=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__NEWLIB__ -I"D:\Users\Nacho\Documentos\FACULTAD\ENIB\SEN\OS\LPC55S69_OS.src\drivers" -I"D:\Users\Nacho\Documentos\FACULTAD\ENIB\SEN\OS\LPC55S69_OS.src\LPC55S69\drivers" -I"D:\Users\Nacho\Documentos\FACULTAD\ENIB\SEN\OS\LPC55S69_OS.src\utilities" -I"D:\Users\Nacho\Documentos\FACULTAD\ENIB\SEN\OS\LPC55S69_OS.src\component\uart" -I"D:\Users\Nacho\Documentos\FACULTAD\ENIB\SEN\OS\LPC55S69_OS.src\component\serial_manager" -I"D:\Users\Nacho\Documentos\FACULTAD\ENIB\SEN\OS\LPC55S69_OS.src\component\lists" -I"D:\Users\Nacho\Documentos\FACULTAD\ENIB\SEN\OS\LPC55S69_OS.src\CMSIS" -I"D:\Users\Nacho\Documentos\FACULTAD\ENIB\SEN\OS\LPC55S69_OS.src\device" -I"D:\Users\Nacho\Documentos\FACULTAD\ENIB\SEN\OS\LPC55S69_OS.src\board" -I"D:\Users\Nacho\Documentos\FACULTAD\ENIB\SEN\OS\LPC55S69_OS.src\source" -I"D:\Users\Nacho\Documentos\FACULTAD\ENIB\SEN\OS\LPC55S69_OS.src\drivers" -I"D:\Users\Nacho\Documentos\FACULTAD\ENIB\SEN\OS\LPC55S69_OS.src\LPC55S69\drivers" -I"D:\Users\Nacho\Documentos\FACULTAD\ENIB\SEN\OS\LPC55S69_OS.src\utilities" -I"D:\Users\Nacho\Documentos\FACULTAD\ENIB\SEN\OS\LPC55S69_OS.src\component\uart" -I"D:\Users\Nacho\Documentos\FACULTAD\ENIB\SEN\OS\LPC55S69_OS.src\component\serial_manager" -I"D:\Users\Nacho\Documentos\FACULTAD\ENIB\SEN\OS\LPC55S69_OS.src\component\lists" -I"D:\Users\Nacho\Documentos\FACULTAD\ENIB\SEN\OS\LPC55S69_OS.src\startup" -I"D:\Users\Nacho\Documentos\FACULTAD\ENIB\SEN\OS\LPC55S69_OS.src\CMSIS" -I"D:\Users\Nacho\Documentos\FACULTAD\ENIB\SEN\OS\LPC55S69_OS.src\device" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m33 -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -D__NEWLIB__ -fstack-usage -specs=nano.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-source

clean-source:
	-$(RM) ./source/main.d ./source/main.o ./source/oslib.d ./source/oslib.o ./source/semihost_hardfault.d ./source/semihost_hardfault.o

.PHONY: clean-source


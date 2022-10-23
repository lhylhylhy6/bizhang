################################################################################
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../applications/car.c \
../applications/car_pwm.c \
../applications/hcsr04.c \
../applications/main.c \
../applications/mpu6050.c \
../applications/pid.c \
../applications/uart2.c 

OBJS += \
./applications/car.o \
./applications/car_pwm.o \
./applications/hcsr04.o \
./applications/main.o \
./applications/mpu6050.o \
./applications/pid.o \
./applications/uart2.o 

C_DEPS += \
./applications/car.d \
./applications/car_pwm.d \
./applications/hcsr04.d \
./applications/main.d \
./applications/mpu6050.d \
./applications/pid.d \
./applications/uart2.d 


# Each subdirectory must supply rules for building sources it contributes
applications/%.o: ../applications/%.c
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -ffunction-sections -fdata-sections -Wall  -g -gdwarf-2 -DSOC_FAMILY_STM32 -DSOC_SERIES_STM32F4 -DUSE_HAL_DRIVER -DSTM32F407xx -I"C:\Users\10091\Desktop\1\bizhang\drivers" -I"C:\Users\10091\Desktop\1\bizhang\eMPL" -I"C:\Users\10091\Desktop\1\bizhang\drivers\include" -I"C:\Users\10091\Desktop\1\bizhang\drivers\include\config" -I"C:\Users\10091\Desktop\1\bizhang\libraries\CMSIS\Device\ST\STM32F4xx\Include" -I"C:\Users\10091\Desktop\1\bizhang\libraries\CMSIS\Include" -I"C:\Users\10091\Desktop\1\bizhang\libraries\CMSIS\RTOS\Template" -I"C:\Users\10091\Desktop\1\bizhang\libraries\STM32F4xx_HAL_Driver\Inc" -I"C:\Users\10091\Desktop\1\bizhang\libraries\STM32F4xx_HAL_Driver\Inc\Legacy" -I"C:\Users\10091\Desktop\1\bizhang" -I"C:\Users\10091\Desktop\1\bizhang\applications" -I"C:\Users\10091\Desktop\1\bizhang" -I"C:\Users\10091\Desktop\1\bizhang\packages\mpu6xxx-latest\inc" -I"C:\Users\10091\Desktop\1\bizhang\rt-thread\components\drivers\include" -I"C:\Users\10091\Desktop\1\bizhang\rt-thread\components\drivers\sensors" -I"C:\Users\10091\Desktop\1\bizhang\rt-thread\components\finsh" -I"C:\Users\10091\Desktop\1\bizhang\rt-thread\components\libc\compilers\common" -I"C:\Users\10091\Desktop\1\bizhang\rt-thread\components\libc\compilers\newlib" -I"C:\Users\10091\Desktop\1\bizhang\rt-thread\components\libc\posix\io\poll" -I"C:\Users\10091\Desktop\1\bizhang\rt-thread\components\libc\posix\io\stdio" -I"C:\Users\10091\Desktop\1\bizhang\rt-thread\components\libc\posix\ipc" -I"C:\Users\10091\Desktop\1\bizhang\rt-thread\components\utilities\ulog" -I"C:\Users\10091\Desktop\1\bizhang\rt-thread\include" -I"C:\Users\10091\Desktop\1\bizhang\rt-thread\libcpu\arm\common" -I"C:\Users\10091\Desktop\1\bizhang\rt-thread\libcpu\arm\cortex-m4" -include"C:\Users\10091\Desktop\1\bizhang\rtconfig_preinc.h" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"


################################################################################
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../applications/car.c \
../applications/car_pwm.c \
../applications/hc_pid.c \
../applications/hcsr04.c \
../applications/main.c \
../applications/mpu6050.c \
../applications/straight_pid.c \
../applications/uart2.c 

OBJS += \
./applications/car.o \
./applications/car_pwm.o \
./applications/hc_pid.o \
./applications/hcsr04.o \
./applications/main.o \
./applications/mpu6050.o \
./applications/straight_pid.o \
./applications/uart2.o 

C_DEPS += \
./applications/car.d \
./applications/car_pwm.d \
./applications/hc_pid.d \
./applications/hcsr04.d \
./applications/main.d \
./applications/mpu6050.d \
./applications/straight_pid.d \
./applications/uart2.d 


# Each subdirectory must supply rules for building sources it contributes
applications/%.o: ../applications/%.c
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -ffunction-sections -fdata-sections -Wall  -g -gdwarf-2 -DSOC_FAMILY_STM32 -DSOC_SERIES_STM32F4 -DUSE_HAL_DRIVER -DSTM32F407xx -I"G:\RT-ThreadStudio1\workspace\bizhang\drivers" -I"G:\RT-ThreadStudio1\workspace\bizhang\eMPL" -I"G:\RT-ThreadStudio1\workspace\bizhang\drivers\include" -I"G:\RT-ThreadStudio1\workspace\bizhang\drivers\include\config" -I"G:\RT-ThreadStudio1\workspace\bizhang\libraries\CMSIS\Device\ST\STM32F4xx\Include" -I"G:\RT-ThreadStudio1\workspace\bizhang\libraries\CMSIS\Include" -I"G:\RT-ThreadStudio1\workspace\bizhang\libraries\CMSIS\RTOS\Template" -I"G:\RT-ThreadStudio1\workspace\bizhang\libraries\STM32F4xx_HAL_Driver\Inc" -I"G:\RT-ThreadStudio1\workspace\bizhang\libraries\STM32F4xx_HAL_Driver\Inc\Legacy" -I"G:\RT-ThreadStudio1\workspace\bizhang" -I"G:\RT-ThreadStudio1\workspace\bizhang\applications" -I"G:\RT-ThreadStudio1\workspace\bizhang" -I"G:\RT-ThreadStudio1\workspace\bizhang\packages\mpu6xxx-latest\inc" -I"G:\RT-ThreadStudio1\workspace\bizhang\rt-thread\components\drivers\include" -I"G:\RT-ThreadStudio1\workspace\bizhang\rt-thread\components\drivers\sensors" -I"G:\RT-ThreadStudio1\workspace\bizhang\rt-thread\components\finsh" -I"G:\RT-ThreadStudio1\workspace\bizhang\rt-thread\components\libc\compilers\common" -I"G:\RT-ThreadStudio1\workspace\bizhang\rt-thread\components\libc\compilers\newlib" -I"G:\RT-ThreadStudio1\workspace\bizhang\rt-thread\components\libc\posix\io\poll" -I"G:\RT-ThreadStudio1\workspace\bizhang\rt-thread\components\libc\posix\io\stdio" -I"G:\RT-ThreadStudio1\workspace\bizhang\rt-thread\components\libc\posix\ipc" -I"G:\RT-ThreadStudio1\workspace\bizhang\rt-thread\components\utilities\ulog" -I"G:\RT-ThreadStudio1\workspace\bizhang\rt-thread\include" -I"G:\RT-ThreadStudio1\workspace\bizhang\rt-thread\libcpu\arm\common" -I"G:\RT-ThreadStudio1\workspace\bizhang\rt-thread\libcpu\arm\cortex-m4" -include"G:\RT-ThreadStudio1\workspace\bizhang\rtconfig_preinc.h" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"


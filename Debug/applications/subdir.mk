################################################################################
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../applications/car.c \
../applications/car_pwm.c \
../applications/hc_pid.c \
../applications/main.c \
../applications/mpu6050.c \
../applications/ov_pid.c \
../applications/straight_pid.c \
../applications/test.c \
../applications/uart2.c 

OBJS += \
./applications/car.o \
./applications/car_pwm.o \
./applications/hc_pid.o \
./applications/main.o \
./applications/mpu6050.o \
./applications/ov_pid.o \
./applications/straight_pid.o \
./applications/test.o \
./applications/uart2.o 

C_DEPS += \
./applications/car.d \
./applications/car_pwm.d \
./applications/hc_pid.d \
./applications/main.d \
./applications/mpu6050.d \
./applications/ov_pid.d \
./applications/straight_pid.d \
./applications/test.d \
./applications/uart2.d 


# Each subdirectory must supply rules for building sources it contributes
applications/%.o: ../applications/%.c
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -ffunction-sections -fdata-sections -Wall  -g -gdwarf-2 -DSOC_FAMILY_STM32 -DSOC_SERIES_STM32F4 -DUSE_HAL_DRIVER -DSTM32F407xx -I"D:\diansai\2022\bizhang\drivers" -I"D:\diansai\2022\bizhang\eMPL" -I"D:\diansai\2022\bizhang\drivers\include" -I"D:\diansai\2022\bizhang\drivers\include\config" -I"D:\diansai\2022\bizhang\libraries\CMSIS\Device\ST\STM32F4xx\Include" -I"D:\diansai\2022\bizhang\libraries\CMSIS\Include" -I"D:\diansai\2022\bizhang\libraries\CMSIS\RTOS\Template" -I"D:\diansai\2022\bizhang\libraries\STM32F4xx_HAL_Driver\Inc" -I"D:\diansai\2022\bizhang\libraries\STM32F4xx_HAL_Driver\Inc\Legacy" -I"D:\diansai\2022\bizhang" -I"D:\diansai\2022\bizhang\applications" -I"D:\diansai\2022\bizhang" -I"D:\diansai\2022\bizhang\packages\mpu6xxx-latest\inc" -I"D:\diansai\2022\bizhang\packages\sr04-latest" -I"D:\diansai\2022\bizhang\rt-thread\components\drivers\include" -I"D:\diansai\2022\bizhang\rt-thread\components\drivers\sensors" -I"D:\diansai\2022\bizhang\rt-thread\components\finsh" -I"D:\diansai\2022\bizhang\rt-thread\components\libc\compilers\common" -I"D:\diansai\2022\bizhang\rt-thread\components\libc\compilers\newlib" -I"D:\diansai\2022\bizhang\rt-thread\components\libc\posix\io\poll" -I"D:\diansai\2022\bizhang\rt-thread\components\libc\posix\io\stdio" -I"D:\diansai\2022\bizhang\rt-thread\components\libc\posix\ipc" -I"D:\diansai\2022\bizhang\rt-thread\components\utilities\ulog" -I"D:\diansai\2022\bizhang\rt-thread\include" -I"D:\diansai\2022\bizhang\rt-thread\libcpu\arm\common" -I"D:\diansai\2022\bizhang\rt-thread\libcpu\arm\cortex-m4" -include"D:\diansai\2022\bizhang\rtconfig_preinc.h" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"


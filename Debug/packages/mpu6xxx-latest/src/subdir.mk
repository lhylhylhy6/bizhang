################################################################################
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../packages/mpu6xxx-latest/src/mpu6xxx.c \
../packages/mpu6xxx-latest/src/sensor_inven_mpu6xxx.c 

OBJS += \
./packages/mpu6xxx-latest/src/mpu6xxx.o \
./packages/mpu6xxx-latest/src/sensor_inven_mpu6xxx.o 

C_DEPS += \
./packages/mpu6xxx-latest/src/mpu6xxx.d \
./packages/mpu6xxx-latest/src/sensor_inven_mpu6xxx.d 


# Each subdirectory must supply rules for building sources it contributes
packages/mpu6xxx-latest/src/%.o: ../packages/mpu6xxx-latest/src/%.c
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -ffunction-sections -fdata-sections -Wall  -g -gdwarf-2 -DSOC_FAMILY_STM32 -DSOC_SERIES_STM32F4 -DUSE_HAL_DRIVER -DSTM32F407xx -I"D:\diansai\2022\bizhang\drivers" -I"D:\diansai\2022\bizhang\eMPL" -I"D:\diansai\2022\bizhang\drivers\include" -I"D:\diansai\2022\bizhang\drivers\include\config" -I"D:\diansai\2022\bizhang\libraries\CMSIS\Device\ST\STM32F4xx\Include" -I"D:\diansai\2022\bizhang\libraries\CMSIS\Include" -I"D:\diansai\2022\bizhang\libraries\CMSIS\RTOS\Template" -I"D:\diansai\2022\bizhang\libraries\STM32F4xx_HAL_Driver\Inc" -I"D:\diansai\2022\bizhang\libraries\STM32F4xx_HAL_Driver\Inc\Legacy" -I"D:\diansai\2022\bizhang" -I"D:\diansai\2022\bizhang\applications" -I"D:\diansai\2022\bizhang" -I"D:\diansai\2022\bizhang\packages\mpu6xxx-latest\inc" -I"D:\diansai\2022\bizhang\packages\sr04-latest" -I"D:\diansai\2022\bizhang\rt-thread\components\drivers\include" -I"D:\diansai\2022\bizhang\rt-thread\components\drivers\sensors" -I"D:\diansai\2022\bizhang\rt-thread\components\finsh" -I"D:\diansai\2022\bizhang\rt-thread\components\libc\compilers\common" -I"D:\diansai\2022\bizhang\rt-thread\components\libc\compilers\newlib" -I"D:\diansai\2022\bizhang\rt-thread\components\libc\posix\io\poll" -I"D:\diansai\2022\bizhang\rt-thread\components\libc\posix\io\stdio" -I"D:\diansai\2022\bizhang\rt-thread\components\libc\posix\ipc" -I"D:\diansai\2022\bizhang\rt-thread\components\utilities\ulog" -I"D:\diansai\2022\bizhang\rt-thread\include" -I"D:\diansai\2022\bizhang\rt-thread\libcpu\arm\common" -I"D:\diansai\2022\bizhang\rt-thread\libcpu\arm\cortex-m4" -include"D:\diansai\2022\bizhang\rtconfig_preinc.h" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"


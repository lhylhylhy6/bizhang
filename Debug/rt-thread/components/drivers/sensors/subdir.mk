################################################################################
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../rt-thread/components/drivers/sensors/sensor.c \
../rt-thread/components/drivers/sensors/sensor_cmd.c 

OBJS += \
./rt-thread/components/drivers/sensors/sensor.o \
./rt-thread/components/drivers/sensors/sensor_cmd.o 

C_DEPS += \
./rt-thread/components/drivers/sensors/sensor.d \
./rt-thread/components/drivers/sensors/sensor_cmd.d 


# Each subdirectory must supply rules for building sources it contributes
rt-thread/components/drivers/sensors/%.o: ../rt-thread/components/drivers/sensors/%.c
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -ffunction-sections -fdata-sections -Wall  -g -gdwarf-2 -DSOC_FAMILY_STM32 -DSOC_SERIES_STM32F4 -DUSE_HAL_DRIVER -DSTM32F407xx -I"C:\Users\10091\Desktop\1\bizhang\drivers" -I"C:\Users\10091\Desktop\1\bizhang\eMPL" -I"C:\Users\10091\Desktop\1\bizhang\drivers\include" -I"C:\Users\10091\Desktop\1\bizhang\drivers\include\config" -I"C:\Users\10091\Desktop\1\bizhang\libraries\CMSIS\Device\ST\STM32F4xx\Include" -I"C:\Users\10091\Desktop\1\bizhang\libraries\CMSIS\Include" -I"C:\Users\10091\Desktop\1\bizhang\libraries\CMSIS\RTOS\Template" -I"C:\Users\10091\Desktop\1\bizhang\libraries\STM32F4xx_HAL_Driver\Inc" -I"C:\Users\10091\Desktop\1\bizhang\libraries\STM32F4xx_HAL_Driver\Inc\Legacy" -I"C:\Users\10091\Desktop\1\bizhang" -I"C:\Users\10091\Desktop\1\bizhang\applications" -I"C:\Users\10091\Desktop\1\bizhang" -I"C:\Users\10091\Desktop\1\bizhang\packages\mpu6xxx-latest\inc" -I"C:\Users\10091\Desktop\1\bizhang\rt-thread\components\drivers\include" -I"C:\Users\10091\Desktop\1\bizhang\rt-thread\components\drivers\sensors" -I"C:\Users\10091\Desktop\1\bizhang\rt-thread\components\finsh" -I"C:\Users\10091\Desktop\1\bizhang\rt-thread\components\libc\compilers\common" -I"C:\Users\10091\Desktop\1\bizhang\rt-thread\components\libc\compilers\newlib" -I"C:\Users\10091\Desktop\1\bizhang\rt-thread\components\libc\posix\io\poll" -I"C:\Users\10091\Desktop\1\bizhang\rt-thread\components\libc\posix\io\stdio" -I"C:\Users\10091\Desktop\1\bizhang\rt-thread\components\libc\posix\ipc" -I"C:\Users\10091\Desktop\1\bizhang\rt-thread\components\utilities\ulog" -I"C:\Users\10091\Desktop\1\bizhang\rt-thread\include" -I"C:\Users\10091\Desktop\1\bizhang\rt-thread\libcpu\arm\common" -I"C:\Users\10091\Desktop\1\bizhang\rt-thread\libcpu\arm\cortex-m4" -include"C:\Users\10091\Desktop\1\bizhang\rtconfig_preinc.h" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"


################################################################################
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../libraries/CMSIS/Device/ST/STM32F4xx/Source/Templates/system_stm32f4xx.c 

OBJS += \
./libraries/CMSIS/Device/ST/STM32F4xx/Source/Templates/system_stm32f4xx.o 

C_DEPS += \
./libraries/CMSIS/Device/ST/STM32F4xx/Source/Templates/system_stm32f4xx.d 


# Each subdirectory must supply rules for building sources it contributes
libraries/CMSIS/Device/ST/STM32F4xx/Source/Templates/%.o: ../libraries/CMSIS/Device/ST/STM32F4xx/Source/Templates/%.c
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -ffunction-sections -fdata-sections -Wall  -g -gdwarf-2 -DSOC_FAMILY_STM32 -DSOC_SERIES_STM32F4 -DUSE_HAL_DRIVER -DSTM32F407xx -I"D:\RT-ThreadStudio\project\bizhang\drivers" -I"D:\RT-ThreadStudio\project\bizhang\eMPL" -I"D:\RT-ThreadStudio\project\bizhang\drivers\include" -I"D:\RT-ThreadStudio\project\bizhang\drivers\include\config" -I"D:\RT-ThreadStudio\project\bizhang\libraries\CMSIS\Device\ST\STM32F4xx\Include" -I"D:\RT-ThreadStudio\project\bizhang\libraries\CMSIS\Include" -I"D:\RT-ThreadStudio\project\bizhang\libraries\CMSIS\RTOS\Template" -I"D:\RT-ThreadStudio\project\bizhang\libraries\STM32F4xx_HAL_Driver\Inc" -I"D:\RT-ThreadStudio\project\bizhang\libraries\STM32F4xx_HAL_Driver\Inc\Legacy" -I"D:\RT-ThreadStudio\project\bizhang" -I"D:\RT-ThreadStudio\project\bizhang\applications" -I"D:\RT-ThreadStudio\project\bizhang" -I"D:\RT-ThreadStudio\project\bizhang\packages\mpu6xxx-latest\inc" -I"D:\RT-ThreadStudio\project\bizhang\rt-thread\components\drivers\include" -I"D:\RT-ThreadStudio\project\bizhang\rt-thread\components\drivers\sensors" -I"D:\RT-ThreadStudio\project\bizhang\rt-thread\components\finsh" -I"D:\RT-ThreadStudio\project\bizhang\rt-thread\components\libc\compilers\common" -I"D:\RT-ThreadStudio\project\bizhang\rt-thread\components\libc\compilers\newlib" -I"D:\RT-ThreadStudio\project\bizhang\rt-thread\components\libc\posix\io\poll" -I"D:\RT-ThreadStudio\project\bizhang\rt-thread\components\libc\posix\io\stdio" -I"D:\RT-ThreadStudio\project\bizhang\rt-thread\components\libc\posix\ipc" -I"D:\RT-ThreadStudio\project\bizhang\rt-thread\components\utilities\ulog" -I"D:\RT-ThreadStudio\project\bizhang\rt-thread\include" -I"D:\RT-ThreadStudio\project\bizhang\rt-thread\libcpu\arm\common" -I"D:\RT-ThreadStudio\project\bizhang\rt-thread\libcpu\arm\cortex-m4" -include"D:\RT-ThreadStudio\project\bizhang\rtconfig_preinc.h" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"

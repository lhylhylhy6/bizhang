################################################################################
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../rt-thread/components/drivers/ipc/completion.c \
../rt-thread/components/drivers/ipc/dataqueue.c \
../rt-thread/components/drivers/ipc/pipe.c \
../rt-thread/components/drivers/ipc/ringblk_buf.c \
../rt-thread/components/drivers/ipc/ringbuffer.c \
../rt-thread/components/drivers/ipc/waitqueue.c \
../rt-thread/components/drivers/ipc/workqueue.c 

OBJS += \
./rt-thread/components/drivers/ipc/completion.o \
./rt-thread/components/drivers/ipc/dataqueue.o \
./rt-thread/components/drivers/ipc/pipe.o \
./rt-thread/components/drivers/ipc/ringblk_buf.o \
./rt-thread/components/drivers/ipc/ringbuffer.o \
./rt-thread/components/drivers/ipc/waitqueue.o \
./rt-thread/components/drivers/ipc/workqueue.o 

C_DEPS += \
./rt-thread/components/drivers/ipc/completion.d \
./rt-thread/components/drivers/ipc/dataqueue.d \
./rt-thread/components/drivers/ipc/pipe.d \
./rt-thread/components/drivers/ipc/ringblk_buf.d \
./rt-thread/components/drivers/ipc/ringbuffer.d \
./rt-thread/components/drivers/ipc/waitqueue.d \
./rt-thread/components/drivers/ipc/workqueue.d 


# Each subdirectory must supply rules for building sources it contributes
rt-thread/components/drivers/ipc/%.o: ../rt-thread/components/drivers/ipc/%.c
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -ffunction-sections -fdata-sections -Wall  -g -gdwarf-2 -DSOC_FAMILY_STM32 -DSOC_SERIES_STM32F4 -DUSE_HAL_DRIVER -DSTM32F407xx -I"G:\RT-ThreadStudio1\workspace\bizhang\drivers" -I"G:\RT-ThreadStudio1\workspace\bizhang\eMPL" -I"G:\RT-ThreadStudio1\workspace\bizhang\drivers\include" -I"G:\RT-ThreadStudio1\workspace\bizhang\drivers\include\config" -I"G:\RT-ThreadStudio1\workspace\bizhang\libraries\CMSIS\Device\ST\STM32F4xx\Include" -I"G:\RT-ThreadStudio1\workspace\bizhang\libraries\CMSIS\Include" -I"G:\RT-ThreadStudio1\workspace\bizhang\libraries\CMSIS\RTOS\Template" -I"G:\RT-ThreadStudio1\workspace\bizhang\libraries\STM32F4xx_HAL_Driver\Inc" -I"G:\RT-ThreadStudio1\workspace\bizhang\libraries\STM32F4xx_HAL_Driver\Inc\Legacy" -I"G:\RT-ThreadStudio1\workspace\bizhang" -I"G:\RT-ThreadStudio1\workspace\bizhang\applications" -I"G:\RT-ThreadStudio1\workspace\bizhang" -I"G:\RT-ThreadStudio1\workspace\bizhang\packages\mpu6xxx-latest\inc" -I"G:\RT-ThreadStudio1\workspace\bizhang\rt-thread\components\drivers\include" -I"G:\RT-ThreadStudio1\workspace\bizhang\rt-thread\components\drivers\sensors" -I"G:\RT-ThreadStudio1\workspace\bizhang\rt-thread\components\finsh" -I"G:\RT-ThreadStudio1\workspace\bizhang\rt-thread\components\libc\compilers\common" -I"G:\RT-ThreadStudio1\workspace\bizhang\rt-thread\components\libc\compilers\newlib" -I"G:\RT-ThreadStudio1\workspace\bizhang\rt-thread\components\libc\posix\io\poll" -I"G:\RT-ThreadStudio1\workspace\bizhang\rt-thread\components\libc\posix\io\stdio" -I"G:\RT-ThreadStudio1\workspace\bizhang\rt-thread\components\libc\posix\ipc" -I"G:\RT-ThreadStudio1\workspace\bizhang\rt-thread\components\utilities\ulog" -I"G:\RT-ThreadStudio1\workspace\bizhang\rt-thread\include" -I"G:\RT-ThreadStudio1\workspace\bizhang\rt-thread\libcpu\arm\common" -I"G:\RT-ThreadStudio1\workspace\bizhang\rt-thread\libcpu\arm\cortex-m4" -include"G:\RT-ThreadStudio1\workspace\bizhang\rtconfig_preinc.h" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"


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
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -ffunction-sections -fdata-sections -Wall  -g -gdwarf-2 -DSOC_FAMILY_STM32 -DSOC_SERIES_STM32F4 -DUSE_HAL_DRIVER -DSTM32F407xx -I"D:\diansai\2022\bizhang\drivers" -I"D:\diansai\2022\bizhang\eMPL" -I"D:\diansai\2022\bizhang\drivers\include" -I"D:\diansai\2022\bizhang\drivers\include\config" -I"D:\diansai\2022\bizhang\libraries\CMSIS\Device\ST\STM32F4xx\Include" -I"D:\diansai\2022\bizhang\libraries\CMSIS\Include" -I"D:\diansai\2022\bizhang\libraries\CMSIS\RTOS\Template" -I"D:\diansai\2022\bizhang\libraries\STM32F4xx_HAL_Driver\Inc" -I"D:\diansai\2022\bizhang\libraries\STM32F4xx_HAL_Driver\Inc\Legacy" -I"D:\diansai\2022\bizhang" -I"D:\diansai\2022\bizhang\applications" -I"D:\diansai\2022\bizhang" -I"D:\diansai\2022\bizhang\packages\mpu6xxx-latest\inc" -I"D:\diansai\2022\bizhang\packages\sr04-latest" -I"D:\diansai\2022\bizhang\rt-thread\components\drivers\include" -I"D:\diansai\2022\bizhang\rt-thread\components\drivers\sensors" -I"D:\diansai\2022\bizhang\rt-thread\components\finsh" -I"D:\diansai\2022\bizhang\rt-thread\components\libc\compilers\common" -I"D:\diansai\2022\bizhang\rt-thread\components\libc\compilers\newlib" -I"D:\diansai\2022\bizhang\rt-thread\components\libc\posix\io\poll" -I"D:\diansai\2022\bizhang\rt-thread\components\libc\posix\io\stdio" -I"D:\diansai\2022\bizhang\rt-thread\components\libc\posix\ipc" -I"D:\diansai\2022\bizhang\rt-thread\components\utilities\ulog" -I"D:\diansai\2022\bizhang\rt-thread\include" -I"D:\diansai\2022\bizhang\rt-thread\libcpu\arm\common" -I"D:\diansai\2022\bizhang\rt-thread\libcpu\arm\cortex-m4" -include"D:\diansai\2022\bizhang\rtconfig_preinc.h" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"


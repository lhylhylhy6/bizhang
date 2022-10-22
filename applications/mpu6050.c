/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-10-22     10091       the first version
 */
#include "mpu6050.h"
#define DBG_TAG "mpu"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>

struct mpu6xxx_device *dev;
rt_mutex_t number_protect;
rt_thread_t mpu_device = RT_NULL;

float pitch,roll,yaw,number;

void angle_read_entry(void *parameter)
{
    while(1)
    {
        rt_mutex_take(number_protect, RT_WAITING_FOREVER);
        while(mpu_dmp_get_data(&pitch,&roll,&yaw)!=0){}
        number = roll;
//        rt_kprintf("%d\n",number);
        LOG_D("%.2f",roll);
        rt_mutex_release(number_protect);
        rt_thread_delay(10);
    }
}

void mpu_6050_init(void)
{
    dev = mpu6xxx_init("i2c1", 0x68);
    mpu6xxx_set_param(dev, MPU6XXX_SAMPLE_RATE, 1000);
    mpu6xxx_set_param(dev, MPU6XXX_DLPF_CONFIG, MPU6XXX_DLPF_188HZ);
    while(mpu_dmp_init())
    {
        rt_kprintf("init error\n");
        rt_thread_delay(50);
    }
    rt_kprintf("init ok\n");
    number_protect = rt_mutex_create("protect", RT_IPC_FLAG_PRIO);
    mpu_device = rt_thread_create("mpu6050", angle_read_entry, RT_NULL, 1024, 0, 300);
    if(mpu_device)
    {
        rt_thread_startup(mpu_device);
    }
    else {
        rt_kprintf("error\n");
    }
}


rt_uint8_t MPU_Write_Len(rt_uint8_t addr,rt_uint8_t reg,rt_uint8_t len,rt_uint8_t *databuf)
{
    rt_uint8_t res;
#ifdef RT_USING_I2C
    struct rt_i2c_msg msgs;
    rt_uint8_t buf[50] = {0};
#endif
    buf[0] = reg;

    for(int i = 0;i<len;i++)
    {
        buf[i+1]=databuf[i];
    }

    if (dev->bus->type == RT_Device_Class_I2CBUS)
    {
        msgs.addr  = dev->i2c_addr;    /* slave address */
        msgs.flags = RT_I2C_WR;        /* write flag */
        msgs.buf   = buf;              /* Send data pointer */
        msgs.len   = len+1;

        if (rt_i2c_transfer((struct rt_i2c_bus_device *)dev->bus, &msgs, 1) == 1)
        {
            res = RT_EOK;
        }
        else
        {
            res = -RT_ERROR;
        }
    }
    return res;
}

rt_uint8_t MPU_Read_Len(rt_uint8_t addr,rt_uint8_t reg,rt_uint8_t len,rt_uint8_t *buf)
{
    rt_int8_t res = 0;
#ifdef RT_USING_I2C
    struct rt_i2c_msg msgs[2];
#endif
#ifdef RT_USING_SPI
    rt_uint8_t tmp;
#endif
    if (dev->bus->type == RT_Device_Class_I2CBUS)
    {
        msgs[0].addr  = dev->i2c_addr;    /* Slave address */
        msgs[0].flags = RT_I2C_WR;        /* Write flag */
        msgs[0].buf   = &reg;             /* Slave register address */
        msgs[0].len   = 1;                /* Number of bytes sent */

        msgs[1].addr  = dev->i2c_addr;    /* Slave address */
        msgs[1].flags = RT_I2C_RD;        /* Read flag */
        msgs[1].buf   = buf;              /* Read data pointer */
        msgs[1].len   = len;              /* Number of bytes read */

        if (rt_i2c_transfer((struct rt_i2c_bus_device *)dev->bus, msgs, 2) == 2)
        {
            res = RT_EOK;
        }
        else
        {
            res = -RT_ERROR;
        }
    }

    return res;
}

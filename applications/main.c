/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-09-20     RT-Thread    first version
 */

#include <rtthread.h>
#include "uart2.h"
#include "car.h"
#include "car_pwm.h"
#include "ov_pid.h"
#include "straight_pid.h"

#define DBG_TAG "main"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>

#define INT_PIN   GET_PIN(F,3)


int pin_inter_init(void);

rt_uint16_t distance=0;
extern rt_uint8_t start_flag;

extern enum car_state State;



int main(void)
{
    //初始化
    LOG_D("v0.7\r\n");
    car_init();
    pid_uart_init();
    straight_pid_init();
    rt_thread_mdelay(500);
    test_init();
    pin_inter_init();
    while (1)
    {
        //rt_kprintf("%d\r\n",distance);
        rt_thread_mdelay(1000);
    }
    return RT_EOK;
}

int restart(void)
{
    rt_hw_cpu_reset();
    return RT_EOK;
}

extern rt_uint8_t return_f;
extern uint8_t should_stop;
rt_uint32_t temp_i=0;
uint16_t pin_level=0;
void inter_handle(void *args)
{
    if(start_flag==1&&return_f==1&&should_stop==1)
    {
        temp_i=10;
        while(temp_i--)
        {
            pin_level += rt_pin_read(INT_PIN);
        }
        if(pin_level>=8)
        {
            State=CAR_STOP;
            car_stop();
            rt_kprintf("stop\r\n");
        }
        pin_level=0;
    }
}
int pin_inter_init(void)
{
    rt_pin_mode(INT_PIN,PIN_MODE_INPUT);
    rt_pin_attach_irq(INT_PIN, PIN_IRQ_MODE_RISING,inter_handle, RT_NULL);
    rt_pin_irq_enable(INT_PIN, PIN_IRQ_ENABLE);
    return 0;
}
//INIT_APP_EXPORT(pin_inter_init);
MSH_CMD_EXPORT(restart , restart);

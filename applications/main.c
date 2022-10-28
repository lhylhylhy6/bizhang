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
#include "hcsr04.h"
#include "hc_pid.h"
#include "straight_pid.h"
#define DBG_TAG "main"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>
#include "car_pwm.h"

extern rt_thread_t straight_pid_thread;
extern rt_thread_t pid_read_thread;
extern rt_thread_t mid_hc_thread;
extern rt_uint32_t number;
extern int middle;
extern rt_int32_t pwm_l,pwm_r;
extern int turn_flag;
extern float left_val;
extern float right_val;

int main(void)
{
    pid_uart_init();
    car_init();
    straight_pid_init();
    HCSR_mid_init();
    rt_kprintf("init all ok!\r\n");
    while (1)
    {
        if(turn_flag==1)
        {
            car_left();
            if((left_val<=60)&&(right_val<=60))
            {
                turn_flag = 0;
                car_right_angle();
                rt_thread_resume(pid_read_thread);
                rt_thread_resume(straight_pid_thread);
                rt_thread_resume(mid_hc_thread);
                car_forward();
            }
        }
        rt_thread_mdelay(50);
    }
    return RT_EOK;
}

int restart(void)
{
    rt_hw_cpu_reset();
    return RT_EOK;
}
MSH_CMD_EXPORT(restart , restart);

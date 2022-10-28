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

extern int turn_flag;

extern float left_val;
extern float right_val;
extern int start_single;

int main(void)
{
    pid_uart_init();
    car_init();
    straight_pid_init();
    HCSR_mid_init();
    rt_kprintf("init all ok!\r\n");
    static int m = 0;
    static int cycle_flag = 0;
    static int delay_num = 0;
    while (1)
    {
        if(turn_flag==1)
        {
            car_left();
            if(cycle_flag==0)
            {
                delay_num++;
            }
            if(delay_num == 40)
            {
                cycle_flag = 1;
                delay_num = 0;
            }
            m++;
            if(m==20)
            {
                LOG_D("%f %f\n",left_val,right_val);
                m=0;
            }
            if(((right_val+left_val>=80)&&(right_val+left_val<=120))&&(cycle_flag == 1))
            {
                LOG_D("~~~~~~~~~~~~~~~~\n");
                turn_flag = 0;
                cycle_flag = 0;
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

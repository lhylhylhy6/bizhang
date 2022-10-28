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

int stop_single = 0;

extern rt_thread_t straight_pid_thread;
extern rt_thread_t pid_read_thread;
extern rt_thread_t mid_hc_thread;

extern int turn_flag;

extern float left_val;
extern float right_val;
extern float left_min_val;
extern float right_min_val;
extern int start_single;
extern int stop_flag;

rt_timer_t clear_data;
rt_timer_t stop_timer;
void clearn_data_entry(void *parameter)
{
    left_min_val=99999;
    right_min_val=99999;
}

void stop_entry(void *parameter)
{
    stop_single = 1;
}
int main(void)
{
    pid_uart_init();
    car_init();
    straight_pid_init();
    HCSR_mid_init();
    clear_data = rt_timer_create("clearn", clearn_data_entry, 0, 500, RT_TIMER_FLAG_SOFT_TIMER|RT_TIMER_FLAG_PERIODIC);
    rt_timer_start(clear_data);
    stop_timer = rt_timer_create("stop", stop_entry, 0, 5000, RT_TIMER_FLAG_SOFT_TIMER|RT_TIMER_FLAG_ONE_SHOT);
    rt_kprintf("init all ok 1.1!\r\n");
    static int m = 0;
    static int cycle_flag = 0;
    static int delay_num = 0;
    while (1)
    {

        if(turn_flag==1)
        {
            //LOG_D("--turn_flag now is 1--");
            if(stop_flag == 5 )
            {
               stop_flag=100;
               rt_timer_start(stop_timer);
            }
            if(stop_single == 0)
               car_left();
            else if (stop_single == 1)
            {
                stop_single=2;
                LOG_D("SUCCESS\r\n");
                car_right_angle();
                car_forward();

            }
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
            if(((right_min_val+left_val>=60)&&(right_min_val+left_val<=100))&&(cycle_flag == 1))
            {
                LOG_D("~~~~~~~~~~~~~~~~\n");
                turn_flag = 0;
                //LOG_D("--turn_flag now is 0--");
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

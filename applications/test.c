/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-18     lhylh       the first version
 */
#include "car_pwm.h"
#include "car.h"

#define DBG_TAG "test"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>

rt_timer_t scan_red = 0;
rt_uint8_t red_flag=1;
rt_uint8_t stop_flag=0;

extern rt_uint16_t distance;
extern struct rt_device_pwm * yuntai_dev;
extern rt_device_t pid_uart;
extern rt_uint32_t yuntai_period;
extern rt_uint32_t sp_pulse;
extern rt_uint32_t sz_pulse;
rt_thread_t test_thread;

extern rt_uint8_t ov_control_flag;
extern rt_uint8_t str_control_flag;
extern rt_uint8_t is_color;

rt_uint8_t sent_black;
rt_uint8_t  start_flag=0;
rt_uint8_t return_f=0;
//rt_uint8_t  three = 0;
rt_uint8_t post_num=1;
uint8_t should_stop=0;


void time_out_entry(void *parameter)
{
    LOG_D("TIMEOUT \r\n");
    if(red_flag==1)
    {
        LOG_D("~~~~~~~~~~~~~~~~~\n");
    }
    else if(red_flag==0)
    {
        LOG_D("post_num:%d---send_back:%d\n",post_num,sent_black);
        return_f=1;
    }
    LOG_D("close timer\r\n");
}


enum car_state State=CAR_STOP;
rt_uint8_t car_side=0; //0为左，1为右

void test_entry(void *parameter)
{
    State = CAR_PID;
    rt_kprintf("****************************\r\n");
    while(1)
    {
        if(stop_flag==0)
        {
            switch(State)
            {
                case CAR_PID:
                    str_control_flag=1;
                    car_forward();
                    if(should_stop==0)
                    {
                        while(distance>70)
                        {
                            //rt_kprintf("%d\r\n",distance);
                            rt_thread_mdelay(100);
                        }
                        rt_kprintf("state is turn\r\n");
                        State = CAR_TURN;
                    }
                    break;
                case CAR_TURN:
                    str_control_flag=0;
                    if(car_side)
                    {
                        car_right_angle();
                    }
                    else
                    {
                        car_left_angle();
                    }
                    sent_black++;
                    State = CAR_CIRCLE;
                    red_flag=0;
                    rt_kprintf("state is circle\r\n");
                    break;
                case CAR_CIRCLE:
                    str_control_flag=0;
                    start_flag=1;
                    if(return_f==0)
                    {
                        LOG_D("open timer\r\n");
                        red_flag=0;
                        rt_timer_start(scan_red);
                    }
                    else
                    {
                        rt_pwm_set(yuntai_dev, sz_pulse, yuntai_period, yuntai_period*85/1000);
                    }
                    rt_kprintf("%d--%d\r\n",post_num,sent_black);
                    if(post_num*2-1==sent_black && return_f==1)
                    {
                       char ch='c';
                       rt_pwm_set(yuntai_dev, SZ_CHANNEL, yuntai_period, yuntai_period*90/1000);
                       should_stop=1;
                       rt_device_write(pid_uart, -1, &ch, sizeof(ch));
                       extern rt_uint32_t pulse;
                       pulse=40;
                    }
                    if(car_side)
                    {
                        car_right();
                        car_side=0;
                    }
                    else
                    {
                        car_left();
                        car_side=1;
                    }
                    rt_thread_mdelay(500); // !!!
                    is_color=0;
                    while(1)
                    {
                        if(post_num==1)
                        {
                            if(return_f==1)
                            {
                               rt_thread_mdelay(500); //为了第一个柱子
                               char ch='c';
                               should_stop=1;
                               rt_pwm_set(yuntai_dev, SZ_CHANNEL, yuntai_period, yuntai_period*90/1000);
                               rt_device_write(pid_uart, -1, &ch, sizeof(ch));
                               extern rt_uint32_t pulse;
                               pulse=40;
                            }
                        }
                        if(State==CAR_STOP)
                        {
                            break;
                        }
                        if(is_color==1)
                        {
                            if(return_f==0)
                                post_num++;
                            if(State!=CAR_STOP)
                            {
                                State = CAR_PID;
                                rt_kprintf("state is pid\r\n");
                                break;
                            }
                            break;
                        }
                        rt_thread_mdelay(100);
                    }
                    break;
                case CAR_STOP:
                    ov_control_flag=0;
                    str_control_flag=0;
                    car_stop();
                    rt_kprintf("state is stop\r\n");
                    break;
            }
        }
        rt_thread_mdelay(100);
    }
}

int test_init(void)
{
    test_thread = rt_thread_create("test_t", test_entry, RT_NULL, 2048, 5, 200);
    scan_red = rt_timer_create("scan", time_out_entry, RT_NULL, 1700, RT_TIMER_FLAG_SOFT_TIMER|RT_TIMER_FLAG_ONE_SHOT);
    if(test_thread)
    {
        rt_thread_startup(test_thread);
    }
    else {
        LOG_E("start up test_thread filed!\n");
    }
    return 0;
}


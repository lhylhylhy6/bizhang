/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-09-20     lhylh       the first version
 */
#include "car.h"
#include "pid.h"
#include <rtthread.h>
#include <rtdevice.h>
#include "drivers\include\drv_common.h"
#include "hcsr04.h"

#define DBG_TAG "car"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>

#define CAR_MSH_ENABLE 1

extern int pulse;


//设置车的基本速度
int car_set_percent(int argc,char **argv)
{
    if(argc != 2)
    {
        rt_kprintf("please input car_set_percent <percent>\r\n");
        return -RT_ERROR;
    }
    else {
        pulse = atoi(argv[1]);
    }
    return RT_EOK;
}


int car_init(void)
{
    rt_err_t ret = RT_EOK;

    rt_pin_mode(AIN1_PIN, PIN_MODE_OUTPUT);
    rt_pin_mode(AIN2_PIN, PIN_MODE_OUTPUT);
    rt_pin_mode(BIN1_PIN, PIN_MODE_OUTPUT);
    rt_pin_mode(BIN2_PIN, PIN_MODE_OUTPUT);

    rt_pin_write(AIN1_PIN, PIN_LOW);
    rt_pin_write(AIN2_PIN, PIN_LOW);
    rt_pin_write(BIN1_PIN, PIN_LOW);
    rt_pin_write(BIN2_PIN, PIN_LOW);

    ret = pwm_init();


    return ret;
}

extern struct rt_device_pwm * pwm1;
extern struct rt_device_pwm * pwm2;
extern rt_uint32_t period;

int car_forward(void)
{
    rt_pwm_set(pwm1, PWM_CHANNEL1, period, period*pulse/100); //left
    rt_pwm_set(pwm2, PWM_CHANNEL2, period, period*pulse/100); //right
    rt_pin_write(AIN1_PIN, PIN_HIGH);
    rt_pin_write(AIN2_PIN, PIN_LOW);
    rt_pin_write(BIN1_PIN, PIN_HIGH);
    rt_pin_write(BIN2_PIN, PIN_LOW);
    my_pwm_enable();
    return RT_EOK;
}

int car_stop(void)
{
    rt_pin_write(AIN1_PIN, PIN_LOW);
    rt_pin_write(AIN2_PIN, PIN_LOW);
    rt_pin_write(BIN1_PIN, PIN_LOW);
    rt_pin_write(BIN2_PIN, PIN_LOW);
    my_pwm_disable();
    rt_kprintf("now car is stop\r\n");
    return RT_EOK;
}
//int a=25,b=50;
//int car_set(int argc,char **argv)
//{
//    if(argc==3)
//    {
//        a=atoi(argv[1]);
//        b=atoi(argv[2]);
//    }
//    return 0;
//}
//MSH_CMD_EXPORT(car_set,car_set);

int car_left(void)
{
    rt_pwm_set(pwm1, PWM_CHANNEL1, period, period*25/100); //left
    rt_pwm_set(pwm2, PWM_CHANNEL2, period, period*40/100); //right
    return 0;
}



int car_right(void)
{
   rt_err_t ret = RT_EOK;
   rt_pwm_set(pwm1,PWM_CHANNEL1,period, period * 30/100);
   rt_pwm_set(pwm2,PWM_CHANNEL2,period, period * 15/100);
   //rt_thread_mdelay(100);
//   rt_pwm_set(pwm1,PWM_CHANNEL1,period, period * pulse/100);
//   rt_pwm_set(pwm2,PWM_CHANNEL2,period, period * pulse/ 100);
   return ret;
}
extern float right_val;
extern int ffflag;
void car_cc_entery(void *parameter)
{
    while(1)
    {
        rt_kprintf("%d\n",ffflag);
        if(ffflag==0)
        {
            car_forward();
        }
        if(right_val>7&&ffflag==1)
        {
            ffflag=0;
            car_right();
        }
        else if(right_val<7&&ffflag==1)
        {
            ffflag=0;
            car_left();
        }
        rt_thread_mdelay(100);
    }
}

rt_thread_t cc_thread;
void car_cc_init(void)
{
    cc_thread = rt_thread_create("cc", car_cc_entery, RT_NULL, 1024, 8, 400);
    if(cc_thread)
    {
        rt_thread_startup(cc_thread);
    }
    else {
        LOG_D("start up cc error\n");
    }
}


#if CAR_MSH_ENABLE

MSH_CMD_EXPORT(car_set_percent , car set percent);
MSH_CMD_EXPORT(car_stop,car stop);
MSH_CMD_EXPORT(car_forward,car forward);

#endif

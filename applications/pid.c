/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-09-20     10091       the first version
 */
#include "pid.h"
#include "hc_pid.h"
#include "car.h"

#define DBG_TAG "pid"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>

extern rt_uint32_t number;
extern rt_uint32_t period,pulse;

extern struct rt_device_pwm * pwm1 ;
extern struct rt_device_pwm * pwm2 ;

rt_int32_t pwm_l,pwm_r;
rt_int32_t speed1;
rt_int32_t speed2;


int middle = 162;
float kp = 180089;
float ki = -2.33;
float kd = 81;
float dia=0;

int val_flag=1;


rt_thread_t pid_thread = RT_NULL;

void pwm_limit(rt_int32_t * pwm1,rt_int32_t * pwm2)
{
    if(*pwm1>1000000) *pwm1=1000000;
    else if(*pwm1<-1000000) *pwm1=-1000000;

    if(*pwm2>1000000) *pwm2=1000000;
    else if(*pwm2<-1000000) *pwm2=-1000000;
}

void pwm_abs(rt_int32_t pwm_1,rt_int32_t pwm_2)
{

    if(pwm_1<0)
        {
            rt_pin_write(AIN2_PIN, PIN_HIGH);
            rt_pin_write(AIN1_PIN, PIN_LOW);
            pwm_1 = -pwm_1;
        }
        else if(pwm_1>=0)
        {
            rt_pin_write(AIN1_PIN, PIN_HIGH);
            rt_pin_write(AIN2_PIN, PIN_LOW);
        }
        if(pwm_2<0)
        {
            rt_pin_write(BIN2_PIN, PIN_HIGH);
            rt_pin_write(BIN1_PIN, PIN_LOW);
            pwm_2 = -pwm_2;
        }
        else if(pwm_2>=0)
        {
            rt_pin_write(BIN1_PIN, PIN_HIGH);
            rt_pin_write(BIN2_PIN, PIN_LOW);
        }
        pwm_limit(&pwm_1, &pwm_2);
        rt_pwm_set(pwm1, PWM_CHANNEL1, period,(rt_uint32_t) pwm_1);
        rt_pwm_set(pwm2, PWM_CHANNEL2, period,(rt_uint32_t) pwm_2);
}


float error=0,ierror=0,derror=0,errorlast=0;
void pid_compute(int val)
{
    speed1 = period*25/100;
    speed2 = period*40/100;
    error = middle*1.0 - val;
    ierror=ierror+error;
    derror=error-errorlast;
    errorlast=error;
    if(ierror>3000) ierror=3000;
    else if(ierror<-3000) ierror=-3000;
    dia = kp*error/100.0+ki*ierror+kd*derror/10.0;
    pwm_l = speed1 - dia;
    pwm_r = speed2 + dia;
    pwm_abs(pwm_l, pwm_r);
}



int pid_set(int argc,char **argv)
{
    if(argc<4)
    {
        rt_kprintf("the format is <kp> <ki> <kd>\r\n");
    }
    else {
        kp = atof(argv[1]);
        ki = atof(argv[2]);
        kd = atof(argv[3]);
        rt_kprintf("SET OK ! KP:%f KI:%f KD:%f",kp,ki,kd);
    }
    return RT_EOK;
}
MSH_CMD_EXPORT(pid_set,pid parameter set);



rt_uint32_t num=0;
extern float right_val,left_val;
void pid_thread_entry(void *parameter)
{
    while(1)
    {
//        speed = period*pulse/100;
        num = left_val;
        dia = 0;
        if(num<10)
            hc_pid_compute(num);

        else if(num>200)
        {
            car_forward();
        }

        rt_thread_mdelay(50);
    }
}

int pid_init(void)
{
    pid_thread = rt_thread_create("pid_thread", pid_thread_entry, RT_NULL, 1024, 13, 300);
    if(pid_thread)
    {
        rt_thread_startup(pid_thread);
    }
    else {
        rt_kprintf("create pid_thread error\r\n");
        return -RT_ERROR;
    }
    return RT_EOK;
}

void pid_clear(void)
{
    num = 0;
    number=0;
    error=0;
    ierror=0;
    derror=0;
    errorlast=0;
}







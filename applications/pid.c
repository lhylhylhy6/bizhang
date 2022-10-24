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
#define DBG_TAG "pid"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>

extern rt_uint32_t number;
extern rt_uint32_t period,pulse;
extern rt_mutex_t number_protect;

extern struct rt_device_pwm * pwm1 ;
extern struct rt_device_pwm * pwm2 ;

rt_int32_t pwm_l,pwm_r;
rt_int32_t speed;
int middle = 162;
float kp = 180089;
float ki = -2.33;
float kd = 81;
float dia=0;

int val_flag=1;


rt_thread_t pid_thread = RT_NULL;
rt_mutex_t pid_completion;



float error=0,ierror=0,derror=0,errorlast=0;
void pid_compute(int val)
{

    error = middle*1.0 - val;
    ierror=ierror+error;
    derror=error-errorlast;
    errorlast=error;
    if(ierror>3000) ierror=3000;
    else if(ierror<-3000) ierror=-3000;
    dia = kp*error/100.0+ki*ierror+kd*derror/10.0;
    pwm_l = speed - dia;
    pwm_r = speed + dia;
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
extern float right_val;
void pid_thread_entry(void *parameter)
{

    while(1)
    {
        speed = period*pulse/100;

        //rt_mutex_take(number_protect, RT_WAITING_FOREVER);
//        if(val_flag==1)
//            num = number;
//        else if(val_flag==2)
//        {
//            num = right_val;
//        }
        num = right_val;
        //rt_mutex_release(number_protect);
        dia = 0;

        rt_mutex_take(pid_completion, RT_WAITING_FOREVER);
        hc_pid_compute(num);
        rt_mutex_release(pid_completion);
        rt_thread_mdelay(10);
    }
}

int pid_init(void)
{
    pid_completion = rt_mutex_create("pid_compl", RT_IPC_FLAG_PRIO);
    pid_thread = rt_thread_create("pid_thread", pid_thread_entry, RT_NULL, 1024, 9, 300);
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







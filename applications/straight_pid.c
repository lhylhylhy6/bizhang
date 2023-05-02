/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-10-27     lhylh       the first version
 */
#include "straight_pid.h"
#include "car.h"

#define DBG_TAG "straight_pid"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>

rt_uint8_t str_control_flag=1;

extern rt_uint32_t number;
extern rt_uint32_t period,pulse;

extern struct rt_device_pwm * pwm1 ;
extern struct rt_device_pwm * pwm2 ;
extern struct rt_completion straight_comp;
extern rt_uint32_t sp_pulse;
extern rt_uint32_t ov_location;
extern struct rt_completion ov_comp;

rt_int32_t pwm_l,pwm_r;
rt_int32_t speed;


int straight_middle = 165;
float straight_kp =0.1;
float straight_ki =0;
float straight_kd =0;

float straight_dia=0;

rt_thread_t straight_pid_thread = RT_NULL;

void straight_pwm_limit(rt_int32_t * pwm1,rt_int32_t * pwm2)
{
    if(*pwm1>80) *pwm1=80;
    if(*pwm2>80) *pwm2=80;
}

void straight_pwm_abs(rt_int32_t pwm_1,rt_int32_t pwm_2)
{

    if(pwm_1<0)
    {
        pwm_1 = 0;
    }
    if(pwm_2<0)
    {
        pwm_2 = 0;
    }
    straight_pwm_limit(&pwm_1, &pwm_2);
//    LOG_D("%d %d \n",pwm_1,pwm_2);
    rt_pwm_set(pwm1, PWM_CHANNEL1, period,(rt_uint32_t) pwm_1*period/100);
    rt_pwm_set(pwm2, PWM_CHANNEL2, period,(rt_uint32_t) pwm_2*period/100);
}


float error2=0,ierror2=0,derror2=0,errorlast2=0;
void straight_pid_compute(int val)
{
    error2 = straight_middle*1.0 - val;
    ierror2=ierror2+error2;
    derror2=error2-errorlast2;
    errorlast2=error2;
    if(ierror2>3000) ierror2=3000;
    else if(ierror2<-3000) ierror2=-3000;
    straight_dia = straight_kp*error2+straight_ki*ierror2+straight_kd*derror2;
    pwm_l = pulse - (rt_int32_t)straight_dia;
    pwm_r = pulse + (rt_int32_t)straight_dia;
//    LOG_D("%d %f %d\n",pulse,straight_dia,pwm_l);
    straight_pwm_abs(pwm_l, pwm_r);
}



int straight_pid_set(int argc,char **argv)
{
    if(argc<4)
    {
        LOG_D("the format is <kp> <ki> <kd>\r\n");
    }
    else {
        straight_kp = atof(argv[1]);
        straight_ki = atof(argv[2]);
        straight_kd = atof(argv[3]);
        LOG_D("SET OK ! KP:%f KI:%f KD:%f",straight_kp,straight_ki,straight_kd);
    }
    return RT_EOK;
}
MSH_CMD_EXPORT(straight_pid_set,pid parameter set);


//extern int turn_flag;
rt_uint32_t staraight_num=0;
void straight_pid_thread_entry(void *parameter)
{
    while(1)
    {
//        if(turn_flag)
//        {
//             rt_thread_suspend(straight_pid_thread);
//             rt_schedule();
//        }
        if(str_control_flag)
        {
            rt_completion_wait(&ov_comp, RT_WAITING_FOREVER);
            staraight_num = ov_location;
            straight_dia = 0;
            straight_pid_compute(staraight_num);
        }
        rt_thread_mdelay(50);
    }
}

int straight_pid_init(void)
{
    straight_pid_thread = rt_thread_create("straight_pid_thread", straight_pid_thread_entry, RT_NULL, 1024, 7, 300);
    if(straight_pid_thread)
    {
        rt_thread_startup(straight_pid_thread);
    }
    else {
        rt_kprintf("create pid_thread error\r\n");
        return -RT_ERROR;
    }
    return RT_EOK;
}

void straight_pid_clear(void)
{
    staraight_num = 0;
    number=0;
    error2=0;
    ierror2=0;
    derror2=0;
    errorlast2=0;
}

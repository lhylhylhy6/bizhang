/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-10-29     10091       the first version
 */
#include <ov_pid.h>
#include "car_pwm.h"

rt_uint8_t ov_control_flag=1;

rt_thread_t ov_pid_compute;
rt_uint32_t max_pulse = 120,min_pulse = 20;
rt_uint32_t ov_mid_pulse = 75;
struct rt_completion straight_comp;


extern struct rt_completion ov_comp;
extern rt_uint32_t ov_location;
extern struct rt_device_pwm * yuntai_dev;
extern rt_uint32_t yuntai_period;
extern rt_uint32_t sp_pulse;
extern rt_uint32_t sz_pulse;
/*
 * 中间75 右打死 20 左打死130
 */

int middle = 165;
float kp =  -0.0805;
float ki = 0;
float kd = 0.006;
float dia=0;
float error=0,ierror=0,derror=0,errorlast=0;
rt_uint32_t old_pulse = 75;
int angle_limit(rt_uint32_t *angle)
{
    if(*angle<min_pulse)
        *angle = min_pulse;
    else if (*angle>max_pulse) {
        *angle = max_pulse;
    }

//    rt_kprintf("%d\n",*angle);
    rt_pwm_set(yuntai_dev,SP_CHANNEL, yuntai_period, yuntai_period*(*angle)/1000);

    return RT_EOK;
}

int direction_pid_compute(rt_int32_t val)
{
       error = middle*1.0 - val;
       ierror=ierror+error;
       derror=error-errorlast;
       errorlast=error;
       if(ierror>3000) ierror=3000;
       else if(ierror<-3000) ierror=-3000;
       dia = kp*error+ki*ierror+kd*derror;
       sp_pulse = sp_pulse-dia; //125-25

       return 0;
}

void ov_pid_entry(void *parameter)
{
    while(1)
    {
        if(ov_control_flag)
        {
            rt_completion_wait(&ov_comp, RT_WAITING_FOREVER);
            dia = 0;
            direction_pid_compute(ov_location);
            angle_limit(&sp_pulse);
            rt_completion_done(&straight_comp);
        }
        rt_thread_mdelay(10);
    }
}


int ov_pid_init(void)
{
    rt_err_t err = RT_EOK;
    rt_completion_init(&straight_comp);
    ov_pid_compute = rt_thread_create("ov_pid", ov_pid_entry, RT_NULL, 1024, 7, 300);
    if(ov_pid_compute)
    {
       rt_kprintf("ov_pid_thread create successfully\n");
       rt_thread_startup(ov_pid_compute);
    }
    else {
        rt_kprintf("ov_pid_thread create error\n");
    }
    return err;
}

int ov_pid_set(int argc,char **argv)
{
    if(argc < 4)
    {
        rt_kprintf("Too few parameters\n");
        return error;
    }
    kp =  atof(argv[1]);
    ki =  atof(argv[2]);
    kd =  atof(argv[3]);
    rt_kprintf("ov_pid set ok\n");
    return RT_EOK;
}
void ov_pid_clearn(void)
{
    error=0;
    ierror=0;
    derror=0;
    errorlast=0;
}
MSH_CMD_EXPORT(ov_pid_set,ov_pid parameter set);

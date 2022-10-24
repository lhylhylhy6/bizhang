/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-10-23     10091       the first version
 */
#include "hc_pid.h"

int middle1 = 10;
float kp1 = 500;
float ki1 = 0;
float kd1 = 0;
float dia1=0;

extern rt_uint32_t period,pulse;
extern struct rt_device_pwm * pwm1 ;
extern struct rt_device_pwm * pwm2 ;

extern rt_int32_t pwm_l,pwm_r;
extern rt_int32_t speed;

void hc_pwm_limit(rt_int32_t * pwm1,rt_int32_t * pwm2)
{
    if(*pwm1>1000000) *pwm1=1000000;
    else if(*pwm1<-1000000) *pwm1=-1000000;

    if(*pwm2>1000000) *pwm2=1000000;
    else if(*pwm2<-1000000) *pwm2=-1000000;
}

void hc_pwm_abs(rt_int32_t pwm_1,rt_int32_t pwm_2)
{

    if(pwm_1<0)
    {
        pwm_1 = 0;
    }
    else if(pwm_1>=0)
    {
        rt_pin_write(AIN1_PIN, PIN_HIGH);
        rt_pin_write(AIN2_PIN, PIN_LOW);
    }
    if(pwm_2<0)
    {
        pwm_2 = 0;
    }
    else if(pwm_2>=0)
    {
        rt_pin_write(BIN1_PIN, PIN_HIGH);
        rt_pin_write(BIN2_PIN, PIN_LOW);
    }

    hc_pwm_limit(&pwm_1, &pwm_2);
    static int i=0;
    i++;
    if(i==100)
    {
        i = 0;
        rt_kprintf("%d %d\n",pwm_1,pwm_2);
    }

    rt_pwm_set(pwm1, PWM_CHANNEL1, period,(rt_uint32_t) pwm_1);
    rt_pwm_set(pwm2, PWM_CHANNEL2, period,(rt_uint32_t) pwm_2);
}

float error1=0,ierror1=0,derror1=0,errorlast1=0;
int hc_pid_compute(int val)
{
    if(val>100)
        return 0;
    error1 = middle1*1.0 - val;
    ierror1=ierror1+error1;
    derror1=error1-errorlast1;
    errorlast1=error1;
    if(ierror1>3000) ierror1=3000;
    else if(ierror1<-3000) ierror1=-3000;
    dia1 = kp1*error1+ki1*ierror1+kd1*derror1;
    pwm_l = speed - dia1;
    pwm_r = speed + dia1;
    hc_pwm_abs(pwm_l, pwm_r);

}


int hc_pid_set(int argc,char **argv)
{
    if(argc<4)
    {
        rt_kprintf("the format is <kp> <ki> <kd>\r\n");
    }
    else {
        kp1 = atof(argv[1]);
        ki1 = atof(argv[2]);
        kd1 = atof(argv[3]);
        rt_kprintf("SET OK ! KP:%f KI:%f KD:%f",kp1,ki1,kd1);
    }
    return RT_EOK;
}
MSH_CMD_EXPORT(hc_pid_set,pid parameter set);

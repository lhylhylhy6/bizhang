/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-09-20     10091       the first version
 */
#include "car_pwm.h"

#define DBG_TAG "pwm"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>

#define AIN1_PIN GET_PIN(F, 6)
#define AIN2_PIN GET_PIN(F, 7)
#define BIN1_PIN GET_PIN(F, 8)
#define BIN2_PIN GET_PIN(F, 9)

struct rt_device_pwm * pwm1 = RT_NULL;
struct rt_device_pwm * pwm2 = RT_NULL;

rt_uint32_t period = 1000000 ;
rt_uint32_t pulse = 25;

int pwm_init(void)
{
    rt_err_t ret;
    pwm1 = (struct rt_device_pwm *)rt_device_find(PWM_DEVICE_NAME1);
    pwm2 = (struct rt_device_pwm *)rt_device_find(PWM_DEVICE_NAME2);
    if(pwm1)
    {
        ret = rt_pwm_set(pwm1, PWM_CHANNEL1, period, (period*pulse)/100);
        if(ret<0)
            LOG_D("ret1: %d\r\n",ret);
        rt_pwm_enable(pwm1, PWM_CHANNEL1);
    }
    ret = RT_EOK;
    if(pwm2)
    {
        ret = rt_pwm_set(pwm2, PWM_CHANNEL2, period, (period*pulse)/100);
        if(ret<0)
            LOG_D("ret2: %d\r\n",ret);
        rt_pwm_enable(pwm2, PWM_CHANNEL2);
    }
    ret = rt_pwm_disable(pwm1, PWM_CHANNEL1);
    ret = rt_pwm_disable(pwm2, PWM_CHANNEL2);
    return ret;
}


rt_err_t my_pwm_enable(void)
{
    rt_err_t ret = RT_EOK;
    ret = rt_pwm_enable(pwm1, PWM_CHANNEL1);
    ret = rt_pwm_enable(pwm2, PWM_CHANNEL2);
    return ret;
}

rt_err_t my_pwm_disable(void)
{
    rt_err_t ret = RT_EOK;
    ret = rt_pwm_disable(pwm1, PWM_CHANNEL1);
    ret = rt_pwm_disable(pwm2, PWM_CHANNEL2);
    return ret;
}






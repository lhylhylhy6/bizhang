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
#include "car.h"

#define DBG_TAG "pwm"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>

struct rt_device_pwm * pwm1 = RT_NULL;
struct rt_device_pwm * pwm2 = RT_NULL;

struct rt_device_pwm * yuntai_dev = RT_NULL;

rt_uint32_t period = 1000000 ;
rt_uint32_t pulse = 50;

rt_uint32_t yuntai_period = 20000000 ;
rt_uint32_t sp_pulse  = 75; //zuo 120  zhong 75 you 20
rt_uint32_t sz_pulse  = 85;//zhong 85  xia 110

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
    else {
        rt_kprintf("error");
    }
    ret = RT_EOK;
    if(pwm2)
    {
        ret = rt_pwm_set(pwm2, PWM_CHANNEL2, period, (period*pulse)/100);
        if(ret<0)
            LOG_D("ret2: %d\r\n",ret);
        rt_pwm_enable(pwm2, PWM_CHANNEL2);
    }

    yuntai_dev = (struct rt_device_pwm *)rt_device_find(YUNTAI_PWM);
    if(yuntai_dev)
    {
        ret = rt_pwm_set(yuntai_dev, SP_CHANNEL, yuntai_period, (yuntai_period*sp_pulse)/1000);
        ret = rt_pwm_set(yuntai_dev, SZ_CHANNEL, yuntai_period, (yuntai_period*sz_pulse)/1000);
        rt_pwm_enable(yuntai_dev, SP_CHANNEL);
        rt_pwm_enable(yuntai_dev, SZ_CHANNEL);
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

int my_pwm_extern_set_pulse(int argc,char **argv)
{
    char *dev_name;
    rt_uint32_t new_pulse=0;
    if(argc>=2)
    {
        dev_name = argv[1];
        new_pulse = atoi(argv[2]);

        if(strcmp(dev_name,"left")==0)
        {
            rt_pin_write(AIN1_PIN, PIN_HIGH);
            rt_pin_write(AIN2_PIN, PIN_LOW);
            rt_pin_write(BIN1_PIN, PIN_HIGH);
            rt_pin_write(BIN2_PIN, PIN_LOW);
            my_pwm_enable();
            rt_pwm_set(pwm1,PWM_CHANNEL1,period, period*new_pulse/100);
        }
        else if(strcmp(dev_name,"right")==0)
        {
            rt_pin_write(AIN1_PIN, PIN_HIGH);
            rt_pin_write(AIN2_PIN, PIN_LOW);
            rt_pin_write(BIN1_PIN, PIN_HIGH);
            rt_pin_write(BIN2_PIN, PIN_LOW);
            my_pwm_enable();
            rt_pwm_set(pwm2,PWM_CHANNEL2,period, period*new_pulse/100);
        }
        else if(strcmp(dev_name,"sp")==0)
        {
            rt_pwm_set(yuntai_dev, SP_CHANNEL, yuntai_period, yuntai_period*new_pulse/1000);
        }
        else if(strcmp(dev_name,"sz")==0)
        {
            rt_pwm_set(yuntai_dev, SZ_CHANNEL, yuntai_period, yuntai_period*new_pulse/1000);
        }
    }
    else
    {
        rt_kprintf("please input my_pwm_extern_set_pulse <dev_name> <new_pulse>\r\n");
        rt_kprintf("<dev_name> can be left/right/sp/sz \r\n");
    }

    return 0;
}
MSH_CMD_EXPORT(my_pwm_extern_set_pulse,my_pwm_extern_set_pulse);




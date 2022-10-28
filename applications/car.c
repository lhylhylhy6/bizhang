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
#include "hc_pid.h"
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

int car_left(void)
{
    rt_pwm_set(pwm1, PWM_CHANNEL1, period, period*25/100); //left
    rt_pwm_set(pwm2, PWM_CHANNEL2, period, period*40/100); //right
    rt_pin_write(AIN1_PIN, PIN_HIGH);
    rt_pin_write(AIN2_PIN, PIN_LOW);
    rt_pin_write(BIN1_PIN, PIN_HIGH);
    rt_pin_write(BIN2_PIN, PIN_LOW);
    my_pwm_enable();
    return 0;
}


int car_right_angle(void)
{

      int level;
      level = rt_hw_interrupt_disable();
      LOG_D("car_turn_right  start\n");
      rt_pin_write(AIN1_PIN, PIN_LOW);
      rt_pin_write(AIN2_PIN, PIN_HIGH);
      rt_pin_write(BIN1_PIN, PIN_HIGH);
      rt_pin_write(BIN2_PIN, PIN_LOW);
      rt_pwm_set(pwm1, PWM_CHANNEL1, period, period*40/100); //left
      rt_pwm_set(pwm2, PWM_CHANNEL2, period, period*90/100); //right
      my_pwm_enable();
      for(int i=0;i<3;i++)
      {
          for(int ii=0;ii<2000;ii++)
          {
              for(int iii=0;iii<1000;iii++)
              {

              }
          }
      }
      rt_hw_interrupt_enable(level);
      LOG_D("car_turn_right over\n");
      return 0;
}
#if 0
int limit = 4600;
int set_right_delay(int argc,char **argv)
{
    if(argc != 2)
    {
        rt_kprintf("please input car_left angle\r\n");
        return -RT_ERROR;
    }
    else {
        limit = atoi(argv[1]);
    }
    return RT_EOK;

}


int set_left_delay(int argc,char **argv)
{
    if(argc != 2)
    {
        rt_kprintf("please input car_left angle\r\n");
        return -RT_ERROR;
    }
    else {
        limit = atoi(argv[1]);
    }
    return RT_EOK;

}
#endif
int car_left_angle(void)
{
      int level;
      LOG_D("car_turn_left  start\n");
      level = rt_hw_interrupt_disable();
      rt_pin_write(AIN1_PIN, PIN_HIGH);
      rt_pin_write(AIN2_PIN, PIN_LOW);
      rt_pin_write(BIN1_PIN, PIN_LOW);
      rt_pin_write(BIN2_PIN, PIN_HIGH);
      rt_pwm_set(pwm1, PWM_CHANNEL1, period, period*90/100); //left
      rt_pwm_set(pwm2, PWM_CHANNEL2, period, period*40/100); //right
      my_pwm_enable();
      for(int i=0;i<3;i++)
      {
          for(int ii=0;ii<2300;ii++)
          {
              for(int iii=0;iii<1000;iii++)
              {

              }
          }
      }
      rt_hw_interrupt_enable(level);
      LOG_D("car_turn_left  over\n");
      return 0;
}

int car_right(void)
{
   rt_err_t ret = RT_EOK;
   rt_pwm_set(pwm1,PWM_CHANNEL1,period, period * 30/100);
   rt_pwm_set(pwm2,PWM_CHANNEL2,period, period * 15/100);
   return ret;
}



#if CAR_MSH_ENABLE

MSH_CMD_EXPORT(car_set_percent , car set percent);
MSH_CMD_EXPORT(car_stop,car stop);
MSH_CMD_EXPORT(car_forward,car forward);
MSH_CMD_EXPORT(car_left_angle,car_left);
MSH_CMD_EXPORT(car_right_angle,car_right);
//MSH_CMD_EXPORT(set_left_delay,car_left_delay);
//MSH_CMD_EXPORT(set_right_delay,car_right_delay);
#endif

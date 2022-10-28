/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-10-22     lhylh       the first version
 */
/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-10-22     lhylh       the first version
// */
#include "hcsr04.h"
#include "stdlib.h"
#include "car_pwm.h"
#include "car.h"
#define DBG_TAG "hcsr04"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>

#define CMP_MID_VAL    20


#define Left_HC_Trig_Pin        GET_PIN(F,3)
#define Left_HC_Echo_Pin        GET_PIN(F,4)

#define Right_HC_Trig_Pin       GET_PIN(F,1)
#define Right_HC_Echo_Pin       GET_PIN(F,2)

#define Mid_HC_Trig_Pin         GET_PIN(F,5)
#define Mid_HC_Echo_Pin         GET_PIN(F,0)

rt_thread_t mid_hc_thread;
rt_thread_t left_hc_thread;
rt_thread_t right_hc_thread;

extern rt_thread_t pid_read_thread;
extern rt_thread_t straight_pid_thread;
extern struct rt_device_pwm * pwm1;
extern struct rt_device_pwm * pwm2;
extern rt_uint32_t period;
extern int val_flag;

float mid_val;
float left_val;
float right_val;

int turn_flag = 0;

int HCSR_pin_init(void)
{
    rt_pin_mode(Left_HC_Trig_Pin,PIN_MODE_OUTPUT);
    rt_pin_mode(Left_HC_Echo_Pin,PIN_MODE_INPUT);

    rt_pin_mode(Right_HC_Trig_Pin,PIN_MODE_OUTPUT);
    rt_pin_mode(Right_HC_Echo_Pin,PIN_MODE_INPUT);

    rt_pin_mode(Mid_HC_Trig_Pin,PIN_MODE_OUTPUT);
    rt_pin_mode(Mid_HC_Echo_Pin,PIN_MODE_INPUT);
    return 0;
}
INIT_APP_EXPORT(HCSR_pin_init);


static void hcsr_mid_thread_entry(void *parameter)
{
    int count = 0 ,S = 0,i=0;
    while(1)
    {
        for(i=0;i<2;i++)
        {
            rt_pin_write(Mid_HC_Trig_Pin,PIN_HIGH);
            rt_hw_us_delay(10);
            rt_pin_write(Mid_HC_Trig_Pin,PIN_LOW);
            while(!rt_pin_read(Mid_HC_Echo_Pin))
            {
                int a=0;
                a++;
                rt_hw_us_delay(50);
                if(a>200)
                    goto __exit;
            }
            while(rt_pin_read(Mid_HC_Echo_Pin))
            {
                count++;
                rt_hw_us_delay(50);
            }
            S = 17*count +S;
            count = 0;
            rt_thread_mdelay(20);
        }
        mid_val = S/40.0;
        //LOG_D("mid : S = %f cm\n",mid_val);
        if(mid_val<=CMP_MID_VAL)
        {
            turn_flag = 1;
            car_stop();
            car_right_angle();
            HCSR_left_init();
            HCSR_right_init();
            rt_thread_suspend(mid_hc_thread);
            rt_schedule();
        }
__exit:
        S=0;
        count=0;
        rt_thread_mdelay(50);
    }
}

static void hcsr_left_thread_entry(void *parameter)
{
    int count = 0 ,S = 0,i=0;

    while(1)
    {
        if(turn_flag == 0)
        {
            rt_thread_suspend(right_hc_thread);
            rt_schedule();
        }
        for(i=0;i<2;i++)
        {
            rt_pin_write(Left_HC_Trig_Pin,PIN_HIGH);
            rt_hw_us_delay(10);
            rt_pin_write(Left_HC_Trig_Pin,PIN_LOW);
            while(!rt_pin_read(Left_HC_Echo_Pin))
            {
                int a=0;
                a++;
                rt_hw_us_delay(50);

                if(a>500)
                    goto __exit;
            }
            while(rt_pin_read(Left_HC_Echo_Pin))
            {
                count++;
                rt_hw_us_delay(50);
            }
            S = 17*count +S;
            count = 0;
            rt_thread_mdelay(20);
        }
        left_val = S/40.0;
        //LOG_D("left : S = %f cm\n",left_val);
__exit:
        S=0;
        count=0;
        rt_thread_mdelay(50);
    }
}

static void hcsr_right_thread_entry(void *parameter)
{
    int count = 0 ,S = 0,i=0;
    while(1)
    {
        if(turn_flag==0)
        {
            rt_thread_suspend(right_hc_thread);
            rt_schedule();
        }
        for(i=0;i<2;i++)
        {
            rt_pin_write(Right_HC_Trig_Pin,PIN_HIGH);
            rt_hw_us_delay(10);
            rt_pin_write(Right_HC_Trig_Pin,PIN_LOW);
            while(!rt_pin_read(Right_HC_Echo_Pin));
            {
                int a=0;
                a++;
                rt_hw_us_delay(50);
                if(a>200)
                {
                    goto __exti;
                }

            }
            while(rt_pin_read(Right_HC_Echo_Pin))
            {
                count++;
                rt_hw_us_delay(50);
            }
            S = 17*count +S;
            count = 0;
            rt_thread_mdelay(50);
        }
        right_val=S/40.0;
        //LOG_D("right : S = %f cm\n",right_val);
__exti:
        S=0;
        count=0;
        rt_thread_mdelay(50);
    }
}

rt_err_t HCSR_left_init(void)
{
    rt_err_t ree = RT_EOK;
    left_hc_thread = rt_thread_create("left_hc", hcsr_left_thread_entry, RT_NULL, 1024, 15, 150);
    if(left_hc_thread)
    {
        ree = rt_thread_startup(left_hc_thread);
        LOG_D("left_hc_thread start ok!\r\n");
    }
    return ree;
}

rt_err_t HCSR_mid_init(void)
{
    rt_err_t ree=RT_EOK;

    mid_hc_thread = rt_thread_create("mid_hc", hcsr_mid_thread_entry, RT_NULL, 1024, 15, 200);
    if(mid_hc_thread)
    {
        ree = rt_thread_startup(mid_hc_thread);
        LOG_D("mid_hc_thread start ok!\r\n");
    }

    return ree;
}

rt_err_t HCSR_right_init(void)
{
    rt_err_t ree = RT_EOK;
    right_hc_thread = rt_thread_create("right_hc", hcsr_right_thread_entry, RT_NULL, 1024,15, 200);
    if(right_hc_thread)
    {
        ree = rt_thread_startup(right_hc_thread);
        LOG_D("right_hc_thread start ok!\r\n");
    }
    return ree;
}

void hcsr_read(int argc,char **argv)
{
    int switch_num=0;
    int trig=0,echo=0;
    int times=3;
    char str[8]="mid";
    if(argc==2)
    {
        switch_num = atoi(argv[1]);
    }
    else if(argc==3)
    {
        switch_num = atoi(argv[1]);
        times = atoi(argv[2]);
    }
    switch(switch_num)
    {
        case 1:trig=Left_HC_Trig_Pin;echo=Left_HC_Echo_Pin;     sprintf(str,"left"); break;
        case 2:trig=Right_HC_Trig_Pin;echo=Right_HC_Echo_Pin;       sprintf(str,"right");break;
        case 3:trig=Mid_HC_Trig_Pin;echo=Mid_HC_Echo_Pin;   sprintf(str,"mid");break;
        default:trig=Left_HC_Trig_Pin;echo=Left_HC_Echo_Pin;    sprintf(str,"left");
    }

    while(times--)
    {
        int count=0,i=0,S=0;
        double cmval = 0.0;
        for(i=0;i<5;i++)
        {
            rt_pin_write(trig,PIN_HIGH);
            rt_hw_us_delay(10);
            rt_pin_write(trig,PIN_LOW);
            while(!rt_pin_read(echo));
            while(rt_pin_read(echo))
            {
                count++;
                rt_hw_us_delay(50);
            }
            S = 17*count +S;
            count = 0;
            rt_thread_mdelay(50);
        }
        cmval=S/100.0;
        LOG_D("%s : S = %f cm\n",str,cmval);
        S=0;
        count=0;
        cmval=0;
    }
}
MSH_CMD_EXPORT(hcsr_read,hcsr_read);

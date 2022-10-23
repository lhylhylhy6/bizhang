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
 */
#include "hcsr04.h"
#include "string.h"

#define DBG_TAG "hcsr04"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>

#define EN_LEFT_HC      1
#define EN_RIGHT_HC     1
#define EN_MID_HC       1

#define Left_HC_Trig_Pin        GET_PIN(F,1)
#define Left_HC_Echo_Pin        GET_PIN(F,2)

#define Right_HC_Trig_Pin       GET_PIN(F,3)
#define Right_HC_Echo_Pin       GET_PIN(F,4)

#define Mid_HC_Trig_Pin         GET_PIN(F,5)
#define Mid_HC_Echo_Pin         GET_PIN(F,6)

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
    float cmval=0;
    while(1)
    {
        for(i=0;i<5;i++)
        {
            rt_pin_write(Mid_HC_Trig_Pin,PIN_HIGH);
            rt_hw_us_delay(10);
            rt_pin_write(Mid_HC_Trig_Pin,PIN_LOW);
            while(!rt_pin_read(Mid_HC_Echo_Pin));
            while(rt_pin_read(Mid_HC_Echo_Pin))
            {
                count++;
                rt_hw_us_delay(50);
            }
            S = 17*count +S;
            count = 0;
            rt_thread_mdelay(50);
        }
        cmval=S/100.0;
        LOG_D("mid : S = %d cm\n",cmval);
    }
}

static void hcsr_left_thread_entry(void *parameter)
{
    int count = 0 ,S = 0,i=0;
    float cmval=0;
    while(1)
    {
        for(i=0;i<5;i++)
        {
            rt_pin_write(Left_HC_Trig_Pin,PIN_HIGH);
            rt_hw_us_delay(10);
            rt_pin_write(Left_HC_Trig_Pin,PIN_LOW);
            while(!rt_pin_read(Left_HC_Echo_Pin));
            while(rt_pin_read(Left_HC_Echo_Pin))
            {
                count++;
                rt_hw_us_delay(50);
            }
            S = 17*count +S;
            count = 0;
            rt_thread_mdelay(50);
        }
        cmval=S/100.0;
        LOG_D("left : S = %d cm\n",cmval);
    }
}

static void hcsr_right_thread_entry(void *parameter)
{
    int count = 0 ,S = 0,i=0;
    float cmval=0;
    while(1)
    {
        for(i=0;i<5;i++)
        {
            rt_pin_write(Right_HC_Trig_Pin,PIN_HIGH);
            rt_hw_us_delay(10);
            rt_pin_write(Right_HC_Trig_Pin,PIN_LOW);
            while(!rt_pin_read(Right_HC_Echo_Pin));
            while(rt_pin_read(Right_HC_Echo_Pin))
            {
                count++;
                rt_hw_us_delay(50);
            }
            S = 17*count +S;
            count = 0;
            rt_thread_mdelay(50);
        }
        cmval=S/100.0;
        LOG_D("right : S = %d cm\n",cmval);
    }
}

rt_err_t HCSR_init(void)
{
    rt_err_t ree=RT_EOK;

#if EN_LEFT_HC
    rt_thread_t left_hc_thread;
    left_hc_thread = rt_thread_create("left_hc", hcsr_left_thread_entry, RT_NULL, 512, 1, 400);
    if(left_hc_thread)
    {
        ree = rt_thread_startup(left_hc_thread);
        LOG_D("left_hc_thread start ok!\r\n");
    }
#endif
#if EN_RIGHT_HC
    rt_thread_t right_hc_thread;
    right_hc_thread = rt_thread_create("right_hc", hcsr_right_thread_entry, RT_NULL, 512, 1, 400);
    if(right_hc_thread)
    {
        ree = rt_thread_startup(right_hc_thread);
        LOG_D("right_hc_thread start ok!\r\n");
    }
#endif
#if EN_MID_HC
    rt_thread_t mid_hc_thread;
    mid_hc_thread = rt_thread_create("mid_hc", hcsr_mid_thread_entry, RT_NULL, 512, 1, 400);
    if(mid_hc_thread)
    {
        ree = rt_thread_startup(mid_hc_thread);
        LOG_D("mid_hc_thread start ok!\r\n");
    }
#endif
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
        case 2:trig=Mid_HC_Trig_Pin;echo=Mid_HC_Echo_Pin;       sprintf(str,"mid");break;
        case 3:trig=Right_HC_Trig_Pin;echo=Right_HC_Echo_Pin;   sprintf(str,"right");break;
        default:trig=Mid_HC_Trig_Pin;echo=Mid_HC_Echo_Pin;
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

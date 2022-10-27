/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-09-20     RT-Thread    first version
 */

#include <rtthread.h>
#include "uart2.h"
#include "car.h"
#include "hcsr04.h"
#include "hc_pid.h"
#define DBG_TAG "main"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>
#include "car_pwm.h"

extern rt_uint32_t number;
extern int middle;
extern rt_int32_t pwm_l,pwm_r;
int main(void)
{
    //pid_uart_init();
    car_init();
    HCSR_init();
    hc_pid_init();
    car_forward();
    car_left();
    rt_kprintf("init all ok!\r\n");
    while (1)
    {
        car_left();
        rt_thread_mdelay(50);
    }

    return RT_EOK;
}

int restart(void)
{
    rt_hw_cpu_reset();
    return RT_EOK;
}
MSH_CMD_EXPORT(restart , restart);

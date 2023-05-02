/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-09-20     10091       the first version
 */
#include "uart2.h"
#include "car.h"

rt_uint8_t is_color=0;

rt_sem_t rx_sem;
rt_device_t pid_uart = RT_NULL;
rt_uint32_t number = 0;
rt_uint32_t ov_location = 0;
rt_thread_t pid_read_thread;
struct rt_completion ov_comp;

extern int turn_flag;
extern rt_uint8_t red_flag;
rt_err_t pid_uart_rx_inter(rt_device_t dev,rt_size_t size)
{
    rt_sem_release(rx_sem);
    return RT_EOK;
}
int side=0;
void pid_read_entry(void *parameter)
{
      char ch;
      static rt_uint32_t temp_number=0;
      while(1)
     {

         while(rt_device_read(pid_uart, -1, &ch, 1)!=1)
         {
             rt_sem_take(rx_sem, RT_WAITING_FOREVER);
         }

         if(ch=='[')
         {
         }
         else if(ch==']')
         {
             red_flag = 1;
             is_color=1;
             ov_location = temp_number;
             temp_number = 0 ;
             rt_completion_done(&ov_comp);
         }
         else if(ch=='c')
         {

         }
         else if(ch>='0'&&ch<='9')
         {
             temp_number=temp_number *10 + ch-'0';
         }
         ch=0;
     }

}

rt_err_t pid_uart_init(void)
{
    rt_err_t ret = RT_EOK;
    rx_sem = rt_sem_create("pid_rx", 0, RT_IPC_FLAG_PRIO);
    pid_uart = rt_device_find(pid_uart_name);
    rt_completion_init(&ov_comp);
    if(pid_uart)
    {
        ret = rt_device_open(pid_uart, RT_DEVICE_FLAG_INT_RX);
    }
    else {
        rt_kprintf("error pid_uart find\r\n");
        return -1;
    }
    rt_device_set_rx_indicate(pid_uart, pid_uart_rx_inter);
    pid_read_thread = rt_thread_create("pid_read_thread", pid_read_entry, 0, 1024, 5, 300);
    if(pid_read_thread)
    {
        rt_thread_startup(pid_read_thread);
    }
    else {
        rt_kprintf("create pid_read_thread error\r\n");
    }
    return ret;

}

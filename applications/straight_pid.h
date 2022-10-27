/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-10-27     lhylh       the first version
 */
#ifndef APPLICATIONS_STRAIGHT_PID_H_
#define APPLICATIONS_STRAIGHT_PID_H_

#include "rtthread.h"
#include "rtdevice.h"
#include "board.h"

void straight_pwm_limit(rt_int32_t * pwm1,rt_int32_t * pwm2);
void straight_pwm_abs(rt_int32_t pwm_1,rt_int32_t pwm_2);
void straight_pid_compute(int val);
int straight_pid_set(int argc,char **argv);
int straight_pid_init(void);
void straight_pid_clear(void);

#endif /* APPLICATIONS_STRAIGHT_PID_H_ */

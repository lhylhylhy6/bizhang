/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-10-23     10091       the first version
 */
#ifndef APPLICATIONS_HC_PID_H_
#define APPLICATIONS_HC_PID_H_

#include "rtthread.h"
#include "rtdevice.h"
#include "car.h"
#include "car_pwm.h"
#include "board.h"


void hc_pwm_limit(rt_int32_t * pwm1,rt_int32_t * pwm2);
void hc_pwm_abs(rt_int32_t pwm_1,rt_int32_t pwm_2);
int hc_pid_compute(int val);
int hc_pid_set(int argc,char **argv);
int hc_pid_init(void);

#endif /* APPLICATIONS_HC_PID_H_ */

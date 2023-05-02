/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-09-20     lhylh       the first version
 */
#ifndef APPLICATIONS_CAR_H_
#define APPLICATIONS_CAR_H_

#include "car_pwm.h"
#include <board.h>
//ch1 a6 //you
//ch2 a7  /zuo
//you
#define AIN1_PIN GET_PIN(F, 5)
#define AIN2_PIN GET_PIN(F, 6)
//zuo
#define BIN1_PIN GET_PIN(F, 7)
#define BIN2_PIN GET_PIN(F, 8)
enum car_state{
    CAR_PID,
    CAR_TURN,
    CAR_CIRCLE,
    CAR_STOP
};

int car_init(void);
int car_forward(void);
int car_left(void);
int car_right(void);
int car_turn(void);
int car_stop(void);
int car_left_angle();
int car_right_angle();

int test_init(void);

#endif /* APPLICATIONS_CAR_H_ */

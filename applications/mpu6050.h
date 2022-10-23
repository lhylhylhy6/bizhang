/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-10-22     10091       the first version
 */
#ifndef APPLICATIONS_MPU6050_H_

#define APPLICATIONS_MPU6050_H_

#include <rtthread.h>
#include <packages/mpu6xxx-latest/inc/sensor_inven_mpu6xxx.h>
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
#include "dmpKey.h"
#include "dmpmap.h"

void mpu_6050_init(void);
rt_uint8_t MPU_Write_Len(rt_uint8_t addr,rt_uint8_t reg,rt_uint8_t len,rt_uint8_t *databuf);
rt_uint8_t MPU_Read_Len(rt_uint8_t addr,rt_uint8_t reg,rt_uint8_t len,rt_uint8_t *buf);

#endif /* APPLICATIONS_MPU6050_H_ */

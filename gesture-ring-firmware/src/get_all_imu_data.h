// SPDX-License-Identifier: MPL-2.0

#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>

#ifndef GET_ALL_IMU_DATA_H
#define GET_ALL_IMU_DATA_H

struct gyro_data {
    struct sensor_value accel_x;
    struct sensor_value accel_y;
    struct sensor_value accel_z;

    struct sensor_value gyro_x;
    struct sensor_value gyro_y;
    struct sensor_value gyro_z;

    struct sensor_value die_temp;
};

int get_all_gyro_data(const struct device *imu, struct gyro_data *data);

#endif
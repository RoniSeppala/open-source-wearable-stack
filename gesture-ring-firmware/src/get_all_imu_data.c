// SPDX-License-Identifier: MPL-2.0

#include <zephyr/drivers/sensor.h>
#include <zephyr/device.h>

#include "get_all_imu_data.h"

int get_all_gyro_data(const struct device *imu, struct gyro_data *data){
    int err;

    err = sensor_sample_fetch(imu);
    if (err < 0 ) {
        printf("Sample fetch error: %d\n", err);
        return -ENODATA;
    }

    err = sensor_channel_get (imu, SENSOR_CHAN_ACCEL_X, &data->accel_x);
    if (err < 0) {
        printf("Channel get error: %d\n", err);
        return -ENODATA;
    }
    err = sensor_channel_get (imu, SENSOR_CHAN_ACCEL_Y, &data->accel_y);
    if (err < 0) {
        printf("Channel get error: %d\n", err);
        return -ENODATA;
    }
    err = sensor_channel_get (imu, SENSOR_CHAN_ACCEL_Z, &data->accel_z);
    if (err < 0) {
        printf("Channel get error: %d\n", err);
        return -ENODATA;
    }

    err = sensor_channel_get (imu, SENSOR_CHAN_GYRO_X, &data->gyro_x);
    if (err < 0) {
        printf("Channel get error: %d\n", err);
        return -ENODATA;
    }
    err = sensor_channel_get (imu, SENSOR_CHAN_GYRO_Y, &data->gyro_y);
    if (err < 0) {
        printf("Channel get error: %d\n", err);
        return -ENODATA;
    }
    err = sensor_channel_get (imu, SENSOR_CHAN_GYRO_Z, &data->gyro_z);
    if (err < 0) {
        printf("Channel get error: %d\n", err);
        return -ENODATA;
    }

    err = sensor_channel_get (imu, SENSOR_CHAN_DIE_TEMP, &data->die_temp);
    if (err < 0) {
        printf("Channel get error: %d\n", err);
        return -ENODATA;
    }

    return 0;
}
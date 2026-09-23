#include <zephyr/device.h>
#include "get_all_imu_data.h"

#ifndef GESTURE_TEST_H
#define GESTURE_TEST_H

#define REQUIRED_CONFIDENCE
#define CONFIDENCE_BASE

struct all_gyro_data_int64_t {
    int64_t accel_x;
    int64_t accel_y;
    int64_t accel_z;

    int64_t gyro_x;
    int64_t gyro_y;
    int64_t gyro_z;

    int64_t die_temp;
};

struct all_imu_data_accel_normalised_float_gyro_int64_t {
    float accel_x;
    float accel_y;
    float accel_z;

    int64_t gyro_x;
    int64_t gyro_y;
    int64_t gyro_z;

    int64_t die_temp;
};

void acceleration_normalisation(struct all_gyro_data_int64_t *pre_normalisation_data, struct all_imu_data_accel_normalised_float_gyro_int64_t *post_normalisation_data);
void gyro_data_sensor_value_to_int64_t(const struct gyro_data *pre_transform, struct all_gyro_data_int64_t *post_transform);
int get_gesture(const struct device *imu);

#endif
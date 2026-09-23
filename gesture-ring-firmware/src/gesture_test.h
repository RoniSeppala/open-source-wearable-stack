#include <zephyr/device.h>

#ifndef GESTURE_TEST_H
#define GESTURE_TEST_H

#define REQUIRED_CONFIDENCE
#define CONFIDENCE_BASE

int get_gesture(const struct device *imu);

struct all_gyro_data_int64_t {
    int64_t accel_x;
    int64_t accel_y;
    int64_t accel_z;

    int64_t gyro_x;
    int64_t gyro_y;
    int64_t gyro_z;

    int64_t die_temp;
};

#endif
#include <zephyr/device.h>

#ifndef GESTURE_TEST_H
#define GESTURE_TEST_H

#define REQUIRED_CONFIDENCE
#define CONFIDENCE_BASE

int get_gesture(const struct device *imu);

#endif
// SPDX-License-Identifier: MPL-2.0

/* functions by getting confidence values for each gesture by checking how accelerometer/gyro values
 * compare to confidence base
 *
 * returns highest confidence gesture if multiple are over required minimum confidence, and 
 * if none are at required confidence, returns no gesture
*/

#include "gesture_test.h"

#include <zephyr/drivers/sensor.h>
#include <zephyr/device.h>


int get_gesture(const struct device *imu){
    int err;

    err = sensor_sample_fetch(imu);
    if (err < 0 ) {
        printf("Sample fetch error: %d\n", err);
        return -ENODATA;
    }

    return 0;
}
// SPDX-License-Identifier: MPL-2.0

/* functions by getting confidence values for each gesture by checking how accelerometer/gyro values
 * compare to confidence base
 *
 * returns highest confidence gesture if multiple are over required minimum confidence, and 
 * if none are at required confidence, returns no gesture
*/

#include "gesture_test.h"
#include "get_all_imu_data.h"

#include <zephyr/drivers/sensor.h>
#include <zephyr/device.h>

static int acceleration_normalisation(struct gyro_data *pre_normalisation_data, struct gyro_data *post_normalisation_data){
    /*
    magnitude = sqrt(ax*ax + ay*ay + az*az);

    gx = ax / magnitude;
    gy = ay / magnitude;
    gz = az / magnitude;
    */

    
}

static int gyro_data_sensor_value_to_int64_t(struct gyro_data *pre_transform, struct all_gyro_data_int64_t *post_transform){
    int err;

    post_transform->accel_x = sensor_value_to_micro(&pre_transform->accel_x);
    post_transform->accel_y = sensor_value_to_micro(&pre_transform->accel_y);
    post_transform->accel_z = sensor_value_to_micro(&pre_transform->accel_z);

    post_transform->gyro_x = sensor_value_to_micro(&pre_transform->gyro_x);
    post_transform->gyro_y = sensor_value_to_micro(&pre_transform->gyro_y);
    post_transform->gyro_z = sensor_value_to_micro(&pre_transform->gyro_z);

    post_transform->die_temp = sensor_value_to_micro(&pre_transform->die_temp);

    return 0;
}

int get_gesture(const struct device *imu){
    int err;
    struct gyro_data pre_calibration_data_sensor_value;

    struct all_gyro_data_int64_t pre_calibration_data;
    struct all_gyro_data_int64_t post_calibration_data;

    err = get_all_gyro_data(imu, &pre_calibration_data_sensor_value);
    if (err < 0) {
        printf("Channel get error: %d\n", err);
        return -ENODATA;
    }

    err = gyro_data_sensor_value_to_int64_t(&pre_calibration_data_sensor_value, &pre_calibration_data);

    return 0;
}
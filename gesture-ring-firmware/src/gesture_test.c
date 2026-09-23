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
#include <math.h>
#include <errno.h>
#include <stdio.h>

static int gesture_estimation(struct all_imu_data_accel_normalised_float_gyro_int64_t *imu_data){

    return 0;
}

void acceleration_normalisation(struct all_gyro_data_int64_t *pre_normalisation_data, struct all_imu_data_accel_normalised_float_gyro_int64_t *post_normalisation_data){
    /*
    magnitude = sqrt(ax*ax + ay*ay + az*az);

    gx = ax / magnitude;
    gy = ay / magnitude;
    gz = az / magnitude;
    */

    float accel_x = (float)pre_normalisation_data->accel_x;
    float accel_y = (float)pre_normalisation_data->accel_y;
    float accel_z = (float)pre_normalisation_data->accel_z;

    int64_t magnitude = sqrt(accel_x*accel_x+accel_y*accel_y+accel_z*accel_z);

        if (magnitude == 0.0f) {
        post_normalisation_data->accel_x = 0.0f;
        post_normalisation_data->accel_y = 0.0f;
        post_normalisation_data->accel_z = 0.0f;
        return;
    }

    post_normalisation_data->accel_x = pre_normalisation_data->accel_x / magnitude;
    post_normalisation_data->accel_y = pre_normalisation_data->accel_y / magnitude;
    post_normalisation_data->accel_z = pre_normalisation_data->accel_z / magnitude;

    post_normalisation_data->gyro_x = pre_normalisation_data->gyro_x;
    post_normalisation_data->gyro_y = pre_normalisation_data->gyro_y;
    post_normalisation_data->gyro_z = pre_normalisation_data->gyro_z;

    post_normalisation_data->die_temp = pre_normalisation_data->die_temp;
}

void gyro_data_sensor_value_to_int64_t(const struct gyro_data *pre_transform, struct all_gyro_data_int64_t *post_transform){
    post_transform->accel_x = sensor_value_to_micro(&pre_transform->accel_x);
    post_transform->accel_y = sensor_value_to_micro(&pre_transform->accel_y);
    post_transform->accel_z = sensor_value_to_micro(&pre_transform->accel_z);

    post_transform->gyro_x = sensor_value_to_micro(&pre_transform->gyro_x);
    post_transform->gyro_y = sensor_value_to_micro(&pre_transform->gyro_y);
    post_transform->gyro_z = sensor_value_to_micro(&pre_transform->gyro_z);

    post_transform->die_temp = sensor_value_to_micro(&pre_transform->die_temp);
}

int get_gesture(const struct device *imu){
    int err;
    struct gyro_data pre_calibration_data_sensor_value;

    struct all_gyro_data_int64_t pre_calibration_data;
    struct all_imu_data_accel_normalised_float_gyro_int64_t post_calibration_data;

    err = get_all_gyro_data(imu, &pre_calibration_data_sensor_value);
    if (err < 0) {
        printf("Channel get error: %d\n", err);
        return -ENODATA;
    }

    gyro_data_sensor_value_to_int64_t(&pre_calibration_data_sensor_value, &pre_calibration_data);

    acceleration_normalisation(&pre_calibration_data, &post_calibration_data);

    return 0;
}
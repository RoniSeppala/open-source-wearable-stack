// SPDX-License-Identifier: MPL-2.0


#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/led_strip.h>
#include <zephyr/drivers/sensor.h>
#include <stdio.h>

#define LED_NODE DT_ALIAS(led_strip)
#define IMU_NODE DT_ALIAS(imu)

#include "get_all_imu_data.h"
#include "gesture_test.h"

static const struct device *const strip = DEVICE_DT_GET(LED_NODE);
static const struct device *const imu = DEVICE_DT_GET(IMU_NODE);

int main(void)
{
    int err;
    struct led_rgb pixel = {
        .r = 20,
        .g = 0,
        .b = 0,
    };

    if (!device_is_ready(strip)) {
        printf("LED strip not ready\n");
        return 0;
    }

    if (!device_is_ready(imu)) {
        printf("IMU not ready\n");
        return 0;
    }

    struct gyro_data data;
    struct all_gyro_data_int64_t pre_normalisation;
    struct all_imu_data_accel_normalised_float_gyro_int64_t post_normalisation;
    while (1) {

        // led blink
        led_strip_update_rgb(strip, &pixel, 1);

        k_sleep(K_MSEC(50));

        pixel.r = 0;
        pixel.g = 0;
        pixel.b = 0;

        led_strip_update_rgb(strip, &pixel, 1);

        k_sleep(K_MSEC(50));

        pixel.r = 20;

        // accelerometer test

        err = get_all_gyro_data(imu, &data);
        if (err < 0) {
            printf("Channel get error: %d\n", err);
            return -ENODATA;
        }

        gyro_data_sensor_value_to_int64_t(&data, &pre_normalisation);
        acceleration_normalisation(&pre_normalisation, &post_normalisation);
        printf("\r\n\r\n\r\n");

        //printf("Accel x, %d.%06d\r\nAccel y, %d.%06d\r\nAccel z, %d.%06d\r\n\r\nGyro x, %d.%06d\r\nGyro y, %d.%06d\r\nGyro z, %d.%06d\r\n\r\nTemp, %d.%06d\r\n", data.accel_x.val1, data.accel_x.val2, data.accel_y.val1, data.accel_y.val2, data.accel_z.val1, data.accel_z.val2, data.gyro_x.val1, data.gyro_x.val2, data.gyro_y.val1, data.gyro_y.val2, data.gyro_z.val1, data.gyro_z.val2, data.die_temp.val1, data.die_temp.val2);

        printf("Accel x, %.6f\r\nAccel y, %.6f\r\nAccel z, %.6f\r\n\r\nGyro x, %" PRId64 "\r\nGyro y, %" PRId64 "\r\nGyro z, %" PRId64 "\r\n\r\nTemp, %" PRId64 "\r\n", (double)post_normalisation.accel_x, (double)post_normalisation.accel_y, (double)post_normalisation.accel_z, post_normalisation.gyro_x, post_normalisation.gyro_y, post_normalisation.gyro_z, post_normalisation.die_temp);
    }

    return 0;
}
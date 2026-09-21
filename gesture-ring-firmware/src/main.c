// SPDX-License-Identifier: MPL-2.0


#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/led_strip.h>
#include <zephyr/drivers/sensor.h>
#include <stdio.h>

#define LED_NODE DT_ALIAS(led_strip)
#define IMU_NODE DT_ALIAS(imu)

static const struct device *const strip = DEVICE_DT_GET(LED_NODE);
static const struct device *const imu = DEVICE_DT_GET(IMU_NODE);

int main(void)
{
    struct sensor_value accel_x;
    struct sensor_value accel_y;
    struct sensor_value accel_z;

    struct sensor_value gyro_x;
    struct sensor_value gyro_y;
    struct sensor_value gyro_z;

    struct sensor_value die_temp;

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

        // accelerometer checs

        err = sensor_sample_fetch(imu);
        if (err < 0 ) {
            printf("Sample fetch error: %d\n", err);
            return 0;
        }

        err = sensor_channel_get (imu, SENSOR_CHAN_ACCEL_X, &accel_x);
        if (err < 0) {
            printf("Channel get error: %d\n", err);
            return 0;
        }
        err = sensor_channel_get (imu, SENSOR_CHAN_ACCEL_Y, &accel_y);
        if (err < 0) {
            printf("Channel get error: %d\n", err);
            return 0;
        }
        err = sensor_channel_get (imu, SENSOR_CHAN_ACCEL_Z, &accel_z);
        if (err < 0) {
            printf("Channel get error: %d\n", err);
            return 0;
        }

        err = sensor_channel_get (imu, SENSOR_CHAN_GYRO_X, &gyro_x);
        if (err < 0) {
            printf("Channel get error: %d\n", err);
            return 0;
        }
        err = sensor_channel_get (imu, SENSOR_CHAN_GYRO_Y, &gyro_y);
        if (err < 0) {
            printf("Channel get error: %d\n", err);
            return 0;
        }
        err = sensor_channel_get (imu, SENSOR_CHAN_GYRO_Z, &gyro_z);
        if (err < 0) {
            printf("Channel get error: %d\n", err);
            return 0;
        }

        err = sensor_channel_get (imu, SENSOR_CHAN_DIE_TEMP, &die_temp);
        if (err < 0) {
            printf("Channel get error: %d\n", err);
            return 0;
        }

        printf("\r\n\r\n\r\n");
        printf("Accel x, %d.%06d\r\nAccel y, %d.%06d\r\nAccel z, %d.%06d\r\n\r\nGyro x, %d.%06d\r\nGyro y, %d.%06d\r\nGyro z, %d.%06d\r\n\r\nTemp, %d.%06d\r\n", accel_x.val1, accel_x.val2, accel_y.val1, accel_y.val2, accel_z.val1, accel_z.val2, gyro_x.val1, gyro_x.val2, gyro_y.val1, gyro_y.val2, gyro_z.val1, gyro_z.val2, die_temp.val1, die_temp.val2);

    }

    return 0;
}
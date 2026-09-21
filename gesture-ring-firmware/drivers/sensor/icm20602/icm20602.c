/*
 * custom invesense_icm20602 firmware
 * SPDX-License-Identifier: MPL-2.0
 */

#define DT_DRV_COMPAT invensense_icm20602

#include <errno.h>
#include <zephyr/device.h>
#include <zephyr/drivers/i2c.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/sys/util.h>

#include "icm20602.h"

static int icm20602_sample_fetch(const struct device *dev, enum sensor_channel chan)
{
    int err;
    struct icm20602_data *data = dev->data;
    const struct icm20602_config *config = dev->config;
    uint8_t raw[14];

    if (chan != SENSOR_CHAN_ALL){
        return -ENOTSUP;
    }

    data->sample_valid = 0;

    err = i2c_burst_read_dt(&config->i2c, 0x3B, raw, sizeof(raw));

    if (err < 0) {
        return err;
    }

    // decode data
    data->accel[0] = ((uint16_t)raw[0] << 8) | raw[1]; // x
    data->accel[1] = ((uint16_t)raw[2] << 8) | raw[3]; // y
    data->accel[2] = ((uint16_t)raw[4] << 8) | raw[5]; // z

    data->gyro[0] = ((uint16_t)raw[8] << 8) | raw[9]; // x
    data->gyro[1] = ((uint16_t)raw[10] << 8) | raw[11]; // y
    data->gyro[2] = ((uint16_t)raw[12] << 8) | raw[13]; // z

    data->temp = ((uint16_t)raw[6] << 8) | raw[7];

    data->sample_valid=1;

    return 0;
}

static int icm20602_accelerator_ms(const struct device *dev, struct sensor_value *val, int axis) { // axis ids: 0=x, 1=y, 2=z
    struct icm20602_data *data = dev->data;

    if (!data->sample_valid) {
        return -ENODATA;
    }

    int64_t total_ums2 = ((int64_t)data->accel[axis]*SENSOR_G)/16384;
    return sensor_value_from_micro(val, total_ums2);

    return 0;
}

static int icm20602_gyro_rads(const struct device *dev, struct sensor_value *val, int axis) { // axis ids: 0=x, 1=y, 2=z
    struct icm20602_data *data = dev->data;

    if (!data->sample_valid) {
        return -ENODATA;
    }

    int64_t total_urads = ((int64_t)data->gyro[axis]*SENSOR_PI)/(131*180);
    return sensor_value_from_micro(val, total_urads);

    return 0;
}

static int icm20602_channel_get(const struct device *dev, enum sensor_channel chan, struct sensor_value *val)
{
    int err;
    struct icm20602_data *data = dev->data;

    switch (chan)
    {
    case SENSOR_CHAN_ACCEL_X:
        err = icm20602_accelerator_ms(dev, val, 0);
        break;
    case SENSOR_CHAN_ACCEL_Y:
        err = icm20602_accelerator_ms(dev, val, 1);
        break;
    case SENSOR_CHAN_ACCEL_Z:
        err = icm20602_accelerator_ms(dev, val, 2);
        break;
    case SENSOR_CHAN_GYRO_X:
        err = icm20602_gyro_rads(dev, val, 0);
        break;
    case SENSOR_CHAN_GYRO_Y:
        err = icm20602_gyro_rads(dev, val, 1);
        break;
    case SENSOR_CHAN_GYRO_Z:
        err = icm20602_gyro_rads(dev, val, 2);
        break;
    case SENSOR_CHAN_DIE_TEMP:
        if (!data->sample_valid) {
            return -ENODATA;
        }

        int64_t temp_uc =
            25000000LL +
            ((int64_t)data->temp * 10000000LL) / 3268;

        err = sensor_value_from_micro(val, temp_uc);
        break;
    default:
        return -ENOTSUP;
    }

    if (err < 0 ){
        return err;
    }

    return 0;
}

static DEVICE_API(sensor, icm20602_driver_api) = {
    .sample_fetch = icm20602_sample_fetch,
    .channel_get = icm20602_channel_get,
};

static int icm20602_init(const struct device *dev)
{
    const struct icm20602_config *config = dev->config;

	int err;
    uint8_t who_am_i;

    // check device is ready
    if (!i2c_is_ready_dt (&config->i2c)) {
        return -ENODEV;
    }

    // verify who am i
    err = i2c_reg_read_byte_dt(&config->i2c, ICM20602_REG_WHO_AM_I, &who_am_i);

    if (err < 0) {
        return err;
    }

    if (who_am_i != ICM20602_WHO_AM_I_VALUE ) {
        return -ENODEV;
    }

    // wake sensor (register 107)
    err = i2c_reg_write_byte_dt(&config->i2c, ICM20602_REG_PWR_MGMT_1, 0x1);
    if (err < 0){
        return err;
    }

    // set accelerometer range to +-2 g (register 28)
    err = i2c_reg_write_byte_dt(&config->i2c, ICM20602_REG_ACCEL_CONFIG, 0x00);
    if (err < 0){
        return err;
    }

    // set gyro range to +-250 degrees per second (register 27)
    err = i2c_reg_write_byte_dt(&config->i2c, ICM20602_REG_GYRO_CONFIG, 0x00);
    if (err < 0){
        return err;
    }

    return 0;
}

#define ICM20602_DEFINE(inst) \
    static struct icm20602_data icm20602_data_##inst; \
    static const struct icm20602_config icm20602_config_##inst = { \
        .i2c = I2C_DT_SPEC_INST_GET(inst), \
    }; \
    SENSOR_DEVICE_DT_INST_DEFINE(inst, icm20602_init, NULL, &icm20602_data_##inst, &icm20602_config_##inst, POST_KERNEL, CONFIG_SENSOR_INIT_PRIORITY, &icm20602_driver_api);

DT_INST_FOREACH_STATUS_OKAY(ICM20602_DEFINE)

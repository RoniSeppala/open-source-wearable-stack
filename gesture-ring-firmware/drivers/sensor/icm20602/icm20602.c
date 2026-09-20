/*
 * Based in part on TDK InvenSense Zephyr sensor drivers.
 *
 * SPDX-License-Identifier: Apache-2.0
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
    ARG_UNUSED(dev);
    ARG_UNUSED(chan);

    return -ENOTSUP;
}

static int icm20602_channel_get(const struct device *dev, enum sensor_channel chan, struct sensor_value *val)
{
    ARG_UNUSED(dev);
    ARG_UNUSED(chan);
    ARG_UNUSED(val);

    return -ENOTSUP;
}

static DEVICE_API(sensor, icm20602_driver_api) = {
    .sample_fetch = icm20602_sample_fetch,
    .channel_get = icm20602_channel_get,
};

static int icm20602_init(const struct device *dev)
{
    const struct icm20602_config *config = dev->config;

    return 0;
}

#define ICM20602_DEFINE(inst) \
    static struct icm20602_data icm20602_data_##inst; \
    static const struct icm20602_config icm20602_config_##inst = { \
        .i2c = I2C_DT_SPEC_INST_GET(inst), \
    }; \
    SENSOR_DEVICE_DT_INST_DEFINE(inst, icm20602_init, NULL, &icm20602_data_##inst, &icm20602_config_##inst, POST_KERNEL, CONFIG_SENSOR_INIT_PRIORITY, &icm20602_driver_api);

DT_INST_FOREACH_STATUS_OKAY(ICM20602_DEFINE)
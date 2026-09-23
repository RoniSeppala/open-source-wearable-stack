// SPDX-License-Identifier: MPL-2.0

#ifndef ICM20602_H
#define ICM20602_H

#include <zephyr/drivers/i2c.h>
#include <stdint.h>

#define ICM20602_REG_WHO_AM_I 0x75
#define ICM20602_WHO_AM_I_VALUE 0x12
#define ICM20602_REG_ACCEL_CONFIG 0x1C
#define ICM20602_REG_GYRO_CONFIG  0x1B

//power related registers
#define ICM20602_LP_MODE_CFG 0x1E       // gyro low power config
#define ICM20602_SMPLRT_DIV 0x19        // sample rate devider
#define ICM20602_CONFIG 0x1A            // general configuration
#define ICM20602_ACCEL_CONFIG2 0x1D     // accelerometer config 2
#define ICM20602_PWR_MGMT_1 0x6B        // power management 1
#define ICM20602_PWR_MGMT_2 0x6C        // power management 1
#define ICM20602_ACCEL_INTEL_CTRL 0x69  // accelerometer intelligence control


struct icm20602_config {
    struct i2c_dt_spec i2c;
};

struct icm20602_data {
    int16_t accel[3];
    int16_t gyro[3];
    int16_t temp;
    bool sample_valid;
};

#endif
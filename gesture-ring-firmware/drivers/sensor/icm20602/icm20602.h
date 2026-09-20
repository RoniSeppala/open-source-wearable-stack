#ifndef ICM20602_H
#define ICM20602_H

#include <zephyr/drivers/i2c.h>
#include <stdint.h>

#define ICM20602_REG_WHO_AM_I 0x75
#define ICM20602_WHO_AM_I_VALUE 0x12

struct icm20602_config {
    struct i2c_dt_spec i2c;
};

struct icm20602_data {
    int16_t accel[3];
    int16_t gyro[3];
    int16_t temp;
};

#endif
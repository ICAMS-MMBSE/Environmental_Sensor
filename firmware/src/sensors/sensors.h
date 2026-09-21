#ifndef SENSORS_H
#define SENSORS_H

#include <zephyr/drivers/sensor.h>

struct env_reading {
    struct sensor_value co2;
    struct sensor_value temp;
    struct sensor_value humidity;
};

int scd40_init(void)
int scd40_read(struct env_reading *r);

#endif
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/logging/log.h>
#include "sensors.h"

LOG_MODULE_REGISTER(scd40, CONFIG_SENSOR_LOG_LEVEL);

static const struct device *dev = DEVICE_DT_GET(DT_NODELABEL(scd40));

/* Initialize SCD40 */
int scd40_init(void)
{
    if(!device_is_ready(dev)) {
        LOG_ERR("%s not ready", dev->name);
        return -ENODEV;
    }
    LOG_INF("%s ready", dev->name);
    return 0;
}

/* Read SCD40 co2, temperature, and humidity */
int scd40_read(struct env_reading *r)
{
    int ret = sensor_sample_fetch(dev);
    if (ret) {
        LOG_ERR("fetch failed: %d", ret);
        return ret;
    }
    /* Read and store values */
    sensor_channel_get(dev, SENSOR_CHAN_CO2, &r->co2);
    sensor_channel_get(dev, SENSOR_CHAN_AMBIENT_TEMP, &r->temp);
    sensor_channel_get(dev, SENSOR_CHAN_HUMIDITY, &r->humidity);

    return 0;
}
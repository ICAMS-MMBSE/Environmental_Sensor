#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/sys/printk.h>
#define SLEEP_TIME_MS 5000

static const struct device *scd40_dev = DEVICE_DT_GET(DT_NODELABEL(scd40));

static int setup(void)
{
    if(!device_is_ready(scd40_dev)) {
        printk("SCD40 device %s is not ready\n", scd40_dev->name);
        return -1;
    }

    printk("SCD40 device %s is ready\n", scd40_dev->name);
    return 0;
}
int main(void)
{
    if (setup() != 0) {
        return 0;
    }

    while (1) {
        struct sensor_value co2, temp, humidity;
        int ret;

        ret = sensor_sample_fetch(scd40_dev);
        if (ret != 0) {
            printk("sensor_sample_fetch failed: %d\n", ret);
            k_msleep(SLEEP_TIME_MS);
            continue;
        }

        sensor_channel_get(scd40_dev, SENSOR_CHAN_CO2, &co2);
        sensor_channel_get(scd40_dev, SENSOR_CHAN_AMBIENT_TEMP, &temp);
        sensor_channel_get(scd40_dev, SENSOR_CHAN_HUMIDITY, &humidity);

        printk("CO2: %d ppm, Temp %d.%06d C, RH: %d.%06d %%\n",
            co2.val1,
            temp.val1, temp.val2,
            humidity.val1, humidity.val2);
        
        k_msleep(SLEEP_TIME_MS);
    }

    return 0;
}

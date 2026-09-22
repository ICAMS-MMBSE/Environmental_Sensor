#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/logging/log.h>
#include "sensors/sensors.h"
#include "mesh/mesh.h"

#define SLEEP_TIME_MS 5000

LOG_MODULE_REGISTER(main, LOG_LEVEL_INF);

int main(void)
{
    
    if (mesh_init()) {
        LOG_ERR("mesh init failed");
    }

    if (scd40_init()){
        LOG_ERR("sensor init failed, halting");
        return 0;
    }

    while (1) {
        struct env_reading r;
        if (scd40_read(&r) == 0){
            LOG_INF("CO2: %d ppm, Temp %d.%06d C, RH: %d.%06d %%",
                    r.co2.val1,
                    r.temp.val1, r.temp.val2,
                    r.humidity.val1, r.humidity.val2);

        }    
        k_msleep(SLEEP_TIME_MS);
    }

    return 0;
}

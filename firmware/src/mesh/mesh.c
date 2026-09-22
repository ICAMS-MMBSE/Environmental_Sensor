#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/mesh.h>
#include <zephyr/settings/settings.h>
#include <zephyr/logging/log.h>
#include "mesh.h"
#include "model_handler.h"

LOG_MODULE_REGISTER(mesh, LOG_LEVEL_INF);

/* Every node needs its own UUID so a provisioner can tell them apart. */
static const uint8_t dev_uuid[16] = {0xdd, 0xdd};

static const struct bt_mesh_prov prov = {
    .uuid = dev_uuid,
};

static void bt_ready(int err)
{
    if (err) {
        LOG_ERR("Bluetooth init failed (err %d)", err);
        return;
    }

    LOG_INF("Bluetooth initialized");

    err = bt_mesh_init(&prov, model_handler_init());
    if (err) {
        LOG_ERR("Initializing mesh failed (err %d)", err);
        return;
    }

    if (IS_ENABLED(CONFIG_SETTINGS)) {
        settings_load();
    }

    /* This will be a no-op if settings_load() loaded provisioning info */
    bt_mesh_prov_enable(BT_MESH_PROV_ADV | BT_MESH_PROV_GATT);

    LOG_INF("Mesh initialized, waiting to be provisioned");
}

int mesh_init(void)
{
    return bt_enable(bt_ready);
}

#include <zephyr/bluetooth/mesh.h>
#include "model_handler.h"

static void attention_on(const struct bt_mesh_model *mod)
{
}

static void attention_off(const struct bt_mesh_model *mod)
{
}

static const struct bt_mesh_health_srv_cb health_srv_cb = {
    .attn_on = attention_on,
    .attn_off = attention_off,
};

static struct bt_mesh_health_srv health_srv = {
    .cb = &health_srv_cb,
};

BT_MESH_HEALTH_PUB_DEFINE(health_pub, 0);

static const struct bt_mesh_model root_models[] = {
    BT_MESH_MODEL_CFG_SRV,
    BT_MESH_MODEL_HEALTH_SRV(&health_srv, &health_pub),
};

static const struct bt_mesh_elem elements[] = {
    BT_MESH_ELEM(0, root_models, BT_MESH_MODEL_NONE),
};

static const struct bt_mesh_comp comp = {
    .cid = CONFIG_BT_COMPANY_ID,
    .elem = elements,
    .elem_count = ARRAY_SIZE(elements),
};

const struct bt_mesh_comp *model_handler_init(void)
{
    return &comp;
}

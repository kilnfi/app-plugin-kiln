#include "kiln_plugin.h"

void handle_finalize(void *parameters) {
    ethPluginFinalize_t *msg = (ethPluginFinalize_t *) parameters;
    context_t *context = (context_t *) msg->pluginContext;

    msg->uiType = ETH_UI_TYPE_GENERIC;

    switch (context->selectorIndex) {
        case KILN_DEPOSIT:
            msg->numScreens = 1;
            msg->result = ETH_PLUGIN_RESULT_OK;
            break;

        case KILN_WITHDRAW:
        case KILN_WITHDRAW_EL:
        case KILN_WITHDRAW_CL:
            msg->numScreens = 2;
            msg->result = ETH_PLUGIN_RESULT_OK;
            break;

        default:
            PRINTF("Selector Index not supported: %d\n", context->selectorIndex);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

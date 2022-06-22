#include "kiln_plugin.h"

void handle_query_contract_id(void *parameters) {
    ethQueryContractID_t *msg = (ethQueryContractID_t *) parameters;
    const context_t *context = (const context_t *) msg->pluginContext;

    strlcpy(msg->name, PLUGIN_NAME, msg->nameLength);

    switch (context->selectorIndex) {
        case KILN_DEPOSIT:
            strlcpy(msg->version, "Stake", msg->versionLength);
            msg->result = ETH_PLUGIN_RESULT_OK;
            break;

        case KILN_WITHDRAW:
            strlcpy(msg->version, "Withdraw", msg->versionLength);
            msg->result = ETH_PLUGIN_RESULT_OK;
            break;

        default:
            PRINTF("Selector Index not supported: %d\n", context->selectorIndex);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

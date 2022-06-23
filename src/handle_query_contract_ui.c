#include "kiln_plugin.h"
#include "utils.h"

static void deposit_send_ui(ethQueryContractUI_t *msg) {
    strlcpy(msg->title, "Stake", msg->titleLength);

    const uint8_t *eth_amount = msg->pluginSharedRO->txContent->value.value;
    uint8_t eth_amount_size = msg->pluginSharedRO->txContent->value.length;

    amountToString(eth_amount, eth_amount_size, WEI_TO_ETHER, "ETH ", msg->msg, msg->msgLength);
}

static void deposit_withdrawal_ui(ethQueryContractUI_t *msg, context_t *context) {
    strlcpy(msg->title, "Withdrawal", msg->titleLength);

    uint64_t chainid = 0;

    getEthDisplayableAddress(context->withdrawal_address,
                             msg->msg,
                             msg->msgLength,
                             msg->pluginSharedRW->sha3,
                             chainid);
}

static void deposit_ui(ethQueryContractUI_t *msg, context_t *context) {
    switch (msg->screenIndex) {
        case 0:
            deposit_send_ui(msg);
            msg->result = ETH_PLUGIN_RESULT_OK;
            break;

        case 1:
            deposit_withdrawal_ui(msg, context);
            msg->result = ETH_PLUGIN_RESULT_OK;
            break;

        default:
            PRINTF("Received an invalid screenIndex\n");
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

static void withdraw_rewards_ui(ethQueryContractUI_t *msg) {
    strlcpy(msg->title, "Rewards", msg->titleLength);
    strlcpy(msg->msg, "Consensus & Exec", msg->msgLength);
}

static void withdraw_validation_address_ui(ethQueryContractUI_t *msg, context_t *context) {
    strlcpy(msg->title, "Validation Key", msg->titleLength);

    getEthBlsAddressStringFromBinary(msg, context->validator_address);
}

static void withdraw_ui(ethQueryContractUI_t *msg, context_t *context) {
    switch (msg->screenIndex) {
        case 0:
            withdraw_rewards_ui(msg);
            msg->result = ETH_PLUGIN_RESULT_OK;
            break;

        case 1:
            withdraw_validation_address_ui(msg, context);
            msg->result = ETH_PLUGIN_RESULT_OK;
            break;

        default:
            PRINTF("Received an invalid screenIndex\n");
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

void handle_query_contract_ui(void *parameters) {
    ethQueryContractUI_t *msg = (ethQueryContractUI_t *) parameters;
    context_t *context = (context_t *) msg->pluginContext;

    memset(msg->title, 0, msg->titleLength);
    memset(msg->msg, 0, msg->msgLength);

    switch (context->selectorIndex) {
        case KILN_DEPOSIT:
            deposit_ui(msg, context);
            break;

        case KILN_WITHDRAW:
            withdraw_ui(msg, context);
            break;

        default:
            PRINTF("Selector Index not supported: %d\n", context->selectorIndex);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

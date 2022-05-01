#include "kiln_plugin.h"

static void set_send_ui(ethQueryContractUI_t *msg) {
  strlcpy(msg->title, "Stake", msg->titleLength);

  const uint8_t *eth_amount = msg->pluginSharedRO->txContent->value.value;
  uint8_t eth_amount_size = msg->pluginSharedRO->txContent->value.length;

  amountToString(eth_amount, eth_amount_size, WEI_TO_ETHER, "ETH ", msg->msg, msg->msgLength);
}

static void set_withdrawal_ui(ethQueryContractUI_t *msg, context_t *context) {
    strlcpy(msg->title, "Withdrawal", msg->titleLength);

    msg->msg[0] = '0';
    msg->msg[1] = 'x';

    uint64_t chainid = 0;

    getEthAddressStringFromBinary(context->withdrawal_address, msg->msg + 2, msg->pluginSharedRW->sha3, chainid);
}

void handle_query_contract_ui(void *parameters) {
  ethQueryContractUI_t *msg = (ethQueryContractUI_t *) parameters;
  context_t *context = (context_t *) msg->pluginContext;

  memset(msg->title, 0, msg->titleLength);
  memset(msg->msg, 0, msg->msgLength);

  msg->result = ETH_PLUGIN_RESULT_OK;

  switch (msg->screenIndex) {
  case 0:
    set_send_ui(msg);
    break;

  case 1:
    set_withdrawal_ui(msg, context);
    break;

  default:
    PRINTF("Received an invalid screenIndex\n");
    msg->result = ETH_PLUGIN_RESULT_ERROR;
    return;
  }
}

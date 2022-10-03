#include "kiln_plugin.h"

static void handle_deposit_parameters(ethPluginProvideParameter_t *msg, context_t *context) {
    switch (context->next_param) {
        default:
            PRINTF("Param not supported: %d\n", context->next_param);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

static void handle_withdraw_parameters(ethPluginProvideParameter_t *msg, context_t *context) {
    // We don't use the offset here as we know the layout:
    //
    // 0: offset of the array (0x20)
    // 1: length of the array (0x02)
    // 2: first part of the key
    // 3: second part of the key
    switch (context->next_param) {
        case WITHDRAW_VALIDATION_OFFSET:
            context->next_param = WITHDRAW_VALIDATION_LENGTH;
            break;

        case WITHDRAW_VALIDATION_LENGTH:
            context->next_param = WITHDRAW_VALIDATION_KEY_PART_1;
            break;

        case WITHDRAW_VALIDATION_KEY_PART_1:
            copy_parameter(context->validator_address, msg->parameter, 32);
            context->next_param = WITHDRAW_VALIDATION_KEY_PART_2;
            break;

        case WITHDRAW_VALIDATION_KEY_PART_2:
            copy_parameter(context->validator_address + 32, msg->parameter, 16);
            context->next_param = WITHDRAW_UNEXPECTED_PARAMETER;
            break;

        default:
            PRINTF("Param not supported: %d\n", context->next_param);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

void handle_provide_parameter(void *parameters) {
    ethPluginProvideParameter_t *msg = (ethPluginProvideParameter_t *) parameters;
    context_t *context = (context_t *) msg->pluginContext;

    PRINTF("plugin provide parameter: offset %d\nBytes: %.*H\n",
           msg->parameterOffset,
           PARAMETER_LENGTH,
           msg->parameter);

    switch (context->selectorIndex) {
        case KILN_DEPOSIT:
            msg->result = ETH_PLUGIN_RESULT_OK;
            handle_deposit_parameters(msg, context);
            break;

        case KILN_WITHDRAW:
        case KILN_WITHDRAW_EL:
        case KILN_WITHDRAW_CL:
            msg->result = ETH_PLUGIN_RESULT_OK;
            handle_withdraw_parameters(msg, context);
            break;

        default:
            PRINTF("Selector Index not supported: %d\n", context->selectorIndex);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

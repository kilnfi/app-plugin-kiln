#pragma once

#include <string.h>

#include "eth_internals.h"
#include "eth_plugin_interface.h"

#define PLUGIN_NAME "Kiln"

// Available selectors:
//
// 0. deposit(withdrawal_address)
// 1. withdraw()
//
// More to come!
#define NUM_SELECTORS 2

// Selectors available (see mapping above).
typedef enum {
    KILN_DEPOSIT = 0,
    KILN_WITHDRAW,
} selector_t;

// Parameters for deposit selector.
typedef enum {
    DEPOSIT_WITHDRAWAL_ADDRESS = 0,
    DEPOSIT_UNEXPECTED_PARAMETER,
} deposit_parameters;

// Parameters for withdraw selector.
typedef enum {
    WITHDRAW_UNEXPECTED_PARAMETER = 0,
} withdraw_parameters;

extern const uint32_t KILN_SELECTORS[NUM_SELECTORS];

typedef struct context_t {
    uint8_t withdrawal_address[ADDRESS_LENGTH];

    uint8_t next_param;
    uint16_t offset;
    bool go_to_offset;

    selector_t selectorIndex;
} context_t;

_Static_assert(sizeof(context_t) <= 5 * 32, "Structure of parameters too big.");

void handle_provide_parameter(void *parameters);
void handle_query_contract_ui(void *parameters);
void handle_init_contract(void *parameters);
void handle_finalize(void *parameters);
void handle_provide_token(void *parameters);
void handle_query_contract_id(void *parameters);

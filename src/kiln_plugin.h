#pragma once

#include <string.h>

#include "eth_internals.h"
#include "eth_plugin_interface.h"

#define PLUGIN_NAME        "Kiln"
#define VALIDATOR_KEY_SIZE 48

// Available selectors:
//
// 0. deposit()
// 1. withdraw(validator_pubkey)
// 2. withdrawEL(validator_pubkey)
// 3. withdrawCL(validator_pubkey)
//
// More to come!
#define NUM_SELECTORS 4

// Selectors available (see mapping above).
typedef enum {
    KILN_DEPOSIT = 0,
    KILN_WITHDRAW,
    KILN_WITHDRAW_EL,
    KILN_WITHDRAW_CL,
} selector_t;

// Parameters for deposit selector.
typedef enum {
    DEPOSIT_UNEXPECTED_PARAMETER,
} deposit_parameters;

// Parameters for withdraw selectors (applies to withdraw, withdrawEL, withdrawCL)
typedef enum {
    WITHDRAW_VALIDATION_OFFSET = 0,
    WITHDRAW_VALIDATION_LENGTH = 1,
    WITHDRAW_VALIDATION_KEY_PART_1 = 2,  // BLS keys are 48 bytes, thus they are
    WITHDRAW_VALIDATION_KEY_PART_2 = 3,  // taking 2x32 bytes parameters.
    WITHDRAW_UNEXPECTED_PARAMETER,
} withdraw_parameters;

extern const uint32_t KILN_SELECTORS[NUM_SELECTORS];

typedef struct context_t {
    uint8_t validator_address[VALIDATOR_KEY_SIZE];

    uint8_t next_param;

    selector_t selectorIndex;
} context_t;

_Static_assert(sizeof(context_t) <= 5 * 32, "Structure of parameters too big.");

void handle_provide_parameter(void *parameters);
void handle_query_contract_ui(void *parameters);
void handle_init_contract(void *parameters);
void handle_finalize(void *parameters);
void handle_provide_token(void *parameters);
void handle_query_contract_id(void *parameters);

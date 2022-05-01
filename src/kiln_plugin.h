#pragma once

#include <string.h>

#include "eth_internals.h"
#include "eth_plugin_interface.h"

#define PLUGIN_NAME "Kiln"

#define NUM_SELECTORS 1

typedef enum {
  KILN_DEPOSIT = 0
} selector_t;

typedef enum {
  WITHDRAWAL_ADDRESS = 0,  UNEXPECTED_PARAMETER,
} parameter;

extern const uint32_t KILN_SELECTORS[NUM_SELECTORS];

typedef struct context_t {
  uint8_t     withdrawal_address[ADDRESS_LENGTH];

  uint8_t     next_param;
  uint16_t    offset;
  bool        go_to_offset;

  selector_t  selectorIndex;
} context_t;

_Static_assert(sizeof(context_t) <= 5 * 32, "Structure of parameters too big.");

void handle_provide_parameter(void *parameters);
void handle_query_contract_ui(void *parameters);
void handle_init_contract(void *parameters);
void handle_finalize(void *parameters);
void handle_provide_token(void *parameters);
void handle_query_contract_id(void *parameters);

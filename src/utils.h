#pragma once

#include "kiln_plugin.h"
#include "eth_internals.h"

#include "os.h"
#include "cx.h"
#include <string.h>

// Similar to getEthAddressStringFromBinary but for BLS keys.
void getEthBlsAddressStringFromBinary(ethQueryContractUI_t *msg, uint8_t *address);

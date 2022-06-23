#include "eth_internals.h"
#include "utils.h"

void getEthBlsAddressStringFromBinary(ethQueryContractUI_t *msg, uint8_t *address) {
    int i = 0;

    msg->msg[0] = '0';
    msg->msg[1] = 'x';

    for (i = 0; i < 96; i++) {
        uint8_t digit = address[i / 2];
        if ((i % 2) == 0) {
            digit = (digit >> 4) & 0x0f;
        } else {
            digit = digit & 0x0f;
        }
        msg->msg[i + 2] = HEXDIGITS[digit];
    }

    msg->msg[i + 2] = '\0';
}

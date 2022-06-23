#include "bls.h"

// No EIP/ERC regarding BLS keys & checksums, we go uppercase to make it more
// readable in case address starts with a letter (0xa -> 0xA).
static const char UHEXDIGITS[] = "0123456789ABCDEF";

static void displayByteAt(char *msg, uint8_t digit) {
    msg[0] = UHEXDIGITS[(digit >> 4) & 0x0f];
    msg[1] = UHEXDIGITS[digit & 0x0f];
}

// BLS keys are 96 bytes once displayed, we'd need 99 bytes here to properly
// show them but msg->msg is only 43 (it's made with the assumption of eth1
// addresses). Instead, we truncate them to the following pattern:
//
// 0xacbdd2...1c9012
//
// Showing them is more a convenience for the user to confirm it matches the key
// they want to withdraw. This is fine from a security perspective considering
// this tx doesn't send ETH and can only receive it, the mapping is ensured by
// the smart-contract.
void displayEthBlsAddressStringFromBinary(ethQueryContractUI_t *msg, uint8_t *address) {
    msg->msg[0] = '0';
    msg->msg[1] = 'x';

    displayByteAt(&msg->msg[2], address[0]);
    displayByteAt(&msg->msg[4], address[1]);
    displayByteAt(&msg->msg[6], address[2]);

    msg->msg[8] = '.';
    msg->msg[9] = '.';
    msg->msg[10] = '.';

    displayByteAt(&msg->msg[11], address[45]);
    displayByteAt(&msg->msg[13], address[46]);
    displayByteAt(&msg->msg[15], address[47]);
}

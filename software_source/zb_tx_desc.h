#ifndef ZB_TX_DESC_H
#define ZB_TX_DESC_H

#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include "zb_api.h"

//Broadcast options macros.
#define DISABLE_ACK       0x01
#define ENABLE_ENCRYPTION 0x20
#define EXT_TIMEOUT       0x40

//Forward declaration for Zigbee transmit structure.
struct zb_tx;

int tx_command_description(struct zb_tx *tx);
int tx_frame_description(struct zb_tx *tx);

#endif
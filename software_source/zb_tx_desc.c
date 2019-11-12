#include "zb_tx_desc.h"

//This function takes a zb_tx struct as an argument and fills out the frame description
//fields based on what is in the frame.  0 is returned to indicate success.
int tx_frame_description(struct zb_tx *tx) {
    char status_description1[HALF_BUFSZ];
    char status_description2[HALF_BUFSZ];
    int i;

    //Clear any garbage out of description strings.
    tx->frame_description1[0] = 0;
    tx->frame_description2[0] = 0;
    tx->frame_description3[0] = 0;
    tx->frame_description4[0] = 0;

    switch(tx->frame_type) {
        case AT_COMMAND_FRAME:

            break;

        case AT_COMMAND_QUEUE_FRAME:

            break;

        case TRANSMIT_REQUEST_FRAME:
            sprintf(tx->frame_description1, "%s, %s %x, %s %x%x", "Frame Type: Transmit Request", "Frame ID:",
                tx->frame_id, "Destination Serial Number:", tx->serial_high, tx->serial_low);
            sprintf(tx->frame_description2, "%s %x, %s %x", "Network Address:", tx->address, "Broadcast Radius:", tx->broadcast_radius);

            //Build receive options string.
            if(tx->options & DISABLE_ACK)
                strcat(status_description1,  "*Disable Ack* ");
            if(tx->options & ENABLE_ENCRYPTION)
                strcat(status_description1,  "*Encrypted* ");
            if(tx->options & EXT_TIMEOUT)
                strcat(status_description1,  "*Extended Timeout*");

            sprintf(tx->frame_description3, "%s", status_description1);

            //Add raw received data.
            sprintf(tx->frame_description4, "Transmitted Data: %s", tx->rf_data);
            break;

        case EXPLICIT_ADDRESSING_FRAME:

            break;

        case REMOTE_AT_COMMAND_FRAME:

            break;

        case CREATE_SOURCE_ROUTE_FRAME:

            break;

        default:  //Invalid frame type;
            sprintf(tx->frame_description1, "Unknown Frame Type");
            break;
    }
    return 0;
}

//This function takes command data from AT_COMMAND_FRAMEs
//and breaks it down into it's different components.
//It returns 0 on success and -1 if unrecognized AT command.
int tx_command_description(struct zb_tx *tx) {
    char status_description1[HALF_BUFSZ];
    char status_description2[HALF_BUFSZ];


    return 0;
}
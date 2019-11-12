#include "zb_rx_desc.h"

//This function takes an 8 bit AT command status and a character pointer.
//It converts the command status into a human readable string.  A pointer to
//the string is also returned so it can be used in printf statements.
char *print_command_status(uint8_t command_status, char *status_description) {
    switch(command_status) {
        case OK:
            strcpy(status_description, "OK");
            break;
        case ERROR:
            strcpy(status_description, "ERROR");
            break;
        case INVALID_COMMAND:
            strcpy(status_description, "Invalid Command");
            break;
        case INVALID_PARAMETER:
            strcpy(status_description, "Invalid Parameter");
            break;
        case TX_FAILURE:
            strcpy(status_description, "TX Failure");
            break;
        default:
            strcpy(status_description, "Unknown");
            break;
    }
    return status_description;
}

//This function takes an 8 bit modem status and a character pointer.
//It converts the modem status into a human readable string.  A pointer to
//the string is also returned so it can be used in printf statements.
char *print_modem_status(uint8_t modem_status, char *status_description) {
    switch(modem_status) {
        case HARDWARE_RESET:
            strcpy(status_description, "Hardware Reset");
            break;
        case WATCHDOG_TIMER_RESET:
            strcpy(status_description, "Watchdog Timer Reset");
            break;
        case JOINED_NETWORK:
            strcpy(status_description, "Joined Network");
            break;
        case DISASSOCIATED:
            strcpy(status_description, "Disassociated");
            break;
        case COORDINATOR_STARTED:
            strcpy(status_description, "Coordinator Started");
            break;
        case SECURITY_KEY_UPDATED:
            strcpy(status_description, "Network Security Key Updated");
            break;
        case HIGH_VOLTAGE:
            strcpy(status_description, "Voltage Supply Limit Exceeded");
            break;
        case MODEM_RECONFIGURED:
            strcpy(status_description, "Modem Config Changed While Join In Progress");
            break;
        default:
            strcpy(status_description, "Stack Error");
            break;
    }
    return status_description;
}

//This function takes an 8 bit delivery status and a character pointer.
//It converts the delivery status into a human readable string.  A pointer to
//the string is also returned so it can be used in printf statements.
char *print_delivery_status(uint8_t delivery_status, char *status_description) {
    switch(delivery_status) {
        case SUCCESS:
            strcpy(status_description, "Success");
            break;
        case MAC_ACK_FAILURE:
            strcpy(status_description, "MAC ACK Failure");
            break;
        case CCA_FAILURE:
            strcpy(status_description, "CCA Failure");
            break;
        case INVALID_DEST_ENDPOINT:
            strcpy(status_description, "Invalid Destination Endpoint");
            break;
        case NETWORK_ACK_FAILURE:
            strcpy(status_description, "Network ACK Failure");
            break;
        case NOT_JOINED:
            strcpy(status_description, "Not Joined To Network");
            break;
        case SELF_ADDRESSED:
            strcpy(status_description, "Self Addressed");
            break;
        case ADDRESS_NOT_FOUND:
            strcpy(status_description, "Address Not Found");
            break;
        case ROUTE_NOT_FOUND:
            strcpy(status_description, "Route Not Found");
            break;
        case BCAST_SOURCE_FAILED:
            strcpy(status_description, "Broadcast Source Failed To Hear A Neighbor Relay The Message");
            break;
        case INVALID_BINDING_TBL_IND:
            strcpy(status_description, "Invalid Binding Table Index");
            break;
        case RESOURCE_ERROR1:
            strcpy(status_description, "Resource Error");
            break;
        case APS_BCAST_FAILED:
            strcpy(status_description, "APS Broadcast Failed");
            break;
        case APS_UNICAST_FAILED:
            strcpy(status_description, "APS Unicast Failed");
            break;
        case RESOURCE_ERROR2:
            strcpy(status_description, "Resource Error");
            break;
        case PAYLOAD_TOO_LARGE:
            strcpy(status_description, "Data Payload Too Large");
            break;
        case INDIRECT_MESSAGE_RQ:
            strcpy(status_description, "Indirect Message Unrequested");
            break;
        default:
            strcpy(status_description, "Unknown");
            break;
    }
    return status_description;
}

//This function takes an 8 bit discovery status and a character pointer.
//It converts the discovery status into a human readable string.  A pointer to
//the string is also returned so it can be used in printf statements.
char *print_discovery_status(uint8_t discovery_status, char *status_description) {
    switch(discovery_status) {
        case NO_DISCOVERY_OVERHEAD:
            strcpy(status_description, "No Discovery Overhead");
            break;
        case ADDRESS_DISCOVERY:
            strcpy(status_description, "Address Discovery");
            break;
        case ROUTE_DISCOVERY:
            strcpy(status_description, "Route Discovery");
            break;
        case ADDRESS_AND_ROUTE:
            strcpy(status_description, "Address And Route Discovery");
            break;
        case EXTENDED_TIMEOUT:
            strcpy(status_description, "Extended Timeout Discovery");
            break;
        default:
            strcpy(status_description, "Unknown");
            break;
    }
    return status_description;
}

//This function takes an 8 bit discovery options and a character pointer.
//It converts the discovery options into a human readable string.  A pointer to
//the string is also returned so it can be used in printf statements.
char *network_discovery_options(uint8_t discovery_option, char *status_description) {
    switch(discovery_option) {
        case NO_DISCOVERY_OPTIONS:
            strcpy(status_description, "None");
            break;
        case APPEND_DD_VALUE:
            strcpy(status_description, "Append Device Type Identifier");
            break;
        case LOCAL_ND:
            strcpy(status_description, "Local ND Response");
            break;
        case BOTH_DISC_OPTIONS:
            strcpy(status_description, "Append Device Type Identifier And Local ND Response");
            break;
        default:
            strcpy(status_description, "Unknown");
            break;
    }
    return status_description;
}

//This function takes an 8 bit node join time and a character pointer.
//It converts the node join time into a human readable string.  A pointer to
//the string is also returned so it can be used in printf statements.
char *node_join_time(uint8_t join_time, char *status_description) {
    char jt[20];
    switch(join_time) {
        case 0xFF:
            strcpy(status_description, "Always Allow Joining");
            break;
        default:
            sprintf(jt, "%d Seconds", join_time);
            strcpy(status_description, jt);
            break;
    }
    return status_description;
}

//This function takes an 8 bit channel verification and a character pointer.
//It converts the channel verification into a human readable string.  A pointer to
//the string is also returned so it can be used in printf statements.
char *channel_verify(uint8_t ch_verification, char *status_description) {
    switch(ch_verification) {
        case CH_VERIFY_DISABLED:
            strcpy(status_description, "Disabled");
            break;
        case CH_VERIFY_ENABLED:
            strcpy(status_description, "Enabled");
            break;
        default:            
            strcpy(status_description, "Unknown");
            break;
    }
    return status_description;
}

//This function takes an 8 bit device type and a character pointer.
//It converts the device type into a human readable string.  A pointer to
//the string is also returned so it can be used in printf statements.
char *device_type(uint8_t dev, char *status_description) {
    switch(dev) {
        case COORDINATOR:
            strcpy(status_description, "Coordinator");
            break;
        case ROUTER:
            strcpy(status_description, "Router");
            break;
        case END_DEVICE:
            strcpy(status_description, "End Device");
            break;
        default:
            strcpy(status_description, "Unknown");
            break;
    }
    return status_description;
}

//This function takes an 8 bit source event and a character pointer.
//It converts the source event into a human readable string.  A pointer to
//the string is also returned so it can be used in printf statements.
char *source_event(uint8_t event, char *status_description) {
    switch(event) {
        case PUSHBUTTON:
            strcpy(status_description, "Pushbutton");
            break;
        case JOIN:
            strcpy(status_description, "Join");
            break;
        case POWER_CYCLE:
            strcpy(status_description, "Power Cycle");
            break;
        default:
            strcpy(status_description, "Unknown");
            break;
    }
    return status_description;
}

//This function takes a zb_rx struct as an argument and fills out the frame description
//fields based on what is in the frame.  0 is returned to indicate success.
int write_frame_description(struct zb_rx *rx) {
    char status_description1[HALF_BUFSZ];
    char status_description2[HALF_BUFSZ];
    int i;

    switch(rx->frame_type) {
        case AT_COMMAND_RESPONSE_FRAME:
            sprintf(rx->frame_description1, "%s, %s %x, %s %c%c, %s %s", "Frame Type: AT Command Response",
                "Frame ID:", rx->frame_id, "AT Command:", rx->at_command.first_letter, rx->at_command.second_letter,                 
                "Command Status:", print_command_status(rx->command_status, status_description1));
            break;

        case MODEM_STATUS_FRAME:
            sprintf(rx->frame_description1, "%s, %s %s", "Frame Type: Modem Status", "Modem Status:",
                print_modem_status(rx->modem_status, status_description1));
            break;

        case TRANSMIT_STATUS_FRAME:
            sprintf(rx->frame_description1, "%s, %s %x, %s %x", "Frame Type: Transmit Status", "Frame ID:",
                rx->frame_id, "Destination Network Address:", rx->source_address);
            sprintf(rx->frame_description2, "%s %x, %s %s, %s %s", "Transmit Retry Count:", rx->retry_count,
                "Delivery Status:", print_delivery_status(rx->delivery_status, status_description1), "Discovery Status:",
                print_discovery_status(rx->discovery_status, status_description2));
            break;

        case RECEIVE_PACKET_FRAME:
            sprintf(rx->frame_description1, "%s, %s %x%x, %s %x", "Frame Type: Receive Packet", "Source Serial Number:",
                rx->source_serial_hi, rx->source_serial_lo, "Source Network Address:", rx->source_address);
            strcpy(status_description1, "Receive Options: ");
            
            //Build receive options string.
            if(rx->options & PACKET_ACK)
                strcat(status_description1,  "*Acked* ");
            if(rx->options & BCAST_PACKET)
                strcat(status_description1,  "*Broadcast* ");
            if(rx->options & APS_ENCRYPTION)
                strcat(status_description1,  "*Encrypted* ");
            if(rx->options & END_DEVICE_PACKET)
                strcat(status_description1,  "*From End Device*");

            sprintf(rx->frame_description2, "%s", status_description1);

            //Add raw received data.
            sprintf(rx->frame_description4, "Received Data: ");

            for(i = 0; i < rx->received_data_length; i++) {
                sprintf(status_description1, "%x", rx->received_data[i]);
                strcat(rx->frame_description4, status_description1);
            }
            break;

        case EXPLICIT_RX_INDICATOR_FRAME:
            sprintf(rx->frame_description1, "%s, %s %x%x, %s %x", "Frame Type: Explicit RX Indicator ", "Source Serial Number:",
                rx->source_serial_hi, rx->source_serial_lo, "Source Network Address:", rx->source_address);
            strcpy(status_description1, "Receive Options: ");
            
            //Build receive options string.
            if(rx->options & PACKET_ACK)
                strcat(status_description1,  "*Acked* ");
            if(rx->options & BCAST_PACKET)
                strcat(status_description1,  "*Broadcast* ");
            if(rx->options & APS_ENCRYPTION)
                strcat(status_description1,  "*Encrypted* ");
            if(rx->options & END_DEVICE_PACKET)
                strcat(status_description1,  "*From End Device*");

            sprintf(rx->frame_description2, "%s", status_description1);

            //Add explicit data.
            sprintf(rx->frame_description3, "%s %x, %s %x, %s %x, %s %x", "Source Endpoint:", rx->source_endpoint, "Dest. Endpoint:",
                rx->destination_endpoint, "Cluster ID:", rx->cluster_id, "Profile ID:", rx->profile_id);

            //Add raw received data.
            sprintf(rx->frame_description4, "Received Data: ");

            for(i = 0; i < rx->received_data_length; i++) {
                sprintf(status_description1, "%x", rx->received_data[i]);
                strcat(rx->frame_description4, status_description1);
            }

            break;

        case IO_DATA_SAMPLE_RX_INDICATOR_FRAME:
            sprintf(rx->frame_description1, "%s, %s %x%x, %s %x", "Frame Type: IO Sample RX ", "Source Serial Number:",
                rx->source_serial_hi, rx->source_serial_lo, "Source Network Address:", rx->source_address);

            //Build receive options string.
            strcpy(status_description1, "Receive Options: ");
            if(rx->options & PACKET_ACK)
                strcat(status_description1, "*Acked* ");
            if(rx->options & BCAST_PACKET)
                strcat(status_description1, "*Broadcast* ");

            sprintf(rx->frame_description2, "%s, %s %x, %s %x, %s %x", status_description1, "Number Of Samples:",
                rx->number_of_samples, "Digital Channel Mask:", rx->digital_mask, "Analog Channel Mask:", rx->analog_mask);
            
            //Build digital samples string.
            status_description1[0] = 0; //clear string.
            if(rx->digital_mask & D_0) {
                sprintf(status_description2, "D0:%d ", (rx->digital_samples & D_0) ? 1 : 0);
                strcat(status_description1, status_description2);
            }
            if(rx->digital_mask & D_1) {
                sprintf(status_description2, "D1:%d ", (rx->digital_samples & D_1) ? 1 : 0);
                strcat(status_description1, status_description2);
            }
            if(rx->digital_mask & D_2) {
                sprintf(status_description2, "D2: %d ", (rx->digital_samples & D_2) ? 1 : 0);
                strcat(status_description1, status_description2);
            }
            if(rx->digital_mask & D_3) {
                sprintf(status_description2, "D3:%d ", (rx->digital_samples & D_3) ? 1 : 0);
                strcat(status_description1, status_description2);
            }
            if(rx->digital_mask & D_4) {
                sprintf(status_description2, "D4:%d ", (rx->digital_samples & D_4) ? 1 : 0);
                strcat(status_description1, status_description2);
            }
            if(rx->digital_mask & D_5) {
                sprintf(status_description2, "D5:%d ", (rx->digital_samples & D_5) ? 1 : 0);
                strcat(status_description1, status_description2);
            }
            if(rx->digital_mask & D_6) {
                sprintf(status_description2, "D6:%d ", (rx->digital_samples & D_6) ? 1 : 0);
                strcat(status_description1, status_description2);
            }
            if(rx->digital_mask & D_7) {
                sprintf(status_description2, "D7:%d ", (rx->digital_samples & D_7) ? 1 : 0);
                strcat(status_description1, status_description2);
            }
            if(rx->digital_mask & D_10) {
                sprintf(status_description2, "D10:%d ", (rx->digital_samples & D_10) ? 1 : 0);
                strcat(status_description1, status_description2);
            }
            if(rx->digital_mask & D_11) {
                sprintf(status_description2, "D11:%d ", (rx->digital_samples & D_11) ? 1 : 0);
                strcat(status_description1, status_description2);
            }
            if(rx->digital_mask & D_12) {
                sprintf(status_description2, "D12:%d ", (rx->digital_samples & D_12) ? 1 : 0);
                strcat(status_description1, status_description2);
            }
            sprintf(rx->frame_description3, "%s", status_description1);

            //Build analog samples string.
            status_description1[0] = 0; //clear string.
            if(rx->analog_mask & ADC_0) {
                sprintf(status_description2, "ADC0:%dmV ", rx->adc0 * 1200 / 1024);
                strcat(status_description1, status_description2);
            }
            if(rx->analog_mask & ADC_1) {
                sprintf(status_description2, "ADC1:%dmV ", rx->adc1 * 1200 / 1024);
                strcat(status_description1, status_description2);
            }
            if(rx->analog_mask & ADC_2) {
                sprintf(status_description2, "ADC2:%dmV ", rx->adc2 * 1200 / 1024);
                strcat(status_description1, status_description2);
            }
            if(rx->analog_mask & ADC_3) {
                sprintf(status_description2, "ADC3:%dmV ", rx->adc3 * 1200 / 1024);
                strcat(status_description1, status_description2);
            }
            if(rx->analog_mask & ADC_VCC) {
                sprintf(status_description2, "ADC_VCC:%dmV ", rx->adc_vcc * 1200 / 1024);
                strcat(status_description1, status_description2);
            }
            sprintf(rx->frame_description2, "%s", status_description1);
            break;

        case SENSOR_READ_INDICATOR_FRAME: //To be completed when a 1-wire Digi sensor is needed...  
            break;

        case NODE_ID_INDICATOR_FRAME:
            sprintf(rx->frame_description1, "%s, %s %x%x, %s %x", "Frame Type: Node ID Indicator", "Sender Serial Number:",
                rx->sender_serial_hi, rx->sender_serial_lo, "Sender Network Address:", rx->sender_address);

            //Build receive options string.
            strcpy(status_description1, "Receive Options: ");
            if(rx->options & PACKET_ACK)
                strcat(status_description1,  "*Acked* ");
            if(rx->options & BCAST_PACKET)
                strcat(status_description1,  "*Broadcast* ");

            sprintf(rx->frame_description2, "%s, %s %x, %s %x%x", status_description1, "Source Network Address:", rx->source_address,
                "Source Serial Number:", rx->source_serial_hi, rx->source_serial_lo);

            sprintf(rx->frame_description3, "%s %s, %s %x, %s %s", "Node ID String:", rx->param_value.ni_value,
                "Parent Network Address:", rx->parent_address, "Device Type:", device_type(rx->device_type, status_description2));

            sprintf(rx->frame_description4, "%s %s, %s %x, %s %x", "Source Event:", source_event(rx->source_event, status_description2),
                "Profile ID:", rx->profile_id, "Manufacturer ID:", rx->manufacturer_id);

            //Add device type ID, if present.
            if(rx->device_type_id) {
                sprintf(status_description2, ", %s %x", "Device Type ID:", rx->device_type_id);
                strcat(rx->frame_description4, status_description2);
            }
            break;

        case REMOTE_COMMAND_RESPONSE_FRAME:
            sprintf(rx->frame_description1, "%s, %s %x, %s %c%c, %s %s", "Frame Type: Remote AT Command Response",
                "Frame ID:", rx->frame_id, "AT Command:", rx->at_command.first_letter, rx->at_command.second_letter,                 
                "Command Status:", print_command_status(rx->command_status, status_description1));
            sprintf(rx->frame_description2, "%s %x%x, %s %x", "Source Serial Number:", rx->source_serial_hi,
                rx->source_serial_lo, "Source Network Address:", rx->source_address);
            break;

        case OTA_FIRMWARE_UPDATE_STATUS_FRAME: //To be completed when over the air firmware updates are required...
            break;

        case ROUTE_RECORD_INDICATOR_FRAME:
            sprintf(rx->frame_description1, "%s, %s %x%x", "Frame Type: Route Record Indicator", "Source Serial Number:",
                rx->source_serial_hi, rx->source_serial_lo);
            sprintf(rx->frame_description2, "%s %x, %s %x, %s %d", "Source Network Address:", rx->source_address, "Receive Options:",
                rx->options, "Number Of Addresses:", rx->num_addresses);
            sprintf(rx->frame_description3, "Address List: ");
            for(i = 0; i < rx->num_addresses; i++) {
                sprintf(status_description1, "%x ", rx->addresses[i]);
                strcat(rx->frame_description3, status_description1);
            }
            break;

        case MTO_ROUTE_REQUEST_INDICATOR_FRAME:
            sprintf(rx->frame_description1, "%s, %s %x%x", "Frame Type: Many-To-One Route Request Indicator", "Source Serial Number:",
                rx->source_serial_hi, rx->source_serial_lo);
            sprintf(rx->frame_description2, "%s %x, %s %x", "Source Network Address:", rx->source_address, "Reserved:", rx->reserved);
            break;

        default:
            sprintf(rx->frame_description1, "Unknown Frame Type");
            break;
    }
    return 0;
}

//This function takes command data from AT_COMMAND_RESPONSE_FRAMEs
//and breaks it down into it's different components.  It returns 0
//on success and -1 if unrecognized AT command.
int write_command_description(struct zb_rx *rx) {
    char    status_description1[HALF_BUFSZ], status_description2[HALF_BUFSZ];
    uint8_t par_net_index, device_type_index, status_index, profile_id_index, manufacturer_id_index, dev_type_id_index;
    uint8_t io_dig_sample_index, io_an_sample_index, i;

    //DH
    if(rx->at_command.first_letter  == 'D' && rx->at_command.second_letter == 'H') {
        rx->atcmd = DH;  
        rx->param_value.serial_high = bytes_to_uint32(rx->command_data);      
        sprintf(rx->frame_description3, "Destination Serial High: %x", rx->param_value.serial_high);      
    }
    //DL
    else if(rx->at_command.first_letter  == 'D' && rx->at_command.second_letter == 'L') {
        rx->atcmd = DL;
        rx->param_value.serial_low = bytes_to_uint32(rx->command_data);
        sprintf(rx->frame_description3, "Destination Serial Low: %x", rx->param_value.serial_low);        
    }
    //MY
    else if(rx->at_command.first_letter  == 'M' && rx->at_command.second_letter == 'Y') {
        rx->atcmd = MY;
        rx->param_value.network_address = bytes_to_uint16(rx->command_data);
        sprintf(rx->frame_description3, "Network Address: %x", rx->param_value.network_address);
    }
    //MP
    else if(rx->at_command.first_letter  == 'M' && rx->at_command.second_letter == 'P') {
        rx->atcmd = MP;
        rx->param_value.parent_address = bytes_to_uint16(rx->command_data);
        sprintf(rx->frame_description3, "Parent Network Address: %x", rx->param_value.parent_address);
    }
    //NC
    else if(rx->at_command.first_letter  == 'N' && rx->at_command.second_letter == 'C') {
        rx->atcmd = NC;
        rx->param_value.children_remaining = *rx->command_data;
        sprintf(rx->frame_description3, "Number Of Remaining Children: %x", rx->param_value.children_remaining);
    }
    //SH
    else if(rx->at_command.first_letter  == 'S' && rx->at_command.second_letter == 'H') {
        rx->atcmd = SH;
        rx->param_value.serial_high = bytes_to_uint32(rx->command_data);      
        sprintf(rx->frame_description3, "Serial High: %x", rx->param_value.serial_high);
    }
    //SL
    else if(rx->at_command.first_letter  == 'S' && rx->at_command.second_letter == 'L') {
        rx->atcmd = SL;
        rx->param_value.serial_low = bytes_to_uint32(rx->command_data);
        sprintf(rx->frame_description3, "Serial Low: %x", rx->param_value.serial_low);
    }
    //NI
    else if(rx->at_command.first_letter  == 'N' && rx->at_command.second_letter == 'I') {
        rx->atcmd = NI;
        strcpy(rx->param_value.node_identifier, rx->command_data);
        sprintf(rx->frame_description3, "Node Identifier: %s", rx->param_value.node_identifier);
    }
    //SE
    else if(rx->at_command.first_letter  == 'S' && rx->at_command.second_letter == 'E') {
        rx->atcmd = SE;
        rx->param_value.source_endpoint = *rx->command_data;
        sprintf(rx->frame_description3, "Source Endpoint: %x", rx->param_value.source_endpoint);
    }
    //DE
    else if(rx->at_command.first_letter  == 'D' && rx->at_command.second_letter == 'E') {
        rx->atcmd = DE;
        rx->param_value.dest_endpoint = *rx->command_data;
        sprintf(rx->frame_description3, "Destination Endpoint: %x", rx->param_value.dest_endpoint);
    }
    //CI
    else if(rx->at_command.first_letter  == 'C' && rx->at_command.second_letter == 'I') {
        rx->atcmd = CI;
        rx->param_value.cluster_identifier = bytes_to_uint16(rx->command_data);
        sprintf(rx->frame_description3, "Cluster Identifier: %x", rx->param_value.cluster_identifier);
    }
    //NP
    else if(rx->at_command.first_letter  == 'N' && rx->at_command.second_letter == 'P') {
        rx->atcmd = NP;
        rx->param_value.max_payload = bytes_to_uint16(rx->command_data);
        sprintf(rx->frame_description3, "Maximum RF Payload Bytes: %x", rx->param_value.max_payload);
    }
    //DD
    else if(rx->at_command.first_letter  == 'D' && rx->at_command.second_letter == 'D') {
        rx->atcmd = DD;
        rx->param_value.dev_type_identifier = bytes_to_uint32(rx->command_data);
        sprintf(rx->frame_description3, "Device Type Identifier: %x", rx->param_value.dev_type_identifier);
    }
    //CH
    else if(rx->at_command.first_letter  == 'C' && rx->at_command.second_letter == 'H') {
        rx->atcmd = CH;
        rx->param_value.operating_channel = *rx->command_data;
        sprintf(rx->frame_description3, "Operating Channel: %x", rx->param_value.operating_channel);
    }
    //ID
    else if(rx->at_command.first_letter  == 'I' && rx->at_command.second_letter == 'D') {
        rx->atcmd = ID;
        rx->param_value.extended_pan_id[0] = bytes_to_uint32(rx->command_data);
        rx->param_value.extended_pan_id[1] = bytes_to_uint32(&rx->command_data[4]);
        sprintf(rx->frame_description3, "Extended PAN ID: %x%x",
            rx->param_value.extended_pan_id[0], rx->param_value.extended_pan_id[1]);
    }
    //OP
    else if(rx->at_command.first_letter  == 'O' && rx->at_command.second_letter == 'P') {
        rx->atcmd = OP;
        rx->param_value.op_extended_pan_id[0] = bytes_to_uint32(rx->command_data);
        rx->param_value.op_extended_pan_id[1] = bytes_to_uint32(&rx->command_data[4]);
        sprintf(rx->frame_description3, "Operating Extended PAN ID: %x%x",
            rx->param_value.op_extended_pan_id[0], rx->param_value.op_extended_pan_id[1]);
    }
    //NH
    else if(rx->at_command.first_letter  == 'N' && rx->at_command.second_letter == 'H') {
        rx->atcmd = NH;
        rx->param_value.max_unicast_hops = *rx->command_data;
        sprintf(rx->frame_description3, "Maximum Unicast Hops: %x", rx->param_value.max_unicast_hops);
    }
    //BH
    else if(rx->at_command.first_letter  == 'B' && rx->at_command.second_letter == 'H') {
        rx->atcmd = BH;
        rx->param_value.max_broadcast_hops = *rx->command_data;
        sprintf(rx->frame_description3, "Maximum Broadcast Hops: %x", rx->param_value.max_broadcast_hops);
    }
    //OI
    else if(rx->at_command.first_letter  == 'O' && rx->at_command.second_letter == 'I') {
        rx->atcmd = OI;
         rx->param_value.pan_id = bytes_to_uint16(rx->command_data);
        sprintf(rx->frame_description3, "Operating 16-bit PAN ID: %x", rx->param_value.pan_id);
    }
    //NT
    else if(rx->at_command.first_letter  == 'N' && rx->at_command.second_letter == 'T') {
        rx->atcmd = NT;
        rx->param_value.Node_disc_timeout = bytes_to_uint16(rx->command_data);
        sprintf(rx->frame_description3, "Node Discovery Timeout: %x (%d Milliseconds)",
            rx->param_value.Node_disc_timeout, rx->param_value.Node_disc_timeout * 100);
    }
    //NO
    else if(rx->at_command.first_letter  == 'N' && rx->at_command.second_letter == 'O') {
        rx->atcmd = NO;
        rx->param_value.ntwk_disc_options = *rx->command_data;
        sprintf(rx->frame_description3, "Network Discovery Options: %s",
        network_discovery_options(rx->param_value.ntwk_disc_options, status_description1));
    }
    //SC
    else if(rx->at_command.first_letter  == 'S' && rx->at_command.second_letter == 'C') {
        rx->atcmd = SC;
        rx->param_value.scan_channel_bitfield = bytes_to_uint16(rx->command_data);
        sprintf(rx->frame_description3, "Scan Channels Bitmask: %x", rx->param_value.scan_channel_bitfield);  
    }
    //SD
    else if(rx->at_command.first_letter  == 'S' && rx->at_command.second_letter == 'D') {
        rx->atcmd = SD;
        rx->param_value.scan_duration = *rx->command_data;
        sprintf(rx->frame_description3, "Scan Duration Exponent: %x", rx->param_value.scan_duration);
    }
    //ZS
    else if(rx->at_command.first_letter  == 'Z' && rx->at_command.second_letter == 'S') {
        rx->atcmd = ZS;
        rx->param_value.zigbee_stack_profile = *rx->command_data;
        sprintf(rx->frame_description3, "Zigbee Stack Profile: %x", rx->param_value.zigbee_stack_profile);
    }
    //NJ
    else if(rx->at_command.first_letter  == 'N' && rx->at_command.second_letter == 'J') {
        rx->atcmd = NJ;
        rx->param_value.node_join_time = *rx->command_data;
        sprintf(rx->frame_description3, "Node Join Time: %x (%s)", rx->param_value.node_join_time,
            node_join_time(rx->param_value.node_join_time, status_description1));
    }
    //JV
    else if(rx->at_command.first_letter  == 'J' && rx->at_command.second_letter == 'V') {
        rx->atcmd = JV;
        rx->param_value.channel_verification = *rx->command_data;
        sprintf(rx->frame_description3, "Channel Verification: %s",
            channel_verify(rx->param_value.channel_verification, status_description1));
    }
    //NW
    else if(rx->at_command.first_letter  == 'N' && rx->at_command.second_letter == 'W') {
        rx->atcmd = NW;
        rx->param_value.ntwk_watchdog_timeout = bytes_to_uint16(rx->command_data);
        if(!rx->param_value.ntwk_watchdog_timeout)
            sprintf(rx->frame_description3, "Network Watchdog Timeout: Disabled");
        else
            sprintf(rx->frame_description3, "Network Watchdog Timeout: %x (%d Minutes)", rx->param_value.ntwk_watchdog_timeout,
                rx->param_value.ntwk_watchdog_timeout);
    }
    //JN
    else if(rx->at_command.first_letter  == 'J' && rx->at_command.second_letter == 'N') {
        rx->atcmd = JN;
        rx->param_value.join_notification = *rx->command_data;
        sprintf(rx->frame_description3, "Join Notification: %s", rx->param_value.join_notification ? "Enabled" : "Disabled");
    }
    //AR
    else if(rx->at_command.first_letter  == 'A' && rx->at_command.second_letter == 'R') {
        rx->atcmd = AR;
        rx->param_value.aggr_rte_notification = *rx->command_data;
        sprintf(rx->frame_description3, "Aggregate Routing Notification: %x", rx->param_value.aggr_rte_notification);
    }
    //EE
    else if(rx->at_command.first_letter  == 'E' && rx->at_command.second_letter == 'E') {
        rx->atcmd = EE;
        rx->param_value.encryption_enable = *rx->command_data;
        sprintf(rx->frame_description3, "Encryption: %s", rx->param_value.encryption_enable ? "Enabled" : "Disabled");
    }
    //EO
    else if(rx->at_command.first_letter  == 'E' && rx->at_command.second_letter == 'O') {
        rx->atcmd = EO;
        rx->param_value.encryption_options = *rx->command_data;
        sprintf(rx->frame_description3, "Encryption Options: %s",
            (rx->param_value.encryption_options == NO_ENC_OPTIONS)    ? "No Encryption Options" :           
            (rx->param_value.encryption_options == SEND_SECURITY_KEY) ? "Security Key Sent Unsecured" :            
            (rx->param_value.encryption_options == USE_TRUST_CENTER)  ? "Use Trust Center" :
            (rx->param_value.encryption_options == BOTH_ENC_OPTIONS)  ? "Security Key Sent Unsecured And Use Trust Center" :           
            "Unknown");
    }
    //PL
    else if(rx->at_command.first_letter  == 'P' && rx->at_command.second_letter == 'L') {
        rx->atcmd = PL;
        rx->param_value.power_level = *rx->command_data;
        sprintf(rx->frame_description3, "Power Level: %x", rx->param_value.power_level);
    }
    //PM
    else if(rx->at_command.first_letter  == 'P' && rx->at_command.second_letter == 'M') {
        rx->atcmd = PM;
        rx->param_value.power_mode = *rx->command_data;
        sprintf(rx->frame_description3, "Boost Mode: %s", rx->param_value.power_mode ? "Enabled" : "Disabled");
    }
    //DB
    else if(rx->at_command.first_letter  == 'D' && rx->at_command.second_letter == 'B') {
        rx->atcmd = DB;
        rx->param_value.rx_signal_strength = *rx->command_data;
        sprintf(rx->frame_description3, "Signal Strength: %x", rx->param_value.rx_signal_strength);
    }
    //PP
    else if(rx->at_command.first_letter  == 'P' && rx->at_command.second_letter == 'P') {
        rx->atcmd = PP;
        rx->param_value.peak_power = *rx->command_data;
        sprintf(rx->frame_description3, "Peak Power: %x", rx->param_value.peak_power);
    }
    //AP
    else if(rx->at_command.first_letter  == 'A' && rx->at_command.second_letter == 'P') {
        rx->atcmd = AP;
        rx->param_value.api_enable = *rx->command_data;
        sprintf(rx->frame_description3, "API Mode: %x", rx->param_value.api_enable);
    }
    //AO
    else if(rx->at_command.first_letter  == 'A' && rx->at_command.second_letter == 'O') {
        rx->atcmd = AO;
        rx->param_value.api_options = *rx->command_data;
        sprintf(rx->frame_description3, "API Options: %s",
            (rx->param_value.api_options == DEFAULT_API_OPTIONS)   ? "Default Indicators" :
            (rx->param_value.api_options == EXP_RX_INICATOR_FRAME) ? "Explicit RX Indicator Frame" :
            (rx->param_value.api_options == ZDO_PASSTHROUGH)       ? "ZDO Passthrough" :
            "Unknown");
    }
    //BD
    else if(rx->at_command.first_letter  == 'B' && rx->at_command.second_letter == 'D') {
        rx->atcmd = BD;
        rx->param_value.data_rate = bytes_to_uint32(rx->command_data);
        sprintf(rx->frame_description3, "Baud Rate: %d",
            (rx->param_value.data_rate == BAUD_1200)   ? 1200   :
            (rx->param_value.data_rate == BAUD_2400)   ? 2400   :
            (rx->param_value.data_rate == BAUD_4800)   ? 4800   :
            (rx->param_value.data_rate == BAUD_9600)   ? 9600   :
            (rx->param_value.data_rate == BAUD_19200)  ? 19200  :
            (rx->param_value.data_rate == BAUD_38400)  ? 38400  :
            (rx->param_value.data_rate == BAUD_57600)  ? 57600  :
            (rx->param_value.data_rate == BAUD_115200) ? 115200 :
            rx->param_value.data_rate);
    }
    //NB
    else if(rx->at_command.first_letter  == 'N' && rx->at_command.second_letter == 'B') {
        rx->atcmd = NB;
        rx->param_value.serial_parity = *rx->command_data;
        sprintf(rx->frame_description3, "Serial Parity: %s",
            (rx->param_value.serial_parity == NO_PARITY)   ? "No Parity"   :
            (rx->param_value.serial_parity == EVEN_PARITY) ? "Even Parity" :
            (rx->param_value.serial_parity == ODD_PARITY)  ? "Odd Parity"  :
            (rx->param_value.serial_parity == MARK_PARITY) ? "Mark Parity" :
            "Unknown");
    }
    //SB
    else if(rx->at_command.first_letter  == 'S' && rx->at_command.second_letter == 'B') {
        rx->atcmd = SB;
        rx->param_value.stop_bits = *rx->command_data;
        sprintf(rx->frame_description3, "Stop Bits: %s",
            (rx->param_value.stop_bits == STOP_BITS_1) ? "1" :
            (rx->param_value.stop_bits == STOP_BITS_2) ? "2" :
            "Unknown");
    }
    //RO
    else if(rx->at_command.first_letter  == 'R' && rx->at_command.second_letter == 'O') {
        rx->atcmd = RO;
        rx->param_value.packetization_timeout = *rx->command_data;
        sprintf(rx->frame_description3, "Packetization Timeout: %x", rx->param_value.packetization_timeout);
    }
    //D7
    else if(rx->at_command.first_letter  == 'D' && rx->at_command.second_letter == '7') {
        rx->atcmd = D7;
        rx->param_value.dio7_config = *rx->command_data;
        sprintf(rx->frame_description3, "DIO7 Configuration: %s",
            (rx->param_value.dio7_config == DIO_DISABLED)          ? "Disabled"                     :
            (rx->param_value.dio7_config == DIO7_CTS_FLOW_CONTROL) ? "CTS Flow Control"             :
            (rx->param_value.dio7_config == DIO_DIGITAL_INPUT)     ? "Digital Input"                :
            (rx->param_value.dio7_config == DIO_DIGITAL_OUTPUT_LO) ? "Digital Output, Low"          :
            (rx->param_value.dio7_config == DIO_DIGITAL_OUTPUT_HI) ? "Digital Output, High"         :
            (rx->param_value.dio7_config == DIO7_RS485_LO_ENABLE)  ? "RS-485 Transmit Enable, Low"  :
            (rx->param_value.dio7_config == DIO7_RS485_HI_ENABLE)  ? "RS-485 Transmit Enable, High" :
            "Unknown");
    }
    //D6
    else if(rx->at_command.first_letter  == 'D' && rx->at_command.second_letter == '6') {
        rx->atcmd = D6;
        rx->param_value.dio6_config = *rx->command_data;
        sprintf(rx->frame_description3, "DIO6 Configuration: %s",
            (rx->param_value.dio6_config == DIO_DISABLED)          ? "Disabled"             :
            (rx->param_value.dio6_config == DIO6_RTS_FLOW_CONTROL) ? "RTS Flow Control"     :
            (rx->param_value.dio6_config == DIO_DIGITAL_INPUT)     ? "Digital Input"        :
            (rx->param_value.dio6_config == DIO_DIGITAL_OUTPUT_LO) ? "Digital Output, Low"  :
            (rx->param_value.dio6_config == DIO_DIGITAL_OUTPUT_HI) ? "Digital Output, High" :            
            "Unknown");
    }
    //IR
    else if(rx->at_command.first_letter  == 'I' && rx->at_command.second_letter == 'R') {
        rx->atcmd = IR;
        rx->param_value.io_sample_rate = *rx->command_data;
        if(!rx->param_value.io_sample_rate)
            sprintf(rx->frame_description3, "IO Sample Rate: Disabled");
        else
            sprintf(rx->frame_description3, "IO Sample Rate: %d Milliseconds", rx->param_value.io_sample_rate);
    }
    //IC
    else if(rx->at_command.first_letter  == 'I' && rx->at_command.second_letter == 'C') {
        rx->atcmd = IC;
        rx->param_value.io_dig_change_detect = bytes_to_uint16(rx->command_data);
        sprintf(rx->frame_description3, "IO Digital Change Detection Bitmask: %x", rx->param_value.io_dig_change_detect);
    }
    //P0
    else if(rx->at_command.first_letter  == 'P' && rx->at_command.second_letter == '0') {
        rx->atcmd = P0;
        rx->param_value.pwm0_config = *rx->command_data;
        sprintf(rx->frame_description3, "PWM0 Configuration: %s",
            (rx->param_value.pwm0_config == DIO_DISABLED)          ? "Disabled"             :
            (rx->param_value.pwm0_config == RSSI_PWM)              ? "RSSI PWM"             :
            (rx->param_value.pwm0_config == DIO_DIGITAL_INPUT)     ? "Digital Input"        :
            (rx->param_value.pwm0_config == DIO_DIGITAL_OUTPUT_LO) ? "Digital Output, Low"  :
            (rx->param_value.pwm0_config == DIO_DIGITAL_OUTPUT_HI) ? "Digital Output, High" :            
            "Unknown");
    }
    //P1
    else if(rx->at_command.first_letter  == 'P' && rx->at_command.second_letter == '1') {
        rx->atcmd = P1;
        rx->param_value.pwm1_config = *rx->command_data;
        sprintf(rx->frame_description3, "PWM1 Configuration: %s",
            (rx->param_value.pwm1_config == DIO_DIGITAL_INPUT_UNMOM) ? "Unmonitored Digital Input" :            
            (rx->param_value.pwm1_config == DIO_DIGITAL_INPUT)       ? "Digital Input"             :
            (rx->param_value.pwm1_config == DIO_DIGITAL_OUTPUT_LO)   ? "Digital Output, Low"       :
            (rx->param_value.pwm1_config == DIO_DIGITAL_OUTPUT_HI)   ? "Digital Output, High"      :            
            "Unknown");
    }
    //P2
    else if(rx->at_command.first_letter  == 'P' && rx->at_command.second_letter == '2') {
        rx->atcmd = P2;
        rx->param_value.pwm2_config = *rx->command_data;
        sprintf(rx->frame_description3, "PWM2 Configuration: %s",
            (rx->param_value.pwm2_config == DIO_DIGITAL_INPUT_UNMOM) ? "Unmonitored Digital Input" :            
            (rx->param_value.pwm2_config == DIO_DIGITAL_INPUT)       ? "Digital Input"             :
            (rx->param_value.pwm2_config == DIO_DIGITAL_OUTPUT_LO)   ? "Digital Output, Low"       :
            (rx->param_value.pwm2_config == DIO_DIGITAL_OUTPUT_HI)   ? "Digital Output, High"      :            
            "Unknown");
    }
    //P3
    else if(rx->at_command.first_letter  == 'P' && rx->at_command.second_letter == '3') {
        rx->atcmd = P3;
        rx->param_value.pwm3_config = *rx->command_data;
        sprintf(rx->frame_description3, "PWM3 Configuration: %s",
            (rx->param_value.pwm3_config == DIO_DISABLED)            ? "Disabled"                  :            
            (rx->param_value.pwm3_config == DIO_DIGITAL_INPUT)       ? "Digital Input"             :
            (rx->param_value.pwm3_config == DIO_DIGITAL_OUTPUT_LO)   ? "Digital Output, Low"       :
            (rx->param_value.pwm3_config == DIO_DIGITAL_OUTPUT_HI)   ? "Digital Output, High"      :            
            "Unknown");
    }
    //D0
    else if(rx->at_command.first_letter  == 'D' && rx->at_command.second_letter == '0') {
        rx->atcmd = D0;
        rx->param_value.dio0_config = *rx->command_data;
        sprintf(rx->frame_description3, "DIO0 Configuration: %s",
            (rx->param_value.dio0_config == DIO0_COMMISH_BUTTON)   ? "Commissioning Button" :
            (rx->param_value.dio0_config == DIO_ANALOG_INPUT)      ? "Analog Input"         :
            (rx->param_value.dio0_config == DIO_DIGITAL_INPUT)     ? "Digital Input"        :
            (rx->param_value.dio0_config == DIO_DIGITAL_OUTPUT_LO) ? "Digital Output, Low"  :
            (rx->param_value.dio0_config == DIO_DIGITAL_OUTPUT_HI) ? "Digital Output, High" :            
            "Unknown");
    }
    //D1
    else if(rx->at_command.first_letter  == 'D' && rx->at_command.second_letter == '1') {
        rx->atcmd = D1;
        rx->param_value.dio1_config = *rx->command_data;
        sprintf(rx->frame_description3, "DIO1 Configuration: %s",
            (rx->param_value.dio1_config == DIO_DISABLED)          ? "Disabled"             :
            (rx->param_value.dio1_config == DIO_ANALOG_INPUT)      ? "Analog Input"         :
            (rx->param_value.dio1_config == DIO_DIGITAL_INPUT)     ? "Digital Input"        :
            (rx->param_value.dio1_config == DIO_DIGITAL_OUTPUT_LO) ? "Digital Output, Low"  :
            (rx->param_value.dio1_config == DIO_DIGITAL_OUTPUT_HI) ? "Digital Output, High" :            
            "Unknown");
    }
    //D2
    else if(rx->at_command.first_letter  == 'D' && rx->at_command.second_letter == '2') {
        rx->atcmd = D2;
        rx->param_value.dio2_config = *rx->command_data;
        sprintf(rx->frame_description3, "DIO2 Configuration: %s",
            (rx->param_value.dio2_config == DIO_DISABLED)          ? "Disabled"             :
            (rx->param_value.dio2_config == DIO_ANALOG_INPUT)      ? "Analog Input"         :
            (rx->param_value.dio2_config == DIO_DIGITAL_INPUT)     ? "Digital Input"        :
            (rx->param_value.dio2_config == DIO_DIGITAL_OUTPUT_LO) ? "Digital Output, Low"  :
            (rx->param_value.dio2_config == DIO_DIGITAL_OUTPUT_HI) ? "Digital Output, High" :            
            "Unknown");
    }
    //D3
    else if(rx->at_command.first_letter  == 'D' && rx->at_command.second_letter == '3') {
        rx->atcmd = D3;
        rx->param_value.dio3_config = *rx->command_data;
        sprintf(rx->frame_description3, "DIO3 Configuration: %s",
            (rx->param_value.dio3_config == DIO_DISABLED)          ? "Disabled"             :
            (rx->param_value.dio3_config == DIO_ANALOG_INPUT)      ? "Analog Input"         :
            (rx->param_value.dio3_config == DIO_DIGITAL_INPUT)     ? "Digital Input"        :
            (rx->param_value.dio3_config == DIO_DIGITAL_OUTPUT_LO) ? "Digital Output, Low"  :
            (rx->param_value.dio3_config == DIO_DIGITAL_OUTPUT_HI) ? "Digital Output, High" :            
            "Unknown");
    }
    //D4
    else if(rx->at_command.first_letter  == 'D' && rx->at_command.second_letter == '4') {
        rx->atcmd = D4;
        rx->param_value.dio4_config = *rx->command_data;
        sprintf(rx->frame_description3, "DIO4 Configuration: %s",
            (rx->param_value.dio4_config == DIO_DISABLED)          ? "Disabled"             :
            (rx->param_value.dio4_config == DIO_DIGITAL_INPUT)     ? "Digital Input"        :
            (rx->param_value.dio4_config == DIO_DIGITAL_OUTPUT_LO) ? "Digital Output, Low"  :
            (rx->param_value.dio4_config == DIO_DIGITAL_OUTPUT_HI) ? "Digital Output, High" :            
            "Unknown");
    }
    //D5
    else if(rx->at_command.first_letter  == 'D' && rx->at_command.second_letter == '5') {
        rx->atcmd = D5;
        rx->param_value.dio5_config = *rx->command_data;
        sprintf(rx->frame_description3, "DIO5 Configuration: %s",
            (rx->param_value.dio5_config == DIO_DISABLED)          ? "Disabled"             :
            (rx->param_value.dio5_config == DIO5_ASSOC_LED)        ? "Associated LED"       :
            (rx->param_value.dio5_config == DIO_DIGITAL_INPUT)     ? "Digital Input"        :
            (rx->param_value.dio5_config == DIO_DIGITAL_OUTPUT_LO) ? "Digital Output, Low"  :
            (rx->param_value.dio5_config == DIO_DIGITAL_OUTPUT_HI) ? "Digital Output, High" :            
            "Unknown");
    }
    //D8
    else if(rx->at_command.first_letter  == 'D' && rx->at_command.second_letter == '8') {
        rx->atcmd = D8;
        rx->param_value.dio8_config = *rx->command_data;
        sprintf(rx->frame_description3, "DIO8 Configuration: %s",
            (rx->param_value.dio8_config == DIO_DISABLED)          ? "Disabled"             :
            (rx->param_value.dio8_config == DIO_DIGITAL_INPUT)     ? "Digital Input"        :
            (rx->param_value.dio8_config == DIO_DIGITAL_OUTPUT_LO) ? "Digital Output, Low"  :
            (rx->param_value.dio8_config == DIO_DIGITAL_OUTPUT_HI) ? "Digital Output, High" :            
            "Unknown");
    }
    //LT
    else if(rx->at_command.first_letter  == 'L' && rx->at_command.second_letter == 'T') {
        rx->atcmd = LT;
        rx->param_value.led_blink_time = *rx->command_data;
        if(!rx->param_value.led_blink_time)
            sprintf(rx->frame_description3, "Associated LED Blink Time: 500 Milliseconds");
        else
            sprintf(rx->frame_description3, "Associated LED Blink Time: %x (%d Milliseconds)",
                rx->param_value.led_blink_time, rx->param_value.led_blink_time * 10);
    }
    //PR
    else if(rx->at_command.first_letter  == 'P' && rx->at_command.second_letter == 'R') {
        rx->atcmd = PR;
        rx->param_value.pull_up_resistor = bytes_to_uint16(rx->command_data);
        sprintf(rx->frame_description3, "Pull-up Resistor Bitmask: %x", rx->param_value.pull_up_resistor);
    }
    //RP
    else if(rx->at_command.first_letter  == 'R' && rx->at_command.second_letter == 'P') {
        rx->atcmd = RP;
        rx->param_value.rssi_pwm_timer = *rx->command_data;
        if(rx->param_value.rssi_pwm_timer == RSSI_ALWAYS_ON)
            sprintf(rx->frame_description3, "RSSI PWM Timer: Always On");
        else
            sprintf(rx->frame_description3, "RSSI PWM Timer: %x (%d Milliseconds)",
                rx->param_value.rssi_pwm_timer, rx->param_value.rssi_pwm_timer * 100);
    }
    //%V
    else if(rx->at_command.first_letter  == '%' && rx->at_command.second_letter == 'V') {
        rx->atcmd = VV;
        rx->param_value.supply_voltage = bytes_to_uint16(rx->command_data);
        sprintf(rx->frame_description3, "Internal Supply Voltage %x (%1.2f Volts DC)",
            rx->param_value.supply_voltage, (float)rx->param_value.supply_voltage * 1200 / 1024 / 1000);
    }
    //V+
    else if(rx->at_command.first_letter  == 'V' && rx->at_command.second_letter == '+') {
        rx->atcmd = VP;
        rx->param_value.volt_supply_monitor = bytes_to_uint16(rx->command_data);
        if(!rx->param_value.volt_supply_monitor)
             sprintf(rx->frame_description3, "Voltage Supply Monitor: Disabled");
        else
            sprintf(rx->frame_description3, "Voltage Supply Monitor: %x (%1.2f Volts DC)",
                rx->param_value.volt_supply_monitor, (float)rx->param_value.volt_supply_monitor * 1200 / 1024 / 1000);
    }
    //TP
    else if(rx->at_command.first_letter  == 'T' && rx->at_command.second_letter == 'P') {
        rx->atcmd = TP;
        rx->param_value.module_temperature = bytes_to_uint16(rx->command_data);
        sprintf(rx->frame_description3, "Module Temperature: %x", rx->param_value.module_temperature);
    }
    //VR
    else if(rx->at_command.first_letter  == 'V' && rx->at_command.second_letter == 'R') {
        rx->atcmd = VR;
        rx->param_value.firmware_version = bytes_to_uint16(rx->command_data);
        sprintf(rx->frame_description3, "Firmware Version: %x", rx->param_value.firmware_version);
    }
    //HV
    else if(rx->at_command.first_letter  == 'H' && rx->at_command.second_letter == 'V') {
        rx->atcmd = HV;
        rx->param_value.hardware_version = bytes_to_uint16(rx->command_data);
        sprintf(rx->frame_description3, "Hardware Version: %x", rx->param_value.hardware_version);
    }
    //AI
    else if(rx->at_command.first_letter  == 'A' && rx->at_command.second_letter == 'I') {
        rx->atcmd = AI;
        rx->param_value.assoc_indication = *rx->command_data;
        sprintf(rx->frame_description3, "Association Indication: %s",
            (rx->param_value.assoc_indication == JOINED_NTWRK)           ? "Successfully Formed Or Joined A Network"                      :
            (rx->param_value.assoc_indication == NO_PAN_FOUND)           ? "Scan Found No PANs"                                           :
            (rx->param_value.assoc_indication == NO_VALID_PAN_FOUND)     ? "Scan Found No Valid PANs Based On Current SC And ID Settings" :
            (rx->param_value.assoc_indication == JOIN_NOT_ALLOWED)       ? "Coordinators Or Routers Not Allowing Join"                    :
            (rx->param_value.assoc_indication == NO_JOINABLE_BEACONS)    ? "No Joinable Beacons Were Found"                               :
            (rx->param_value.assoc_indication == UNEXPECTED_STATE)       ? "Unexpected State, Node Should Not Attept Join At This Time"   :
            (rx->param_value.assoc_indication == JOIN_ATTEMPT_FAILED)    ? "Node Joining Attempt Failed"                                  :
            (rx->param_value.assoc_indication == COORD_START_FAILED)     ? "Coordinator Start Attempt Failed"                             :
            (rx->param_value.assoc_indication == EXISTING_COORD_CHECK)   ? "Checking For An Existing Coordinator"                         :
            (rx->param_value.assoc_indication == LEAVE_NETWORK_FAILED)   ? "Attempt To Leave The Network Failed"                          :
            (rx->param_value.assoc_indication == DEVICE_NO_RESPONSE)     ? "Attempted To Join A Device That Did Not Respond"              :
            (rx->param_value.assoc_indication == SEC_JOIN_ERR_UNSEC_KEY) ? "Secure Join Error-Network Security Key Received Unsecured"    :
            (rx->param_value.assoc_indication == SEC_JOIN_ERR_NO_KEY)    ? "Secure Join Error-Network Security Key Not Received"          :
            (rx->param_value.assoc_indication == SEC_JOIN_ERR_WRONG_KEY) ? "Secure Join Error-Incorrect Preconfigured Link Key"           :
            (rx->param_value.assoc_indication == SCANNING_FOR_NETWORK)   ? "Scanning For A Zigbee Network" :
            "Unknown");
    }

    /*The following are invalid commands in API mode.  Can only be used in AT mode.
    //CT
    else if(rx->at_command.first_letter  == 'C' && rx->at_command.second_letter == 'T') {
        rx->atcmd = CT;
        rx->param_value.cmd_mode_timeout = bytes_to_uint16(rx->command_data);
        sprintf(rx->frame_description3, "Command Mode Timeout: %x (%d Milliseconds)", rx->param_value.cmd_mode_timeout,
            rx->param_value.cmd_mode_timeout * 100);
    }
    //GT
    else if(rx->at_command.first_letter  == 'G' && rx->at_command.second_letter == 'T') {
        rx->atcmd = GT;
        rx->param_value.guard_times = bytes_to_uint16(rx->command_data);
        sprintf(rx->frame_description3, "Guard Times: %x (%d Milliseconds)", rx->param_value.guard_times,
            rx->param_value.guard_times);
    }
    //CC
    else if(rx->at_command.first_letter  == 'C' && rx->at_command.second_letter == 'C') {
        rx->atcmd = CC;
        rx->param_value.cmd_sequence_char = *rx->command_data;
        sprintf(rx->frame_description3, "Command Sequence Character %c", rx->param_value.cmd_sequence_char);
    }*/

    //SM
    else if(rx->at_command.first_letter  == 'S' && rx->at_command.second_letter == 'M') {
        rx->atcmd = SM;
        rx->param_value.sleep_mode = *rx->command_data;
        sprintf(rx->frame_description3, "Sleep Mode: %s",
            (rx->param_value.sleep_mode == SLEEP_DISABLED)        ? "Sleep Disabled"         :
            (rx->param_value.sleep_mode == PIN_SLEEP)             ? "Pin Sleep"              :
            (rx->param_value.sleep_mode == CYCLIC_SLEEP)          ? "Cyclic Sleep"           :
            (rx->param_value.sleep_mode == CYCLIC_SLEEP_PIN_WAKE) ? "Cyclic Sleep, Pin Wake" :
            "Unknown");
    }
    //SN
    else if(rx->at_command.first_letter  == 'S' && rx->at_command.second_letter == 'N') {
        rx->atcmd = SN;
        rx->param_value.num_of_sleep_periods = bytes_to_uint16(rx->command_data);
        sprintf(rx->frame_description3, "Number Of Sleep Periods: %x", rx->param_value.num_of_sleep_periods);
    }
    //SP
    else if(rx->at_command.first_letter  == 'S' && rx->at_command.second_letter == 'P') {
        rx->atcmd = SP;
        rx->param_value.sleep_period = bytes_to_uint16(rx->command_data);
        sprintf(rx->frame_description3, "Sleep Period: %x (%d Milliseconds)", rx->param_value.sleep_period,
            rx->param_value.sleep_period * 10);
    }
    //ST
    else if(rx->at_command.first_letter  == 'S' && rx->at_command.second_letter == 'T') {
        rx->atcmd = ST;
        rx->param_value.time_before_sleep = bytes_to_uint16(rx->command_data);
        sprintf(rx->frame_description3, "Time Before Sleep: %x (%d Milliseconds)", rx->param_value.time_before_sleep,
            rx->param_value.time_before_sleep);
    }
    //SO
    else if(rx->at_command.first_letter  == 'S' && rx->at_command.second_letter == 'O') {
        rx->atcmd = SO;
        rx->param_value.sleep_options = *rx->command_data;
        //Build sleep options string.
        strcpy(status_description1, "Sleep Options: ");
        if(rx->param_value.sleep_options & WAKE_FOR_ST_TIME)
            strcat(status_description1, "*Always Wake For ST Time* ");
        if(rx->param_value.sleep_options & SLEEP_ENTIRE_SN_SP_TIME)
            strcat(status_description1, "*Sleep Entire ST*SP Time* ");
        if(!rx->param_value.sleep_options)
            strcat(status_description1, "None");
        sprintf(rx->frame_description3, "%s", status_description1);
    }
    //WH
    else if(rx->at_command.first_letter  == 'W' && rx->at_command.second_letter == 'H') {
        rx->atcmd = WH;
        rx->param_value.wake_host = bytes_to_uint16(rx->command_data);
        sprintf(rx->frame_description3, "Wake Host Timer: %x (%d Milliseconds)", rx->param_value.wake_host,
            rx->param_value.wake_host);
    }
    //PO
    else if(rx->at_command.first_letter  == 'P' && rx->at_command.second_letter == 'O') {
        rx->atcmd = PO;
        rx->param_value.polling_rate = bytes_to_uint16(rx->command_data);
        if(!rx->param_value.polling_rate)
            sprintf(rx->frame_description3, "Polling Rate: 100 Milliseconds");
        else
            sprintf(rx->frame_description3, "Polling Rate: %x (%d Milliseconds)", rx->param_value.polling_rate,
                rx->param_value.polling_rate * 10);
    }
    //NR
    else if(rx->at_command.first_letter  == 'N' && rx->at_command.second_letter == 'R') {
        rx->atcmd = NR;
        rx->param_value.network_reset = *rx->command_data;
        sprintf(rx->frame_description3, "Network Reset: %s",
            (rx->param_value.network_reset == RESET_NODE)    ? "Node Reset"    :
            (rx->param_value.network_reset == RESET_NETWORK) ? "Network Reset" :
            "Unknown");
    }
    //CB
    else if(rx->at_command.first_letter  == 'C' && rx->at_command.second_letter == 'B') {
        rx->atcmd = CB;
        rx->param_value.commissioning_button = *rx->command_data;
        sprintf(rx->frame_description3, "Commissioning Button: %x", rx->param_value.commissioning_button);
    }
    //ND
    else if(rx->at_command.first_letter  == 'N' && rx->at_command.second_letter == 'D') {
        rx->atcmd = ND;
        rx->source_serial_hi = bytes_to_uint32(&rx->command_data[SH_INDEX]);
        rx->source_serial_lo = bytes_to_uint32(&rx->command_data[SL_INDEX]);
        rx->source_address   = bytes_to_uint16(&rx->command_data[MY_INDEX]);
        strcpy(rx->param_value.ni_value, &rx->command_data[NI_INDEX]);

        //Calculate remaining index values.
        par_net_index = strlen(rx->param_value.ni_value) + NI_INDEX + 1;
        device_type_index = par_net_index         + 2;
        status_index = device_type_index          + 1;
        profile_id_index = status_index           + 1;
        manufacturer_id_index = profile_id_index  + 2;
        dev_type_id_index = manufacturer_id_index + 2;

        //Get remaining data.
        rx->parent_address = bytes_to_uint16(&rx->command_data[par_net_index]);
        rx->device_type = rx->command_data[device_type_index];
        rx->status = rx->command_data[status_index];
        rx->profile_id = bytes_to_uint16(&rx->command_data[profile_id_index]);
        rx->manufacturer_id = bytes_to_uint16(&rx->command_data[manufacturer_id_index]);

        //Add device type to end of description, if present.
        if(rx->cmd_data_length > dev_type_id_index)
            rx->device_type_id = bytes_to_uint32(&rx->command_data[dev_type_id_index]);

        sprintf(rx->frame_description2, "%s %x%x, %s %x", "Source Serial Number:", rx->source_serial_hi,
                rx->source_serial_lo, "Source Network Address:", rx->source_address);
        sprintf(rx->frame_description3, "%s %s, %s %x, %s %s", "Node ID String:", rx->param_value.ni_value,
                "Parent Network Address:", rx->parent_address, "Device Type:", device_type(rx->device_type, status_description1));
        sprintf(rx->frame_description4, "%s %x, %s %x, %s %x", "Status:", rx->status,
                "Profile ID:", rx->profile_id, "Manufacturer ID:", rx->manufacturer_id);
        //Add device type ID, if present.
        if(rx->device_type_id) {
            sprintf(status_description1, ", %s %x", "Device Type ID:", rx->device_type_id);
            strcat(rx->frame_description4, status_description1);
        }
    }
    //DN
    else if(rx->at_command.first_letter  == 'D' && rx->at_command.second_letter == 'N') {
        rx->atcmd = DN;
        rx->source_serial_hi = bytes_to_uint32(&rx->command_data[SH_INDEX]);
        rx->source_serial_lo = bytes_to_uint32(&rx->command_data[SL_INDEX]);
        rx->source_address   = bytes_to_uint16(&rx->command_data[MY_INDEX]);
        sprintf(rx->frame_description2, "%s %x%x, %s %x", "Source Serial Number:", rx->source_serial_hi,
                rx->source_serial_lo, "Source Network Address:", rx->source_address);        
    }
    //IS
    else if(rx->at_command.first_letter  == 'I' && rx->at_command.second_letter == 'S') {
        rx->atcmd = IS;
        rx->number_of_samples = rx->command_data[IS_NUM_SAMPLES];                 //Number of samples (always 1).
        rx->digital_mask      = bytes_to_uint16(&rx->command_data[IS_DIG_MASK]);  //Digital sample mask.
        rx->analog_mask       = rx->command_data[IS_AN_MASK];                     //Analog sample mask.

        //Calculate remaining index values.
        if(rx->digital_mask)
            io_dig_sample_index = IS_AN_MASK + 1;
        else
            io_dig_sample_index = 0;
        if(rx->digital_mask)
            io_an_sample_index = io_dig_sample_index + 2;
        else
            io_an_sample_index = IS_AN_MASK + 1;

        //Extract digital samples (if any).
        if(io_dig_sample_index)
            rx->digital_samples = bytes_to_uint16(&rx->command_data[io_dig_sample_index]);
        //Extract analog samples.
        i = 0;
        if(rx->analog_mask & ADC_0) {
            rx->adc0 = bytes_to_uint16(&rx->command_data[io_an_sample_index + i]);
            i += 2;
        }
        if(rx->analog_mask & ADC_1) {
            rx->adc1 = bytes_to_uint16(&rx->command_data[io_an_sample_index + i]);
            i += 2;
        }
        if(rx->analog_mask & ADC_2) {
            rx->adc2 = bytes_to_uint16(&rx->command_data[io_an_sample_index + i]);
            i += 2;
        }
        if(rx->analog_mask & ADC_3) {
            rx->adc3 = bytes_to_uint16(&rx->command_data[io_an_sample_index + i]);
            i += 2;
        }  
        if(rx->analog_mask & ADC_VCC) {
            rx->adc_vcc = bytes_to_uint16(&rx->command_data[io_an_sample_index + i]);
            i += 2;
        }

        sprintf(rx->frame_description3, "%s %x, %s %x, %s %x, ", "Num Samples:", rx->number_of_samples,
            "D Mask:", rx->digital_mask, "A Mask:", rx->analog_mask);

        //Build digital samples string.
        status_description1[0] = 0; //clear string.
        if(rx->digital_mask & D_0) {
            sprintf(status_description2, "D0:%d ", (rx->digital_samples & D_0) ? 1 : 0);
            strcat(status_description1, status_description2);
        }
        if(rx->digital_mask & D_1) {
            sprintf(status_description2, "D1:%d ", (rx->digital_samples & D_1) ? 1 : 0);
            strcat(status_description1, status_description2);
        }
        if(rx->digital_mask & D_2) {
            sprintf(status_description2, "D2: %d ", (rx->digital_samples & D_2) ? 1 : 0);
            strcat(status_description1, status_description2);
        }
        if(rx->digital_mask & D_3) {
            sprintf(status_description2, "D3:%d ", (rx->digital_samples & D_3) ? 1 : 0);
            strcat(status_description1, status_description2);
        }
        if(rx->digital_mask & D_4) {
            sprintf(status_description2, "D4:%d ", (rx->digital_samples & D_4) ? 1 : 0);
            strcat(status_description1, status_description2);
        }
        if(rx->digital_mask & D_5) {
            sprintf(status_description2, "D5:%d ", (rx->digital_samples & D_5) ? 1 : 0);
            strcat(status_description1, status_description2);
        }
        if(rx->digital_mask & D_6) {
            sprintf(status_description2, "D6:%d ", (rx->digital_samples & D_6) ? 1 : 0);
            strcat(status_description1, status_description2);
        }
        if(rx->digital_mask & D_7) {
            sprintf(status_description2, "D7:%d ", (rx->digital_samples & D_7) ? 1 : 0);
            strcat(status_description1, status_description2);
        }
        if(rx->digital_mask & D_10) {
            sprintf(status_description2, "D10:%d ", (rx->digital_samples & D_10) ? 1 : 0);
            strcat(status_description1, status_description2);
        }
        if(rx->digital_mask & D_11) {
            sprintf(status_description2, "D11:%d ", (rx->digital_samples & D_11) ? 1 : 0);
            strcat(status_description1, status_description2);
        }
        if(rx->digital_mask & D_12) {
            sprintf(status_description2, "D12:%d ", (rx->digital_samples & D_12) ? 1 : 0);
            strcat(status_description1, status_description2);
        }
        sprintf(rx->frame_description4, "%s", status_description1);

        //Build analog samples string.
        status_description1[0] = 0; //clear string.
        if(rx->analog_mask & ADC_0) {
            sprintf(status_description2, "ADC0:%dmV ", rx->adc0 * 1200 / 1024);
            strcat(status_description1, status_description2);
        }
        if(rx->analog_mask & ADC_1) {
            sprintf(status_description2, "ADC1:%dmV ", rx->adc1 * 1200 / 1024);
            strcat(status_description1, status_description2);
        }
        if(rx->analog_mask & ADC_2) {
            sprintf(status_description2, "ADC2:%dmV ", rx->adc2 * 1200 / 1024);
            strcat(status_description1, status_description2);
        }
        if(rx->analog_mask & ADC_3) {
            sprintf(status_description2, "ADC3:%dmV ", rx->adc3 * 1200 / 1024);
            strcat(status_description1, status_description2);
        }
        if(rx->analog_mask & ADC_VCC) {
            sprintf(status_description2, "ADC_VCC:%dmV ", rx->adc_vcc * 1200 / 1024);
            strcat(status_description1, status_description2);
        }
        strcat(rx->frame_description3, status_description1);

    }
    //To be completed when a XBee sensor device is needed...
    else if(rx->at_command.first_letter  == '1' && rx->at_command.second_letter == 'S')
        rx->atcmd = S1;

    else
        rx->atcmd = 0; //Set to invalid array index.
        return -1;     //Invalid at command.
    return 0;
}
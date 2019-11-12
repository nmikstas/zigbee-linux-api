#include "zb_api.h"  

const struct at_cmd cmd_list[] = {
    {0, 0}, //Null value for index 0.
    //Addressing commands.
    {'D', 'H'}, {'D', 'L'}, {'M', 'Y'}, {'M', 'P'}, {'N', 'C'},
    {'S', 'H'}, {'S', 'L'}, {'N', 'I'}, {'S', 'E'}, {'D', 'E'},
    {'C', 'I'}, {'N', 'P'}, {'D', 'D'},
    //Networking commands.
    {'C', 'H'}, {'I', 'D'}, {'O', 'P'}, {'N', 'H'}, {'B', 'H'},
    {'O', 'I'}, {'N', 'T'}, {'N', 'O'}, {'S', 'C'}, {'S', 'D'},
    {'Z', 'S'}, {'N', 'J'}, {'J', 'V'}, {'N', 'W'}, {'J', 'N'},
    {'A', 'R'},
    //Security commands.
    {'E', 'E'}, {'E', 'O'}, {'N', 'K'}, {'K', 'Y'},
    //RF interfacing commands.
    {'P', 'L'}, {'P', 'M'}, {'D', 'B'}, {'P', 'P'},
    //Serial interfacing commands.
    {'A', 'P'}, {'A', 'O'}, {'B', 'D'}, {'N', 'B'}, {'S', 'B'},
    {'R', 'O'}, {'D', '7'}, {'D', '6'},
    //I/O commands.
    {'I', 'R'}, {'I', 'C'}, {'P', '0'}, {'P', '1'}, {'P', '2'},
    {'P', '3'}, {'D', '0'}, {'D', '1'}, {'D', '2'}, {'D', '3'},
    {'D', '4'}, {'D', '5'}, {'D', '8'}, {'L', 'T'}, {'P', 'R'},
    {'R', 'P'}, {'%', 'V'}, {'V', '+'}, {'T', 'P'},
    //Diagnostic commands.
    {'V', 'R'}, {'H', 'V'}, {'A', 'I'},
    //AT commands options commands.
    {'C', 'T'}, {'C', 'N'}, {'G', 'T'}, {'C', 'C'},
    //Sleep commands.
    {'S', 'M'}, {'S', 'N'}, {'S', 'P'}, {'S', 'T'}, {'S', 'O'},
    {'W', 'H'}, {'S', 'I'}, {'P', 'O'},
    //Execution commands.
    {'A', 'C'}, {'W', 'R'}, {'R', 'E'}, {'F', 'R'}, {'N', 'R'},
    {'C', 'B'}, {'N', 'D'}, {'D', 'N'}, {'I', 'S'}, {'1', 'S'}
};

//This function takes a 32 bit integer and breaks it down into 4 bytes.
//The 4 bytes are stored from highest to lowest in array pointers.
//Zero is returned upon success.
int uint32_to_bytes(uint32_t ser, uint8_t *s) {
    s[0] = ser >> 24;
    s[1] = ser >> 16;
    s[2] = ser >> 8;
    s[3] = ser;
    return 0;
}

//This function takes a 16 bit word and breaks it down into 2 bytes.
//The 2 bytes are stored from highest to lowest in array pointers.
//Zero is returned upon success.
int uint16_to_bytes(uint16_t ser, uint8_t *s) {
    s[0] = ser >> 8;
    s[1] = ser;
    return 0;
}

//This function takes a character array and converts it to a 32 bit
//unsigned integer.  The function returns the 32 bit integer.
uint32_t bytes_to_uint32(uint8_t *s) {
    uint32_t retval;
    retval = s[0];
    retval <<= 8;
    retval |= s[1];
    retval <<= 8;
    retval |= s[2];
    retval <<= 8;
    retval |= s[3];
    return retval;
}

//This function takes a character array and converts it to a 16 bit
//unsigned integer.  The function returns the 16 bit integer.
uint16_t bytes_to_uint16(uint8_t *s) {
    uint16_t retval;
    retval = s[0];
    retval <<= 8;
    retval |= s[1];
    return retval;
}

//This function calculates the checksum from array index CHECKSUM_START
//array index CHECKSUM_START + s->length.  The checksum is returned.
uint8_t get_checksum(struct zb_tx *tx) {
    uint8_t chk = 0xFF;
    int i;

    for(i = CHECKSUM_START; i < CHECKSUM_START + tx->checksum_length; i++)
        chk -= tx->tx_frame[i];

    return chk;
}

//This function dissects the raw rx frame and fills additional fields in the structure with data
//describing the frame contents.  This presents the data in a form more easily understandable by
//the user.  The function returns 0 upon success and -1 if invalid frame type found.
int fill_rx_structure(struct zb_rx *rx) {
    int i, parent_addr_index, dev_type_index, source_event_index, profile_index, manufacturer_index, dev_type_id_index;
    int io_dig_sample_index, io_an_sample_index;

    switch(rx->payload[0]) {
        case AT_COMMAND_RESPONSE_FRAME: //Local AT command response.            
            rx->frame_type = rx->payload[PAYLOAD_FRAME_TYPE];                //Frame type.
            rx->frame_id = rx->payload[PAYLOAD_FRAME_ID];                    //Frame ID.
            rx->at_command.first_letter  = rx->payload[PAYLOAD_COMMAND];     //Command first byte.
            rx->at_command.second_letter = rx->payload[PAYLOAD_COMMAND + 1]; //Command second byte.
            rx->command_status = rx->payload[PAYLOAD_STATUS];                //Status
            rx->cmd_data_length = rx->length - PAYLOAD_DATA_OFFSET;          //Get data length (may be 0).
            
            for(i = 0; i < rx->cmd_data_length; i++)                         //Extract command data from payload data.
                rx->command_data[i] = rx->payload[i + PAYLOAD_DATA_OFFSET];

            write_frame_description(rx);             //Convert frame information into human readable string.

            if(rx->length > PAYLOAD_DATA_OFFSET)   { //Contains command data.
                rx->contains_command_data = TRUE;
                write_command_description(rx);       //Convert command data into human readable string.
            }  
            else                                     //Does not contain command data.
                rx->contains_command_data = FALSE;
            break;

        case MODEM_STATUS_FRAME:
            rx->frame_type = rx->payload[MS_PAYLOAD_FRAME_TYPE]; //Frame type.
            rx->modem_status = rx->payload[MS_PAYLOAD_STATUS];   //Modem status.
            write_frame_description(rx); //Convert frame information into human readable string.
            break;

        case TRANSMIT_STATUS_FRAME:
            rx->frame_type = rx->payload[TS_PAYLOAD_FRAME_TYPE];                     //Frame type.
            rx->frame_id = rx->payload[TS_PAYLOAD_FRAME_ID];                         //Frame ID.
            rx->source_address = bytes_to_uint16(&rx->payload[TS_PAYLOAD_NET_ADDR]); //Destination network address.
            rx->retry_count = rx->payload[TS_PAYLOAD_RETRY_COUNT];                   //Retry count.
            rx->delivery_status = rx->payload[TS_PAYLOAD_DEL_STATUS];                //Delivery status.
            rx->discovery_status = rx->payload[TS_PAYLOAD_DISC_STATUS];              //Discovery status.
            write_frame_description(rx); //Convert frame information into human readable string.
            break;

        case RECEIVE_PACKET_FRAME:
            rx->frame_type = rx->payload[RP_PAYLOAD_FRAME_TYPE];                     //Frame type.
            rx->source_serial_hi = bytes_to_uint32(&rx->payload[RP_PAYLOAD_SER_HI]); //Source upper serial number.
            rx->source_serial_lo = bytes_to_uint32(&rx->payload[RP_PAYLOAD_SER_LO]); //Source lower serial number.
            rx->source_address = bytes_to_uint16(&rx->payload[RP_PAYLOAD_NET_ADDR]); //Source network address.
            rx->options = rx->payload[RP_PAYLOAD_OPTIONS];                           //Receive options.
            rx->received_data_length = rx->length - RP_PAYLOAD_DATA;                 //Get data length.

            for(i = 0; i < rx->received_data_length; i++) //Extract received data from payload data.
                rx->received_data[i] = rx->payload[i + RP_PAYLOAD_DATA];

            write_frame_description(rx); //Convert frame information into human readable string.
            break;

        case EXPLICIT_RX_INDICATOR_FRAME:
            rx->frame_type = rx->payload[EXP_PAYLOAD_FRAME_TYPE];                     //Frame type.
            rx->source_serial_hi = bytes_to_uint32(&rx->payload[EXP_PAYLOAD_SER_HI]); //Source upper serial number.
            rx->source_serial_lo = bytes_to_uint32(&rx->payload[EXP_PAYLOAD_SER_LO]); //Source lower serial number.
            rx->source_address = bytes_to_uint16(&rx->payload[EXP_PAYLOAD_NET_ADDR]); //Source network address.
            rx->source_endpoint = rx->payload[EXP_PAYLOAD_SRC_END];                   //Source endpoint.
            rx->destination_endpoint = rx->payload[EXP_PAYLOAD_DST_END];              //Destination endpoint.
            rx->cluster_id = bytes_to_uint16(&rx->payload[EXP_PAYLOAD_CLST_ID]);      //Cluster ID.
            rx->profile_id = bytes_to_uint16(&rx->payload[EXP_PAYLOAD_PROF_ID]);      //Profile ID.
            rx->options = rx->payload[EXP_PAYLOAD_OPTIONS];                           //Receive options.
            rx->received_data_length = rx->length - EXP_PAYLOAD_DATA;                 //Get data length.

            for(i = 0; i < rx->received_data_length; i++) //Extract received data from payload data.
                rx->received_data[i] = rx->payload[i + EXP_PAYLOAD_DATA];

            write_frame_description(rx); //Convert frame information into human readable string.            
            break;

        case IO_DATA_SAMPLE_RX_INDICATOR_FRAME:
            rx->frame_type = rx->payload[IO_PAYLOAD_FRAME_TYPE];                         //Frame type.
            rx->source_serial_hi = bytes_to_uint32(&rx->payload[IO_PAYLOAD_SRC_SER_HI]); //Source upper serial number.
            rx->source_serial_lo = bytes_to_uint32(&rx->payload[IO_PAYLOAD_SRC_SER_LO]); //Source lower serial number.
            rx->source_address = bytes_to_uint16(&rx->payload[IO_PAYLOAD_SRC_NET_ADR]);  //Source network address.
            rx->options = rx->payload[IO_PAYLOAD_OPTIONS];                               //Receive options.
            rx->number_of_samples = rx->payload[IO_PAYLOAD_NUM_SAMPLES];                 //Number of samples (always 1).
            rx->digital_mask = bytes_to_uint16(&rx->payload[IO_PAYLOAD_DIG_MASK]);       //Digital sample mask.
            rx->analog_mask = rx->payload[IO_PAYLOAD_AN_MASK];                           //Analog sample mask.

            //Calculate remaining index values.
            if(rx->digital_mask)
                io_dig_sample_index = IO_PAYLOAD_AN_MASK + 1;
            else
                io_dig_sample_index = 0;
            if(rx->digital_mask)
                io_an_sample_index = io_dig_sample_index + 2;
            else
                io_an_sample_index = IO_PAYLOAD_AN_MASK + 1;

            //Extract digital samples (if any).
            if(io_dig_sample_index)
                rx->digital_samples = bytes_to_uint16(&rx->payload[io_dig_sample_index]);
            //Extract analog samples.
            i = 0;
            if(rx->analog_mask & ADC_0) {
                rx->adc0 = bytes_to_uint16(&rx->payload[io_an_sample_index + i]);
                i += 2;
            }
            if(rx->analog_mask & ADC_1) {
                rx->adc1 = bytes_to_uint16(&rx->payload[io_an_sample_index + i]);
                i += 2;
            }
            if(rx->analog_mask & ADC_2) {
                rx->adc2 = bytes_to_uint16(&rx->payload[io_an_sample_index + i]);
                i += 2;
            }
            if(rx->analog_mask & ADC_3) {
                rx->adc3 = bytes_to_uint16(&rx->payload[io_an_sample_index + i]);
                i += 2;
            }  
            if(rx->analog_mask & ADC_VCC) {
                rx->adc_vcc = bytes_to_uint16(&rx->payload[io_an_sample_index + i]);
                i += 2;
            }

            write_frame_description(rx); //Convert frame information into human readable string.

            break;

        case SENSOR_READ_INDICATOR_FRAME: //To be completed when a 1-wire Digi sensor is needed...
            break;

        case NODE_ID_INDICATOR_FRAME:
            rx->frame_type = rx->payload[NID_PAYLOAD_FRAME_TYPE];                         //Frame type.
            rx->sender_serial_hi = bytes_to_uint32(&rx->payload[NID_PAYLOAD_SND_SER_HI]); //Sender upper serial number.
            rx->sender_serial_lo = bytes_to_uint32(&rx->payload[NID_PAYLOAD_SND_SER_LO]); //Sender lower serial number.
            rx->sender_address = bytes_to_uint16(&rx->payload[NID_PAYLOAD_SND_NET_ADR]);  //Sender network address.
            rx->options = rx->payload[NID_PAYLOAD_OPTIONS];                               //Receive options.
            rx->source_address = bytes_to_uint16(&rx->payload[NID_PAYLOAD_SRC_NET_ADR]);  //Source network address.
            rx->source_serial_hi = bytes_to_uint32(&rx->payload[NID_PAYLOAD_SRC_SER_HI]); //Source upper serial number.
            rx->source_serial_lo = bytes_to_uint32(&rx->payload[NID_PAYLOAD_SRC_SER_LO]); //Source lower serial number.
            strcpy(rx->param_value.ni_value, &rx->payload[NID_PAYLOAD_NID]);              //Source node ID string.
            
            //Calculate remaining index values.
            parent_addr_index = strlen(rx->param_value.ni_value) + NID_PAYLOAD_NID + 1;
            dev_type_index = parent_addr_index     + 2;
            source_event_index = dev_type_index    + 1;
            profile_index = source_event_index     + 1;
            manufacturer_index = profile_index     + 2;
            dev_type_id_index = manufacturer_index + 2;

            //Get remaining data.
            rx->parent_address = bytes_to_uint16(&rx->payload[parent_addr_index]);        //Parent network address.
            rx->device_type = rx->payload[dev_type_index];                                //Device type.
            rx->source_event = rx->payload[source_event_index];                           //Source event.
            rx->profile_id = bytes_to_uint16(&rx->payload[profile_index]);                //Profile ID.
            rx->manufacturer_id = bytes_to_uint16(&rx->payload[manufacturer_index]);      //Manufacturer ID.

            //Add device type to end of description, if present.
            if(rx->length > dev_type_id_index)
                rx->device_type_id = bytes_to_uint32(&rx->payload[dev_type_id_index]);            

            write_frame_description(rx); //Convert frame information into human readable string.
            break;

        case REMOTE_COMMAND_RESPONSE_FRAME:
            rx->frame_type = rx->payload[RMT_PAYLOAD_FRAME_TYPE];                     //Frame type.
            rx->frame_id = rx->payload[RMT_PAYLOAD_FRAME_ID];                         //Frame ID.
            rx->source_serial_hi = bytes_to_uint32(&rx->payload[RMT_PAYLOAD_SER_HI]); //Source upper serial number.
            rx->source_serial_lo = bytes_to_uint32(&rx->payload[RMT_PAYLOAD_SER_LO]); //Source lower serial number.
            rx->source_address = bytes_to_uint16(&rx->payload[RMT_PAYLOAD_NET_ADDR]); //Source network address.
            rx->at_command.first_letter  = rx->payload[RMT_PAYLOAD_COMMAND];          //Command first byte.
            rx->at_command.second_letter = rx->payload[RMT_PAYLOAD_COMMAND + 1];      //Command second byte.
            rx->command_status = rx->payload[RMT_PAYLOAD_STATUS];                     //Status
            rx->cmd_data_length = rx->length - RMT_PAYLOAD_DATA_OFFSET;               //Get data length (may be 0).

            for(i = 0; i < rx->cmd_data_length; i++)                                  //Extract command data from payload data.
                rx->command_data[i] = rx->payload[i + RMT_PAYLOAD_DATA_OFFSET];

            write_frame_description(rx);                                              //Convert frame information into human readable string.

            if(rx->length > RMT_PAYLOAD_DATA_OFFSET)   {                              //Contains command data.
                rx->contains_command_data = TRUE;
                write_command_description(rx);                                        //Convert command data into human readable string.
            }  
            else                                                                      //Does not contain command data.
                rx->contains_command_data = FALSE;
            break;

        case OTA_FIRMWARE_UPDATE_STATUS_FRAME: //To be completed when over the air firmware updates are required...
            break;

        case ROUTE_RECORD_INDICATOR_FRAME:
            rx->frame_type = rx->payload[RRI_PAYLOAD_FRAME_TYPE];                         //Frame type.            
            rx->source_serial_hi = bytes_to_uint32(&rx->payload[RRI_PAYLOAD_SRC_SER_HI]); //Source upper serial number.
            rx->source_serial_lo = bytes_to_uint32(&rx->payload[RRI_PAYLOAD_SRC_SER_LO]); //Source lower serial number.            
            rx->source_address = bytes_to_uint16(&rx->payload[RRI_PAYLOAD_SRC_NET_ADR]);  //Source network address.
            rx->options = rx->payload[RRI_PAYLOAD_OPTIONS];                               //Receive options.
            rx->num_addresses = rx->payload[RRI_PAYLOAD_NUM_ADR];                         //Number of addresses.

            for(i = 0; i < rx->num_addresses; i++)                                        //Get addresses.
                rx->addresses[i] = bytes_to_uint16(&rx->payload[RRI_PAYLOAD_ADR_LIST + (2 * i)]);

            write_frame_description(rx);                                        //Convert command data into human readable string.
            break;

        case MTO_ROUTE_REQUEST_INDICATOR_FRAME:
            rx->frame_type = rx->payload[MTO_PAYLOAD_FRAME_TYPE];                         //Frame type.
            rx->source_serial_hi = bytes_to_uint32(&rx->payload[MTO_PAYLOAD_SER_HI]); //Source upper serial number.
            rx->source_serial_lo = bytes_to_uint32(&rx->payload[MTO_PAYLOAD_SER_LO]); //Source lower serial number.            
            rx->source_address = bytes_to_uint16(&rx->payload[MTO_PAYLOAD_NET_ADDR]);  //Source network address.
            rx->reserved = rx->payload[MTO_PAYLOAD_RESERVED];                             //Reserved (always 0).

            write_frame_description(rx);                                        //Convert command data into human readable string.
            break;

        default: //Invalid frame type.
            return -1;
    }

    return 0;
}

//get_zb_data takes chunks of raw data ans assembles them into zigbee packets.
//The function can be called many times and retains the previous information
//passed to it and continues to assemble packets.  It is set up to take small
//pieces of rx data over multiple function calls and produce complete packets.
int get_zb_data(unsigned char *rx_packet, size_t rx_packet_length) {
    static enum rx_states rx_state = READY;
    static unsigned char data[BUFSZ];
    struct zb_rx rx;
    int packet_ready = 0;
    unsigned char checksum;
    static int state_count;
    static int data_index;
    static int rx_length;
    static int escape_found = FALSE;
    int i, this_index = 0;

    while(this_index < rx_packet_length) {
        //Move from READY state to LENGTH state.
        if(rx_state == READY && rx_packet[this_index] == FRAME_START) {
            rx_state = LENGTH;
            state_count = 2;
            rx_length = 0;
            this_index++;    
        }
            
        else if(rx_state == LENGTH) {
            if(state_count == 2) { //Get upper byte of packet length.
                if(rx_packet[this_index] == 0x7D) {
                    escape_found = TRUE;
                    this_index++;
                }
                else {
                    if(escape_found == TRUE) {
                        rx_length = rx_packet[this_index] ^ 0x20;
                        escape_found = FALSE;
                    }
                    else
                        rx_length = rx_packet[this_index];

                    rx_length << 8;    //Save into upper byte of word.
                    state_count--;
                    this_index++;
                }
            }
        else if(state_count == 1) { //Get lower byte of packet length.
                if(rx_packet[this_index] == 0x7D) {
                    escape_found = TRUE;
                    this_index++;
                }
                else {
                    if(escape_found == TRUE) {
                        rx_length |= rx_packet[this_index] ^ 0x20;
                        escape_found = FALSE;
                    }
                    else
                    rx_length |= rx_packet[this_index]; //Save into lower byte of word.

                state_count = rx_length;
                rx_state = DATABLOCK;
                    this_index++;
                }
        }               
    }

        //Get payload.          
    else if(rx_state == DATABLOCK) {
            if(rx_packet[this_index] == 0x7D) {
                    escape_found = TRUE;
                    this_index++;
            }
            else {
                if(escape_found == TRUE) {
                    data[data_index] = rx_packet[this_index] ^ 0x20;
                    escape_found = FALSE;
                }
                else
                data[data_index] = rx_packet[this_index];

            data_index++;
            state_count--;
                this_index++;
            if(!state_count)
                rx_state = PROCESS;
            }           
    }
            
    else if(rx_state == PROCESS) {
            if(rx_packet[this_index] == 0x7D) {
                    escape_found = TRUE;
                    this_index++;
            }
            else {
                if(escape_found == TRUE) {
                    checksum = rx_packet[this_index] ^ 0x20;
                    escape_found = FALSE;
                }
                else
                    checksum = rx_packet[this_index]; //Get checksum.

                //Fill struct zb_rx.
                rx.length = rx_length;
                rx.checksum = checksum;
                //Clear any old data.
                memset(rx.payload, 0, BUFSZ);
                for(i = 0; i < rx_length; i++)
                    rx.payload[i] = data[i];

                //Fill in details of struct zb_rx.
                fill_rx_structure(&rx);

                //Indicate packet ready for user.
                packet_ready = 1;

                put_rx_frame(&rx);

                //Clear variables for next packet.
                rx_state = READY;
                data_index = 0;
                state_count = 0;
                memset(&rx, 0, sizeof(rx)); //Zero out rx structure.
                for(i = 0; i < rx_length; i++)
                    data[i] = 0; //Reset data array.
            }           
    }           
            
    else { //Invalid state.
            rx_state = READY;
        data_index = 0;
        state_count = 0;
            this_index++;   
    }           
    }

    return packet_ready;
}

//This function sets the AT command parameters in a frame.  It  
//returns the number of bytes in the command parameters.
int set_at_command_param(struct zb_tx *tx) {
    uint8_t param_index;
    int num_bytes, i = 0;

    //Get index of AT command parameters in the frame.
    if(tx->frame_type == AT_COMMAND_FRAME || tx->frame_type == AT_COMMAND_QUEUE_FRAME)
        param_index = AT_COMMAND_PARAM_INDEX;
    else
        param_index = RMT_COMMAND_PARAM_INDEX;

    switch(tx->atcmd) {
        case DH:
            uint32_to_bytes(tx->param_value.serial_high, &tx->tx_frame[param_index]);
            num_bytes = 4;
            break;

        case DL:
            uint32_to_bytes(tx->param_value.serial_low, &tx->tx_frame[param_index]);
            num_bytes = 4;
            break;

        case NI:  //Copy node identifier into AT command frame parameter field.
            while(tx->param_value.node_identifier[i] > 0x1F && tx->param_value.node_identifier[i] < 0x7F && i < NID_LEN) {
                tx->tx_frame[param_index + i] = tx->param_value.node_identifier[i];
                i++;
            }
            tx->tx_frame[param_index + i] = 0x13; //Terminate string with a carriage return.
            num_bytes = i;
            break;

        case SE:
            tx->tx_frame[param_index] = tx->param_value.source_endpoint;
            num_bytes = 1;
            break;

        case DE:
            tx->tx_frame[param_index] = tx->param_value.dest_endpoint;
            num_bytes = 1;
            break;

        case CI:
            uint16_to_bytes(tx->param_value.cluster_identifier, &tx->tx_frame[param_index]);
            num_bytes = 2;
            break;

        case DD:
            uint32_to_bytes(tx->param_value.dev_type_identifier, &tx->tx_frame[param_index]);
            num_bytes = 4;
            break;

        case ID:
            uint32_to_bytes(tx->param_value.extended_pan_id[0], &tx->tx_frame[param_index]);
            uint32_to_bytes(tx->param_value.extended_pan_id[1], &tx->tx_frame[param_index + 4]);
            num_bytes = 8;
            break;

        case NH:
            tx->tx_frame[param_index] = tx->param_value.max_unicast_hops;
            num_bytes = 1;
            break;

        case BH:
            tx->tx_frame[param_index] = tx->param_value.max_broadcast_hops;
            num_bytes = 1;
            break;

        case NT:
            uint16_to_bytes(tx->param_value.Node_disc_timeout, &tx->tx_frame[param_index]);
            num_bytes = 2;
            break;

        case NO:
            tx->tx_frame[param_index] = tx->param_value.ntwk_disc_options;
            num_bytes = 1;
            break;

        case SC:
            uint16_to_bytes(tx->param_value.scan_channel_bitfield, &tx->tx_frame[param_index]);
            num_bytes = 2;
            break;

        case SD:
            tx->tx_frame[param_index] = tx->param_value.scan_duration;
            num_bytes = 1;
            break;

        case ZS:
            tx->tx_frame[param_index] = tx->param_value.zigbee_stack_profile;
            num_bytes = 1;
            break;

        case NJ:
            tx->tx_frame[param_index] = tx->param_value.node_join_time;
            num_bytes = 1;
            break;

        case JV:
            tx->tx_frame[param_index] = tx->param_value.channel_verification;
            num_bytes = 1;
            break;

        case NW:
            uint16_to_bytes(tx->param_value.ntwk_watchdog_timeout, &tx->tx_frame[param_index]);
            num_bytes = 2;
            break;

        case JN:
            tx->tx_frame[param_index] = tx->param_value.join_notification;
            num_bytes = 1;
            break;

        case AR:
            tx->tx_frame[param_index] = tx->param_value.aggr_rte_notification;
            num_bytes = 1;
            break;

        case EE:
            tx->tx_frame[param_index] = tx->param_value.encryption_enable;
            num_bytes = 1;
            break;

        case EO:
            tx->tx_frame[param_index] = tx->param_value.encryption_options;
            num_bytes = 1;
            break;

        case NK:
            uint32_to_bytes(tx->param_value.encryption_key[0], &tx->tx_frame[param_index]);
            uint32_to_bytes(tx->param_value.encryption_key[1], &tx->tx_frame[param_index + 4]);
            uint32_to_bytes(tx->param_value.encryption_key[2], &tx->tx_frame[param_index + 8]);
            uint32_to_bytes(tx->param_value.encryption_key[3], &tx->tx_frame[param_index + 12]);
            num_bytes = 16;
            break;

        case KY:
            uint32_to_bytes(tx->param_value.link_key[0], &tx->tx_frame[param_index]);
            uint32_to_bytes(tx->param_value.link_key[1], &tx->tx_frame[param_index + 4]);
            uint32_to_bytes(tx->param_value.link_key[2], &tx->tx_frame[param_index + 8]);
            uint32_to_bytes(tx->param_value.link_key[3], &tx->tx_frame[param_index + 12]);
            num_bytes = 16;
            break;

        case PL:
            tx->tx_frame[param_index] = tx->param_value.power_level;
            num_bytes = 1;
            break;

        case PM:
            tx->tx_frame[param_index] = tx->param_value.power_mode;
            num_bytes = 1;
            break;

        case DB:
            tx->tx_frame[param_index] = tx->param_value.rx_signal_strength;
            num_bytes = 1;
            break;

        case AP:
            tx->tx_frame[param_index] = tx->param_value.api_enable;
            num_bytes = 1;
            break;

        case AO:
            tx->tx_frame[param_index] = tx->param_value.api_options;
            num_bytes = 1;
            break;

        case BD:
            uint32_to_bytes(tx->param_value.data_rate, &tx->tx_frame[param_index]);
            num_bytes = 4;
            break;

        case NB:
            tx->tx_frame[param_index] = tx->param_value.serial_parity;
            num_bytes = 1;
            break;

        case SB:
            tx->tx_frame[param_index] = tx->param_value.stop_bits;
            num_bytes = 1;
            break;

        case RO:
            tx->tx_frame[param_index] = tx->param_value.packetization_timeout;
            num_bytes = 1;
            break;

        case D7:
            tx->tx_frame[param_index] = tx->param_value.dio7_config;
            num_bytes = 1;
            break;

        case D6:
            tx->tx_frame[param_index] = tx->param_value.dio6_config;
            num_bytes = 1;
            break;

        case IR:
            uint16_to_bytes(tx->param_value.io_sample_rate, &tx->tx_frame[param_index]);
            num_bytes = 2;
            break;

        case IC:
            uint16_to_bytes(tx->param_value.io_dig_change_detect, &tx->tx_frame[param_index]);
            num_bytes = 2;
            break;

        case P0:
            tx->tx_frame[param_index] = tx->param_value.pwm0_config;
            num_bytes = 1;
            break;

        case P1:
            tx->tx_frame[param_index] = tx->param_value.pwm1_config;
            num_bytes = 1;
            break;

        case P2:
            tx->tx_frame[param_index] = tx->param_value.pwm2_config;
            num_bytes = 1;
            break;

        case P3:
            tx->tx_frame[param_index] = tx->param_value.pwm3_config;
            num_bytes = 1;
            break;

        case D0:
            tx->tx_frame[param_index] = tx->param_value.dio0_config;
            num_bytes = 1;
            break;

        case D1:
            tx->tx_frame[param_index] = tx->param_value.dio1_config;
            num_bytes = 1;
            break;

        case D2:
            tx->tx_frame[param_index] = tx->param_value.dio2_config;
            num_bytes = 1;
            break;

        case D3:
            tx->tx_frame[param_index] = tx->param_value.dio3_config;
            num_bytes = 1;
            break;

        case D4:
            tx->tx_frame[param_index] = tx->param_value.dio4_config;
            num_bytes = 1;
            break;

        case D5:
            tx->tx_frame[param_index] = tx->param_value.dio5_config;
            num_bytes = 1;
            break;

        case D8:
            tx->tx_frame[param_index] = tx->param_value.dio8_config;
            num_bytes = 1;
            break;

        case LT:
            tx->tx_frame[param_index] = tx->param_value.led_blink_time;
            num_bytes = 1;
            break;

        case PR:
            uint16_to_bytes(tx->param_value.pull_up_resistor, &tx->tx_frame[param_index]);
            num_bytes = 2;
            break;

        case RP:
            tx->tx_frame[param_index] = tx->param_value.rssi_pwm_timer;
            num_bytes = 1;
            break;

        case VP:
            uint16_to_bytes(tx->param_value.volt_supply_monitor, &tx->tx_frame[param_index]);
            num_bytes = 2;
            break;

        case CT:
            uint16_to_bytes(tx->param_value.cmd_mode_timeout, &tx->tx_frame[param_index]);
            num_bytes = 2;
            break;

        case GT:
            uint16_to_bytes(tx->param_value.guard_times, &tx->tx_frame[param_index]);
            num_bytes = 2;
            break;

        case CC:
            tx->tx_frame[param_index] = tx->param_value.cmd_sequence_char;
            num_bytes = 1;
            break;

        case SM:
            tx->tx_frame[param_index] = tx->param_value.sleep_mode;
            num_bytes = 1;
            break;

        case SN:
            uint16_to_bytes(tx->param_value.num_of_sleep_periods, &tx->tx_frame[param_index]);
            num_bytes = 2;
            break;

        case SP:
            uint16_to_bytes(tx->param_value.sleep_period, &tx->tx_frame[param_index]);
            num_bytes = 2;
            break;

        case ST:
            uint16_to_bytes(tx->param_value.time_before_sleep, &tx->tx_frame[param_index]);
            num_bytes = 2;
            break;

        case SO:
            tx->tx_frame[param_index] = tx->param_value.sleep_options;
            num_bytes = 1;
            break;

        case WH:
            uint16_to_bytes(tx->param_value.wake_host, &tx->tx_frame[param_index]);
            num_bytes = 2;
            break;

        case PO:
            uint16_to_bytes(tx->param_value.polling_rate, &tx->tx_frame[param_index]);
            num_bytes = 2;
            break;

        case NR:
            tx->tx_frame[param_index] = tx->param_value.network_reset;
            num_bytes = 1;
            break;

        case CB:
            tx->tx_frame[param_index] = tx->param_value.commissioning_button;
            num_bytes = 1;
            break;

        case ND:  //Copy node identifier into AT command frame parameter field.
            while(tx->param_value.ni_value[i] > 0x1F && tx->param_value.ni_value[i] < 0x7F && i < NID_LEN) {
                tx->tx_frame[param_index + i] = tx->param_value.ni_value[i];
                i++;
            }
            tx->tx_frame[param_index + i] = 0x13; //Terminate string with a carriage return.
            num_bytes = i;
            break;

        case DN:  //Copy node identifier into AT command frame parameter field.
            while(tx->param_value.destination_node[i] > 0x1F && tx->param_value.destination_node[i] < 0x7F && i < NID_LEN) {
                tx->tx_frame[param_index + i] = tx->param_value.destination_node[i];
                i++;
            }
            tx->tx_frame[param_index + i] = 0x13; //Terminate string with a carriage return.
            num_bytes = i;
            break;

        default: //Invalid command.
            return -1;
    }
    return num_bytes;
}

//This function takes the zb_tx structure and makes a complete
//Zigbee frame and transmits it.  It calculates the frame length
//and checksum.  It takes a zb_tx structure pointer as an argument
//and a file descriptor for the Zigbee com port.  It returns 0
//on a successful transmit and -1 if an error occurred.
int zb_transmit(struct zb_tx *tx, int fd) {
    uint8_t temp[BUFSZ]; //Used while adding escape characters.
    uint16_t i;
    uint16_t j;

    switch(tx->frame_type) {
        case AT_COMMAND_FRAME:
        case AT_COMMAND_QUEUE_FRAME:            
            //Add AT command to frame.
            tx->tx_frame[AT_COMMAND_INDEX]     = cmd_list[tx->atcmd].first_letter;
            tx->tx_frame[AT_COMMAND_INDEX + 1] = cmd_list[tx->atcmd].second_letter;

            //Calculate total frame length in bytes.
            if(tx->at_cmd_read_write == READ) //Read AT values.
                tx->tx_frame_length = AT_COMMAND_OVERHEAD + 1;            
            else //Write AT values.
                tx->tx_frame_length = AT_COMMAND_OVERHEAD + 1 + set_at_command_param(tx);                                  
            break;

        case REMOTE_AT_COMMAND_FRAME:
            //Add upper serial bytes to frame.
            uint32_to_bytes(tx->serial_high, &tx->tx_frame[SERIAL_HIGH_INDEX]);           
            //Add lower serial bytes to frame.
            uint32_to_bytes(tx->serial_low , &tx->tx_frame[SERIAL_LOW_INDEX]);            
            //Add address to frame.
            uint16_to_bytes(tx->address, &tx->tx_frame[NETWORK_ADDR_INDEX]);
            //Add remote command options to frame.
            tx->tx_frame[RMT_COMMAND_OPTIONS_INDEX] = tx->options;
            //Add AT command to frame.
            tx->tx_frame[RMT_AT_COMMAND_INDEX]      = cmd_list[tx->atcmd].first_letter;
            tx->tx_frame[RMT_AT_COMMAND_INDEX + 1]  = cmd_list[tx->atcmd].second_letter;

            //Calculate total frame length in bytes.
            if(tx->at_cmd_read_write == READ) //Read AT values.
                tx->tx_frame_length = RMT_AT_COMMAND_OVERHEAD + 1;
            else //Write AT values.
                tx->tx_frame_length = RMT_AT_COMMAND_OVERHEAD + 1 + set_at_command_param(tx);
            break;

        case TRANSMIT_REQUEST_FRAME:
            //Calculate total frame length in bytes.
            tx->tx_frame_length = TX_REQUEST_OVERHEAD + strlen(tx->rf_data) + 1;             
            //Add upper serial bytes to frame.
            uint32_to_bytes(tx->serial_high, &tx->tx_frame[SERIAL_HIGH_INDEX]);           
            //Add lower serial bytes to frame.
            uint32_to_bytes(tx->serial_low , &tx->tx_frame[SERIAL_LOW_INDEX]);            
            //Add address to frame.
            uint16_to_bytes(tx->address, &tx->tx_frame[NETWORK_ADDR_INDEX]);            
            //Add broadcast radius to frame.
            tx->tx_frame[BROADCAST_RADIUS_INDEX] = tx->broadcast_radius;
            //Add options byte to frame.
            tx->tx_frame[OPTIONS_INDEX] = tx->options;
            //Add tx string to frame.
            strcpy(&tx->tx_frame[RF_DATA_INDEX], tx->rf_data);           
            break;

        case EXPLICIT_ADDRESSING_FRAME:
            //Calculate total frame length in bytes.
            tx->tx_frame_length = EXP_ADDRESSING_OVERHEAD + strlen(tx->rf_data) + 1;
            //Add upper serial bytes to frame.
            uint32_to_bytes(tx->serial_high, &tx->tx_frame[SERIAL_HIGH_INDEX]);           
            //Add lower serial bytes to frame.
            uint32_to_bytes(tx->serial_low , &tx->tx_frame[SERIAL_LOW_INDEX]);            
            //Add address to frame.
            uint16_to_bytes(tx->address, &tx->tx_frame[NETWORK_ADDR_INDEX]);
            //Add source endpoint to frame.
            tx->tx_frame[EXP_SOURCE_ENDPOINT_INDEX] = tx->src_endpoint;
            //Add destination endpoint to frame.
            tx->tx_frame[EXP_DEST_ENDPOINT_INDEX] = tx->dst_endpoint;
            //Add cluster ID to frame.
            uint16_to_bytes(tx->cluster_id, &tx->tx_frame[EXP_CLUSTER_ID_INDEX]);
            //Add proflie ID to frame.
            uint16_to_bytes(tx->profile_id, &tx->tx_frame[EXP_PROFILE_ID_INDEX]);
            //Add broadcast radius to frame.
            tx->tx_frame[EXP_BROADCAST_RADIUS_INDEX] = tx->broadcast_radius;
            //Add options byte to frame.
            tx->tx_frame[EXP_OPTIONS_INDEX] = tx->options;
            //Add tx string to frame.
            strcpy(&tx->tx_frame[EXP_RF_DATA_INDEX], tx->rf_data);
            break;

        case CREATE_SOURCE_ROUTE_FRAME:
            //Calculate total frame length in bytes.
            tx->tx_frame_length = CSR_OVERHEAD + (2 * tx->num_addresses) + 1;
            //Add upper serial bytes to frame.
            uint32_to_bytes(tx->serial_high, &tx->tx_frame[SERIAL_HIGH_INDEX]);           
            //Add lower serial bytes to frame.
            uint32_to_bytes(tx->serial_low , &tx->tx_frame[SERIAL_LOW_INDEX]);            
            //Add address to frame.
            uint16_to_bytes(tx->address, &tx->tx_frame[NETWORK_ADDR_INDEX]);
            //Add options byte to frame (always 0).
            tx->tx_frame[CSR_COMMAND_OPTIONS_INDEX] = 0;
            //Set the number of addresses in address array.
            tx->tx_frame[CSR_NUM_ADDRESSES_INDEX] = tx->num_addresses;

            //Load address hops into frame (closest node to target first).
            for(i = 0; i < tx->num_addresses; i++)
                uint16_to_bytes(tx->addresses[i], &tx->tx_frame[CSR_ADDRESS_PAYLOAD_INDEX + (2 * i)]);
         break;

        default: //Invalid frame type.
            return -1;
    }

    //Calculate number of payload bytes in frame.
    tx->checksum_length = tx->tx_frame_length - NON_CHECKSUM_BYTES;
    //Put tx->checksum_length into tx frame.
    uint16_to_bytes(tx->checksum_length, &tx->tx_frame[LENGTH_INDEX]);
    //Add frame start byte to frame.
    tx->tx_frame[START_DELIM_INDEX] = FRAME_START;
    //Add frame type to frame.
    tx->tx_frame[FRAME_TYPE_INDEX] = tx->frame_type;
    //Add frame id to frame.
    tx->tx_frame[FRAME_ID_INDEX] = tx->frame_id;
    //Calculate checksum.
    tx->checksum = get_checksum(tx);
    //Add checksum to frame.
    tx->tx_frame[tx->tx_frame_length - 1] = tx->checksum;

    //Add escape characters if enabled.
    if(esc_char == ESC_CHAR_ENABLED) {
        j = 0;

        for(i = 0; i < tx->tx_frame_length; i++) {
            if(i > 0 && tx->tx_frame[i] == 0x7E) {
                temp[j++] = 0x7D;                   //Add escape character.              
                temp[j++] = tx->tx_frame[i] ^ 0x20; //Add XORed character.                
            }
            else if(tx->tx_frame[i] == 0x7D) {
                temp[j++] = 0x7D;                   //Add escape character.               
                temp[j++] = tx->tx_frame[i] ^ 0x20; //Add XORed character.
            }
            else if(tx->tx_frame[i] == 0x11) {
                temp[j++] = 0x7D;                   //Add escape character.              
                temp[j++] = tx->tx_frame[i] ^ 0x20; //Add XORed character.
            }
            else if(tx->tx_frame[i] == 0x13) {
                temp[j++] = 0x7D;                   //Add escape character.               
                temp[j++] = tx->tx_frame[i] ^ 0x20; //Add XORed character.
            }
            else
                temp[j++] = tx->tx_frame[i];        //Simple element copy...no escape needed.
        }

        tx->tx_frame_length = j; //j is now the new frame length.

        for(i = 0; i < tx->tx_frame_length; i++) //Copy temp into tx struct.
            tx->tx_frame[i] = temp[i];
    }

    //Create human readable frame description (Not complete).
    tx_frame_description(tx);   

    //Transmit frame!    
    return write(fd, tx->tx_frame, tx->tx_frame_length);
}

int put_rx_frame(struct zb_rx *rx) {
    struct zb_queue_node *pzb_queue_node;

    //Dynamically allocate memory for new struct.
    pzb_queue_node = (struct zb_queue_node*)malloc(sizeof(struct zb_queue_node));

    if(!pzb_queue_node)
        return ZB_ERR_MALLOC_FAILED;

    if(!queue_start)//Initialize linked list pointers if first node.
        queue_start = queue_end = pzb_queue_node;
    else { //Update the end of the list.
        queue_end->next = pzb_queue_node;
        queue_end = pzb_queue_node;
    }

    queue_end->next = NULL;  

    //Copy contents of Zigbee rx struct into queue.
    memcpy(&queue_end->rx, rx, sizeof(struct zb_rx));

    return ZB_ERR_SUCCESS;
}

int get_rx_frame(struct zb_rx *rx) {

    //Check for empty queue.
    if(!queue_start)
        return ZB_ERR_QUEUE_EMPTY;

    memcpy(rx, &queue_start->rx, sizeof(struct zb_rx));

    free_queue_node();

    return ZB_ERR_SUCCESS;
}

int free_queue_node() {
    struct zb_queue_node *next;

    //Check for empty queue.
    if(!queue_start)
        return ZB_ERR_QUEUE_EMPTY;

    //Free node.
    if(queue_start != queue_end){
        next = queue_start->next;
        free(queue_start);
        queue_start = next;
    }
    else {        
        free(queue_start);
        queue_start = NULL;
        queue_end   = NULL;
    }
    
    return ZB_ERR_SUCCESS;
}
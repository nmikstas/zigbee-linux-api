#include "zb_interface.h"

//This function sets the parameter in a tx frame.
static int set_parameter(struct zb_tx *tx, union params *param) {
    int retval = ZB_SUCCESS;

    switch(tx->atcmd) {
        case DH: tx->param_value.serial_high = param->zb_dword; break;
        case DL: tx->param_value.serial_low = param->zb_dword; break;
        case NI: strcpy(tx->param_value.ni_value, param->zb_nid); break;
        case SE: tx->param_value.source_endpoint = param->zb_byte; break;
        case DE: tx->param_value.dest_endpoint = param->zb_byte; break;
        case CI: tx->param_value.cluster_identifier = param->zb_word; break;
        case DD: tx->param_value.dev_type_identifier = param->zb_dword; break;
        case ID:
            tx->param_value.extended_pan_id[0] = param->zb_dword_2[0];
            tx->param_value.extended_pan_id[1] = param->zb_dword_2[1];
            break;
        case NH: tx->param_value.max_unicast_hops = param->zb_byte; break;
        case BH: tx->param_value.max_broadcast_hops = param->zb_byte; break;
        case NT: tx->param_value.Node_disc_timeout = param->zb_word; break;
        case NO: tx->param_value.ntwk_disc_options = param->zb_byte; break;
        case SC: tx->param_value.scan_channel_bitfield = param->zb_word; break;
        case SD: tx->param_value.scan_duration = param->zb_byte; break;
        case ZS: tx->param_value.zigbee_stack_profile = param->zb_byte; break;
        case NJ: tx->param_value.node_join_time = param->zb_byte; break;
        case JV: tx->param_value.channel_verification = param->zb_byte; break;
        case NW: tx->param_value.ntwk_watchdog_timeout = param->zb_word; break;
        case JN: tx->param_value.join_notification = param->zb_byte; break;
        case AR: tx->param_value.aggr_rte_notification = param->zb_byte; break;
        case EE: tx->param_value.encryption_enable = param->zb_byte; break;
        case EO: tx->param_value.encryption_options = param->zb_byte; break;
        case NK:
            tx->param_value.encryption_key[0] = param->zb_dword_4[0];
            tx->param_value.encryption_key[1] = param->zb_dword_4[1];
            tx->param_value.encryption_key[2] = param->zb_dword_4[2];
            tx->param_value.encryption_key[3] = param->zb_dword_4[3];
            break;
        case KY:
            tx->param_value.link_key[0] = param->zb_dword_4[0];
            tx->param_value.link_key[1] = param->zb_dword_4[1];
            tx->param_value.link_key[2] = param->zb_dword_4[2];
            tx->param_value.link_key[3] = param->zb_dword_4[3];
            break;
        case PL: tx->param_value.power_level = param->zb_byte; break;
        case PM: tx->param_value.power_mode = param->zb_byte; break;
        case DB: tx->param_value.rx_signal_strength = param->zb_byte; break;
        case AP: tx->param_value.api_enable = param->zb_byte; break;
        case AO: tx->param_value.api_options = param->zb_byte; break;
        case BD: tx->param_value.data_rate = param->zb_dword; break;
        case NB: tx->param_value.serial_parity = param->zb_byte; break;
        case SB: tx->param_value.stop_bits = param->zb_byte; break;
        case RO: tx->param_value.packetization_timeout = param->zb_byte; break;
        case D7: tx->param_value.dio7_config = param->zb_byte; break;
        case D6: tx->param_value.dio6_config = param->zb_byte; break;
        case IR: tx->param_value.io_sample_rate = param->zb_word; break;
        case IC: tx->param_value.io_dig_change_detect = param->zb_word; break;
        case P0: tx->param_value.pwm0_config = param->zb_byte; break;
        case P1: tx->param_value.pwm1_config = param->zb_byte; break;
        case P2: tx->param_value.pwm2_config = param->zb_byte; break;
        case P3: tx->param_value.pwm3_config = param->zb_byte; break;
        case D0: tx->param_value.dio0_config = param->zb_byte; break;
        case D1: tx->param_value.dio1_config = param->zb_byte; break;
        case D2: tx->param_value.dio2_config = param->zb_byte; break;
        case D3: tx->param_value.dio3_config = param->zb_byte; break;
        case D4: tx->param_value.dio4_config = param->zb_byte; break;
        case D5: tx->param_value.dio5_config = param->zb_byte; break;
        case D8: tx->param_value.dio8_config = param->zb_byte; break;
        case LT: tx->param_value.led_blink_time = param->zb_byte; break;
        case PR: tx->param_value.pull_up_resistor = param->zb_word; break;
        case RP: tx->param_value.rssi_pwm_timer = param->zb_byte; break;
        case VP: tx->param_value.volt_supply_monitor = param->zb_word; break;
        case CT: tx->param_value.cmd_mode_timeout = param->zb_word; break;
        case GT: tx->param_value.guard_times = param->zb_word; break;
        case CC: tx->param_value.cmd_sequence_char = param->zb_byte; break;
        case SM: tx->param_value.sleep_mode = param->zb_byte; break;
        case SN: tx->param_value.num_of_sleep_periods = param->zb_word; break;
        case SP: tx->param_value.sleep_period = param->zb_word; break;
        case ST: tx->param_value.time_before_sleep = param->zb_word; break;
        case SO: tx->param_value.sleep_options = param->zb_byte; break;            
        case WH: tx->param_value.wake_host = param->zb_word; break;
        case PO: tx->param_value.polling_rate = param->zb_word; break;
        case NR: tx->param_value.network_reset = param->zb_byte; break;
        case CB: tx->param_value.commissioning_button = param->zb_byte; break;;
        case ND: strcpy(tx->param_value.ni_value, param->zb_nid); break;
        case DN: strcpy(tx->param_value.destination_node, param->zb_nid); break;
        default: retval = ZB_INVALID_PARAM; break;
    }

    return retval;
}

int send_at_command(uint8_t local_or_remote, uint8_t read_or_write, uint8_t frame_id,
struct serial_num *serial, uint8_t bcast_radius, uint8_t options, uint8_t at_command,
union params *param, int fd) {
    struct zb_tx tx;
    int retval = ZB_SUCCESS;

    memset(&tx, 0, sizeof(tx));

    //Setup frame type.
    if(local_or_remote == LOCAL)
        tx.frame_type = AT_COMMAND_FRAME;
    else if(local_or_remote == REMOTE)
        tx.frame_type = REMOTE_AT_COMMAND_FRAME;
    else
        return ZB_INVALID_PARAM;

    //Set read or write.
    if(read_or_write == READ)
        tx.at_cmd_read_write = READ;
    else if(read_or_write == WRITE)
        tx.at_cmd_read_write = WRITE;
    else
        return ZB_INVALID_PARAM;

    //Set frame id.
    tx.frame_id = frame_id;

    //Set destination serial number and address.
    if(serial) {
        tx.serial_high = serial->serial_hi;
        tx.serial_low  = serial->serial_lo;
        tx.address     = serial->address;
    }

    //Set broadcast radius.
    tx.broadcast_radius = bcast_radius;

    //Set options.
    tx.options = options;

    //Set AT command.
    tx.atcmd = at_command;

    //Set parameter if needed.
    if(read_or_write == WRITE && param)
        retval = set_parameter(&tx, param);

    //If there was an error, return before transmitting.
    if(retval != ZB_SUCCESS)
        return retval;

    //Transmit frame.
    zb_transmit(&tx, fd);

    return retval;
}

int read_local_at_command(uint8_t frame_id, uint8_t at_command, int fd) {
    return send_at_command(LOCAL, READ, frame_id, NULL, 0, 0, at_command, 0, fd);
}

int write_local_at_command(uint8_t frame_id, uint8_t at_command, union params *param, int fd) {
    return send_at_command(LOCAL, WRITE, frame_id, NULL, 0, 0, at_command, param, fd);
}

int read_remote_at_command(uint8_t frame_id, struct serial_num *serial, uint8_t options,
uint8_t at_command, int fd) {
    return send_at_command(REMOTE, READ, frame_id, serial, 0xFF, options, at_command, 0, fd);
}

int write_remote_at_command(uint8_t frame_id, struct serial_num *serial, uint8_t options,
uint8_t at_command, union params *param, int fd) {
    return send_at_command(REMOTE, WRITE, frame_id, serial, 0xFF, options, at_command, param, fd);
}

int discover_node_by_name(uint8_t frame_id, uint8_t *node_id, int fd) {
    union params param;    
    strcpy(param.zb_nid, node_id);
    return send_at_command(LOCAL, WRITE, frame_id, NULL, 0, 0, ND, &param, fd);
}

int at_command_queue(uint8_t frame_id, uint8_t at_command, union params *param, int fd) {
    struct zb_tx tx;
    int retval = ZB_SUCCESS;

    memset(&tx, 0, sizeof(tx));

    tx.frame_type = AT_COMMAND_QUEUE_FRAME;
    tx.frame_id = frame_id;
    tx.atcmd = at_command;
    
    //Set parameter, if necessary.
    if(param) {
        tx.at_cmd_read_write = WRITE;
        retval = set_parameter(&tx, param);
    }
    else
        tx.at_cmd_read_write = READ;

    //Exit if an error has occurred.
    if(retval != ZB_SUCCESS)
        return retval;

    //Transmit frame.
    zb_transmit(&tx, fd);

    return retval;
}

int tx_request(uint8_t frame_id, struct serial_num *serial, uint8_t bcast_radius,
uint8_t options, uint8_t *message, int fd) {
    struct zb_tx tx;
    int retval = ZB_SUCCESS;

    memset(&tx, 0, sizeof(tx));

    tx.frame_type = TRANSMIT_REQUEST_FRAME;
    tx.frame_id = frame_id;

    //Set destination serial number and address.
    if(serial) {
        tx.serial_high = serial->serial_hi;
        tx.serial_low  = serial->serial_lo;
        tx.address     = serial->address;
    }

    //Set broadcast radius.
    tx.broadcast_radius = bcast_radius;

    //Set options.
    tx.options = options;

    //Copy string to transmit into frame.
    strcpy(tx.rf_data, message);
    
    //Transmit frame.
    zb_transmit(&tx, fd);

    return retval;
}

int exp_address(uint8_t frame_id, struct serial_num *serial, uint8_t src_endpoint,
uint8_t dest_endpoint, uint16_t cluster_id, uint16_t profile_id, uint8_t bcast_radius,
uint8_t options, uint8_t *message, int fd) {
    struct zb_tx tx;
    int retval = ZB_SUCCESS;

    memset(&tx, 0, sizeof(tx));

    tx.frame_type = EXPLICIT_ADDRESSING_FRAME;
    tx.frame_id = frame_id;

    //Set destination serial number and address.
    if(serial) {
        tx.serial_high = serial->serial_hi;
        tx.serial_low  = serial->serial_lo;
        tx.address     = serial->address;
    }
 
    //Set endpoints.
    tx.src_endpoint = src_endpoint;
    tx.dst_endpoint = dest_endpoint;

    //Set IDs.
    tx.cluster_id = cluster_id;
    tx.profile_id = profile_id;

    //Set broadcast radius.
    tx.broadcast_radius = bcast_radius;

    //Set options.
    tx.options = options;

    //Copy string to transmit into frame.
    strcpy(tx.rf_data, message);
    
    //Transmit frame.
    zb_transmit(&tx, fd);

    return retval;
}

int create_route(uint8_t frame_id, struct serial_num *serial, uint8_t num_addresses,
uint16_t *addresses, int fd) {
    struct zb_tx tx;
    int retval = ZB_SUCCESS, i;

    memset(&tx, 0, sizeof(tx));

    tx.frame_type = CREATE_SOURCE_ROUTE_FRAME;
    tx.frame_id = frame_id;

    //Set destination serial number and address.
    if(serial) {
        tx.serial_high = serial->serial_hi;
        tx.serial_low  = serial->serial_lo;
        tx.address     = serial->address;
    }

    tx.num_addresses = num_addresses;

    //Get address list.
    for(i = 0; i < num_addresses; i++)
        tx.addresses[i] = addresses[i];

    return retval;
}

int get_zb_rx_frame(unsigned char *rx_packet, size_t rx_packet_length) {
    return get_zb_data(rx_packet, rx_packet_length);
}
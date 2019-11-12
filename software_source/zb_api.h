#ifndef ZB_API_H
#define ZB_API_H

#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <malloc.h>
#include "zb_rx_desc.h"
#include "zb_tx_desc.h"

//Checksum calculations always start after the first three frame bytes.
#define CHECKSUM_START     3
//First three bytes and last byte of frame are not part of checksum calculation.
#define NON_CHECKSUM_BYTES 4
//Max buf size for frame (plus some extra).
#define BUFSZ              512
#define HALF_BUFSZ         256
//All frames start with 0x7E.
#define FRAME_START        0x7E
//Node ID length max 20 characters and null termination.
#define NID_LEN 21

//Use with at_cmd_read_write.
#define READ               0
#define WRITE              1

#define FALSE              0
#define TRUE               1

#define ESC_CHAR_DISABLED  0
#define ESC_CHAR_ENABLED   1

//Zigbee frame types.
#define AT_COMMAND_FRAME                  0x08 //TX
#define AT_COMMAND_QUEUE_FRAME            0x09 //TX
#define TRANSMIT_REQUEST_FRAME            0x10 //TX
#define EXPLICIT_ADDRESSING_FRAME         0x11 //TX
#define REMOTE_AT_COMMAND_FRAME           0x17 //TX
#define CREATE_SOURCE_ROUTE_FRAME         0x21 //TX
#define AT_COMMAND_RESPONSE_FRAME         0x88 //RX
#define MODEM_STATUS_FRAME                0x8A //RX
#define TRANSMIT_STATUS_FRAME             0x8B //RX
#define RECEIVE_PACKET_FRAME              0x90 //RX
#define EXPLICIT_RX_INDICATOR_FRAME       0x91 //RX
#define IO_DATA_SAMPLE_RX_INDICATOR_FRAME 0x92 //RX
#define SENSOR_READ_INDICATOR_FRAME       0x94 //RX
#define NODE_ID_INDICATOR_FRAME           0x95 //RX
#define REMOTE_COMMAND_RESPONSE_FRAME     0x97 //RX
#define OTA_FIRMWARE_UPDATE_STATUS_FRAME  0xA0 //RX
#define ROUTE_RECORD_INDICATOR_FRAME      0xA1 //RX
#define MTO_ROUTE_REQUEST_INDICATOR_FRAME 0xA3 //RX

//Zigbee general tx frame indexes.
#define START_DELIM_INDEX          0x00
#define LENGTH_INDEX               0x01
#define FRAME_TYPE_INDEX           0x03
#define FRAME_ID_INDEX             0x04
#define SERIAL_HIGH_INDEX          0x05
#define SERIAL_LOW_INDEX           0x09
#define NETWORK_ADDR_INDEX         0x0D

//Zigbee specific tx frame indexes.
//AT command and AT command queue frames.
#define AT_COMMAND_INDEX           0x05
#define AT_COMMAND_PARAM_INDEX     0x07

//Zigbee transmit request frame.
#define BROADCAST_RADIUS_INDEX     0x0F
#define OPTIONS_INDEX              0x10
#define RF_DATA_INDEX              0x11

//Explicit addressing Zigbee command frame.
#define EXP_SOURCE_ENDPOINT_INDEX  0x0F
#define EXP_DEST_ENDPOINT_INDEX    0x10
#define EXP_CLUSTER_ID_INDEX       0x11
#define EXP_PROFILE_ID_INDEX       0x13
#define EXP_BROADCAST_RADIUS_INDEX 0x15
#define EXP_OPTIONS_INDEX          0x16
#define EXP_RF_DATA_INDEX          0x17

//Remote AT command request frame.
#define RMT_COMMAND_OPTIONS_INDEX  0x0F
#define RMT_AT_COMMAND_INDEX       0x10
#define RMT_COMMAND_PARAM_INDEX    0x12

//Create source route frame.
#define CSR_COMMAND_OPTIONS_INDEX  0x0F
#define CSR_NUM_ADDRESSES_INDEX    0x10
#define CSR_ADDRESS_PAYLOAD_INDEX  0x11

//The following overhead defines are used to find the first
//index of the variable size data in a frame.
#define AT_COMMAND_OVERHEAD        0x07
#define TX_REQUEST_OVERHEAD        0x11
#define EXP_ADDRESSING_OVERHEAD    0x17
#define RMT_AT_COMMAND_OVERHEAD    0x12
#define CSR_OVERHEAD               0x11

//Analog mask values.
#define ADC_0                      0x01
#define ADC_1                      0x02
#define ADC_2                      0x04
#define ADC_3                      0x08
#define ADC_VCC                    0x80

//Index values into local AT command response payload array.
#define PAYLOAD_FRAME_TYPE      0
#define PAYLOAD_FRAME_ID        1
#define PAYLOAD_COMMAND         2
#define PAYLOAD_STATUS          4
#define PAYLOAD_DATA_OFFSET     5

//Index values into modem status payload array.
#define MS_PAYLOAD_FRAME_TYPE   0
#define MS_PAYLOAD_STATUS       1

//Index values into transmit status payload array.
#define TS_PAYLOAD_FRAME_TYPE   0
#define TS_PAYLOAD_FRAME_ID     1
#define TS_PAYLOAD_NET_ADDR     2
#define TS_PAYLOAD_RETRY_COUNT  4
#define TS_PAYLOAD_DEL_STATUS   5
#define TS_PAYLOAD_DISC_STATUS  6

//Index values into receive frame payload array.
#define RP_PAYLOAD_FRAME_TYPE   0
#define RP_PAYLOAD_SER_HI       1
#define RP_PAYLOAD_SER_LO       5
#define RP_PAYLOAD_NET_ADDR     9
#define RP_PAYLOAD_OPTIONS      11
#define RP_PAYLOAD_DATA         12

//Index values into IO data sample RX indicator frame payload array.
#define IO_PAYLOAD_FRAME_TYPE   0
#define IO_PAYLOAD_SRC_SER_HI   1
#define IO_PAYLOAD_SRC_SER_LO   5
#define IO_PAYLOAD_SRC_NET_ADR  9
#define IO_PAYLOAD_OPTIONS      11
#define IO_PAYLOAD_NUM_SAMPLES  12
#define IO_PAYLOAD_DIG_MASK     13
#define IO_PAYLOAD_AN_MASK      15

//Index values into node ID indicator payload array.
#define NID_PAYLOAD_FRAME_TYPE  0
#define NID_PAYLOAD_SND_SER_HI  1
#define NID_PAYLOAD_SND_SER_LO  5
#define NID_PAYLOAD_SND_NET_ADR 9
#define NID_PAYLOAD_OPTIONS     11
#define NID_PAYLOAD_SRC_NET_ADR 12
#define NID_PAYLOAD_SRC_SER_HI  14
#define NID_PAYLOAD_SRC_SER_LO  18
#define NID_PAYLOAD_NID         22

//Index values into remote AT command response payload array.
#define RMT_PAYLOAD_FRAME_TYPE  0
#define RMT_PAYLOAD_FRAME_ID    1
#define RMT_PAYLOAD_SER_HI      2
#define RMT_PAYLOAD_SER_LO      6
#define RMT_PAYLOAD_NET_ADDR    10
#define RMT_PAYLOAD_COMMAND     12
#define RMT_PAYLOAD_STATUS      14
#define RMT_PAYLOAD_DATA_OFFSET 15

//Index values into route record indicator payload array.
#define RRI_PAYLOAD_FRAME_TYPE  0
#define RRI_PAYLOAD_SRC_SER_HI  1
#define RRI_PAYLOAD_SRC_SER_LO  5
#define RRI_PAYLOAD_SRC_NET_ADR 9
#define RRI_PAYLOAD_OPTIONS     11
#define RRI_PAYLOAD_NUM_ADR     12
#define RRI_PAYLOAD_ADR_LIST    13

//Index values into explicit RX indicator frame.
#define EXP_PAYLOAD_FRAME_TYPE  0
#define EXP_PAYLOAD_SER_HI      1
#define EXP_PAYLOAD_SER_LO      5
#define EXP_PAYLOAD_NET_ADDR    9
#define EXP_PAYLOAD_SRC_END     11
#define EXP_PAYLOAD_DST_END     12
#define EXP_PAYLOAD_CLST_ID     13
#define EXP_PAYLOAD_PROF_ID     15
#define EXP_PAYLOAD_OPTIONS     17
#define EXP_PAYLOAD_DATA        18

//Index values into many-to-one route request indicator frame.
#define MTO_PAYLOAD_FRAME_TYPE  0
#define MTO_PAYLOAD_SER_HI      1
#define MTO_PAYLOAD_SER_LO      5
#define MTO_PAYLOAD_NET_ADDR    9
#define MTO_PAYLOAD_RESERVED    11

#define ZB_ERR_SUCCESS        0
#define ZB_ERR_QUEUE_EMPTY   -10
#define ZB_ERR_MALLOC_FAILED -11

//Global variable used to enable and disable escape characters.
int esc_char;

struct at_cmd {
    uint8_t first_letter;
    uint8_t second_letter;
};

//Rx states.
enum rx_states {
    READY,
    LENGTH,
    DATABLOCK,
    PROCESS   
};

//Zigbee AT commands.
enum at_commands {
    //Addressing commands.
    DH = 1, DL, MY, MP, NC,
    SH, SL, NI, SE, DE,
    CI, NP, DD,
    //Networking commands.
    CH, ID, OP, NH, BH,
    OI, NT, NO, SC, SD,
    ZS, NJ, JV, NW, JN,
    AR,
    //Security commands.
    EE, EO, NK, KY,
    //RF interfacing commands.
    PL, PM, DB, PP,
    //Serial interfacing commands.
    AP, AO, BD, NB, SB,
    RO, D7, D6,
    //I/O commands.
    IR, IC, P0, P1, P2,
    P3, D0, D1, D2, D3,
    D4, D5, D8, LT, PR,
    RP, VV, VP, TP,
    //Diagnostic commands.
    VR, HV, AI,
    //AT command options commands.
    CT, CN, GT, CC,
    //Sleep commands.
    SM, SN, SP, ST, SO,
    WH, SI, PO,
    //Execution commands.
    AC, WR, RE, FR, NR,
    CB, ND, DN, IS, S1     
};

//Possible parameter read/write values for the various AT commands.
union at_cmd_param_value {
    //Addressing parameters.
    uint32_t serial_high;               //DH, SH
    uint32_t serial_low;                //DL, SL
    uint16_t network_address;           //MY
    uint16_t parent_address;            //MP
    uint16_t children_remaining;        //NC
    uint8_t  node_identifier[NID_LEN];  //NI
    uint8_t  source_endpoint;           //SE
    uint8_t  dest_endpoint;             //DE
    uint16_t cluster_identifier;        //CI
    uint16_t max_payload;               //NP
    uint32_t dev_type_identifier;       //DD

    //Networking parameters.
    uint8_t  operating_channel;         //CH
    uint32_t extended_pan_id[2];        //ID
    uint32_t op_extended_pan_id[2];     //OP
    uint8_t  max_unicast_hops;          //NH
    uint8_t  max_broadcast_hops;        //BH
    uint16_t pan_id;                    //OI
    uint16_t Node_disc_timeout;         //NT
    uint8_t  ntwk_disc_options;         //NO
    uint16_t scan_channel_bitfield;     //SC
    uint8_t  scan_duration;             //SD
    uint8_t  zigbee_stack_profile;      //ZS
    uint8_t  node_join_time;            //NJ
    uint8_t  channel_verification;      //JV
    uint16_t ntwk_watchdog_timeout;     //NW
    uint8_t  join_notification;         //JN
    uint8_t  aggr_rte_notification;     //AR

    //Security parameters.
    uint8_t  encryption_enable;         //EE
    uint8_t  encryption_options;        //EO
    uint32_t encryption_key[4];         //NK
    uint32_t link_key[4];               //KY

    //RF interfacing parameters.
    uint8_t  power_level;               //PL
    uint8_t  power_mode;                //PM
    uint8_t  rx_signal_strength;        //DB
    uint8_t  peak_power;                //PP

    //Serial interfacing parameters.
    uint8_t  api_enable;                //AP
    uint8_t  api_options;               //AO
    uint32_t data_rate;                 //BD
    uint8_t  serial_parity;             //NB
    uint8_t  stop_bits;                 //SB
    uint8_t  packetization_timeout;     //RO
    uint8_t  dio7_config;               //D7
    uint8_t  dio6_config;               //D6

    //I/O parameters.
    uint16_t io_sample_rate;            //IR
    uint16_t io_dig_change_detect;      //IC
    uint8_t  pwm0_config;               //P0
    uint8_t  pwm1_config;               //P1
    uint8_t  pwm2_config;               //P2
    uint8_t  pwm3_config;               //P3
    uint8_t  dio0_config;               //D0
    uint8_t  dio1_config;               //D1
    uint8_t  dio2_config;               //D2
    uint8_t  dio3_config;               //D3
    uint8_t  dio4_config;               //D4
    uint8_t  dio5_config;               //D5
    uint8_t  dio8_config;               //D8
    uint8_t  led_blink_time;            //LT
    uint16_t pull_up_resistor;          //PR
    uint8_t  rssi_pwm_timer;            //RP
    uint16_t supply_voltage;            //%V
    uint16_t volt_supply_monitor;       //V+
    uint16_t module_temperature;        //TP
    uint16_t firmware_version;          //VR
    uint16_t hardware_version;          //HV
    uint8_t  assoc_indication;          //AI

    //AT command parameters.
    uint16_t cmd_mode_timeout;          //CT
    uint16_t guard_times;               //GT
    uint8_t  cmd_sequence_char;         //CC

    //Sleep parameters.
    uint8_t  sleep_mode;                //SM
    uint16_t num_of_sleep_periods;      //SN
    uint16_t sleep_period;              //SP
    uint16_t time_before_sleep;         //ST
    uint8_t  sleep_options;             //SO
    uint16_t wake_host;                 //WH
    uint16_t polling_rate;              //PO

    //Execution parameters.
    uint8_t  network_reset;             //NR
    uint8_t  commissioning_button;      //CB
    uint8_t  ni_value[NID_LEN];         //ND
    uint8_t  destination_node[NID_LEN]; //DN
};

struct zb_tx {
    uint8_t  frame_type;
    uint8_t  frame_id;
    uint32_t serial_high;
    uint32_t serial_low;
    uint16_t address;
    uint8_t  src_endpoint;
    uint8_t  dst_endpoint;
    uint16_t cluster_id;
    uint16_t profile_id;
    uint8_t  broadcast_radius;
    uint8_t  options;
    uint8_t  rf_data[HALF_BUFSZ];
    uint16_t checksum_length;
    uint8_t  checksum;

    //Number of addresses in create source route frame.
    uint8_t  num_addresses;  

    //Array conatining addresses for create source route frame.
    uint16_t addresses[10];     

    //A union for the various parameter values of an AT command write.
    union at_cmd_param_value param_value;

    //Determine if AT command packet is READ or WRITE.
    uint8_t  at_cmd_read_write;
    //AT command code for use in AT command frames.
    enum at_commands atcmd;
    //Total frame length including 0x7E length bytes and checksum.
    uint16_t tx_frame_length;
    //Assembled frame.
    uint8_t  tx_frame[BUFSZ];

    //Human readable frame descriptions.
    char frame_description1[HALF_BUFSZ]; //multiple variables used to allow
    char frame_description2[HALF_BUFSZ]; //the user to add newlines if desired.
    char frame_description3[HALF_BUFSZ]; //The descriptions can be lengthy.
    char frame_description4[BUFSZ * 2];
};

struct zb_rx {
    uint16_t length;                          //Payload array length in bytes.
    uint8_t  frame_type;
    uint8_t  frame_id;

    uint32_t source_serial_hi;                //Upper half of 64 bit source address.
    uint32_t source_serial_lo;                //Lower half of 64 bit source address.
    uint16_t source_address;                  //16 bit source network address.

    uint8_t  payload[BUFSZ];
    uint8_t  checksum;

    struct   at_cmd at_command;               //Contains 2 payload bytes for command name.
    enum     at_commands atcmd;               //AT command code for use in AT command frames.
    union    at_cmd_param_value param_value;
    uint8_t  contains_command_data;           //TRUE or FALSE.
    uint8_t  cmd_data_length;                 //Length of data in command_data array.
    uint8_t  command_data[HALF_BUFSZ];        //Command data minus other payload data.

    //Status variables.
    uint8_t  command_status;                  //OK, ERROR, invalid command, etc.
    uint8_t  modem_status;                    //Hardware reset, joined network, etc.
    uint8_t  delivery_status;
    uint8_t  discovery_status;
    uint8_t  status;    

    uint8_t  retry_count;                     //Number of times a tx was retransmitted.

    //Explicit indicator data.
    uint8_t  source_endpoint;
    uint8_t  destination_endpoint;
    uint16_t cluster_id;
    uint16_t profile_id;                      //Also used in node ID indicator frame.

    //Node ID indicator data.
    uint32_t sender_serial_hi;
    uint32_t sender_serial_lo;
    uint16_t sender_address;
    uint16_t parent_address;
    uint8_t  device_type;
    uint8_t  source_event;
    uint16_t manufacturer_id;
    uint32_t device_type_id;

    uint8_t  options;                         //Receive data options.

    uint8_t  number_of_samples;               //Number of IO sample sets (always 1).
    uint8_t  reserved;                        //Reserved by Zigbee device(always 0).

    //Route record data.
    uint8_t  num_addresses;
    uint16_t addresses[10];

    //I/O sampled data masks.
    uint16_t digital_mask;                    //16-bit digital mask: N/A   N/A   N/A   DIO12 DIO11 DIO10 N/A   N/A  (Upper byte)
    uint8_t  analog_mask;                     //                     DIO7  DIO6  DIO5  DIO4  DIO3  DIO2  DIO1  DIO0 (Lower byte)
    //Digital samples.
    uint16_t digital_samples;                 //8-bit  analog  mask: VCC   N/A   N/A   N/A   ADC3  ADC2  ADC1  ADC0
    //Analog samples.
    uint16_t adc0;
    uint16_t adc1;
    uint16_t adc2;
    uint16_t adc3;
    uint16_t adc_vcc;

    //RF data storage.
    uint8_t  received_data_length;           //Length in bytes of received data.
    uint8_t  received_data[HALF_BUFSZ];      //Received data

    //Human readable frame descriptions.
    char frame_description1[HALF_BUFSZ];     //multiple variables used to allow
    char frame_description2[HALF_BUFSZ];     //the user to add newlines if desired.
    char frame_description3[HALF_BUFSZ];     //The descriptions can be lengthy.
    char frame_description4[BUFSZ * 2];
};

//Queue structure used for creating linked list
//of Zigbee rx frames.
struct zb_queue_node {
    struct zb_rx rx;
    struct zb_queue_node *next;
};

//Pointers to beginning and end of zb_queue_node linked list.
struct zb_queue_node *queue_start, *queue_end;

//This function puts a Zigbee rx frame into the queue. It takes
//a pointer to the zb_rx structure to copy into the queue as an
//argument and returns a status integer.
int put_rx_frame(struct zb_rx *rx);

//This function gets an rx frame from the Zigbee queue. It takes
//a ponter to a rx structure to copy to as an argument and returns
//a status indicator.
int get_rx_frame(struct zb_rx *rx);

//This function frees the head element in the Zigbee rx queue. It
//returns a status indicator.
int free_queue_node();

int get_zb_data(unsigned char *rx_packet, size_t rx_packet_length);
int uint32_to_bytes(uint32_t ser, uint8_t *s);
int uint16_to_bytes(uint16_t ser, uint8_t *s);
uint32_t bytes_to_uint32(uint8_t *s);
uint16_t bytes_to_uint16(uint8_t *s);
unsigned char get_checksum(struct zb_tx *tx);
int zb_transmit(struct zb_tx *tx, int fd);

#endif
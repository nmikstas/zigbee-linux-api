#ifndef ZB_INTERFACE_H
#define ZB_INTERFACE_H

#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include "zb_api.h"

//zb_interface files contain the user friendly function calls that
//interact with the Zigbee API.

//The following defines are used by the user when sending AT commands
//to send them to a remote node or the local node.
#define LOCAL             0
#define REMOTE            1

//Define for broadcast transmissions.
#define BROADCAST         (serial_num *) 0xFFFFFFFF

//Various options used in transmission frames.
#define DISABLE_ACK       0x01
#define APPLY_CHANGES     0x02
#define ENABLE_ENC        0x20
#define EXTENDED_TX       0x40

//Error macros.
#define ZB_SUCCESS        0
#define ZB_INVALID_PARAM -1

//The following structure is used for storing Zigbee serial numbers.
struct serial_num {
    uint32_t serial_hi;
    uint32_t serial_lo;
    uint16_t address;
};

//The params union contains data used by the various AT commands.
//It is a simplified version of union at_cmd_param_value.
union params {
    uint8_t  zb_byte;
    uint16_t zb_word;
    uint32_t zb_dword;
    uint32_t zb_dword_2[2];   //Used for 64-bit PAN IDs.
    uint32_t zb_dword_4[4];   //Used for 128-bit encryption keys.
    uint8_t  zb_nid[NID_LEN]; //used for node identifier strings.
};

//The following function is used to send an AT command to a Zigbee module.
//Macros for local_or_remote can be either LOCAL or REMOTE.
//Macros for read_or_write can be either READ or WRITE.
//Macros for serial can be COORDINATOR for frames to be sent to the coordinator
//or BROADCAST for frames to be broadcast across the entire network.
//The macros for options are DISABLE_ACK, APPLY_CHANGES and EXTENDED_TX.
//The macros for at_command are the same as the commands described in the
//Zigbee manual except for %V, V+ and 1S.  The macros for these commands are as follows:
//%V = VV, V+ = VP, 1S = S1.
//If local_or_remote is LOCAL, only the arguments read_or_write, frame_id and
//at_command are required.  The other arguments are ignored.
//If read_or_write is READ, the param argument is ignored.
int send_at_command(uint8_t local_or_remote, uint8_t read_or_write, uint8_t frame_id,
                   struct serial_num *serial, uint8_t bcast_radius, uint8_t options,
                   uint8_t at_command, union params *param, int fd);

//The following is an easy to use function for reading a local AT command parameter.
//It calls the at_command function with pre-filled arguments.
int read_local_at_command(uint8_t frame_id, uint8_t at_command, int fd);

//The following is an easy to use function for writing a local AT command parameter.
//It calls the at_command function with pre-filled arguments.
int write_local_at_command(uint8_t frame_id, uint8_t at_command, union params *param, int fd);

//The following is an easy to use function for reading a remote AT command parameter.
//It calls the at_command function with pre-filled arguments.
int read_remote_at_command(uint8_t frame_id, struct serial_num *serial, uint8_t options,
                           uint8_t at_command, int fd);

//The following is an easy to use function for writing a remote AT command parameter.
//It calls the at_command function with pre-filled arguments.
int write_remote_at_command(uint8_t frame_id, struct serial_num *serial, uint8_t options,
                            uint8_t at_command, union params *param, int fd);

//The following function is an easy to use function that allows a user to find
//a node on a network by using the node's identifier.
int discover_node_by_name(uint8_t frame_id, uint8_t *node_id, int fd);

//The following function is used to send an AT command to a Zigbee module and
//put it in a queue if it is to be set.  The API command AC (apply changes)
//must be called in order for the parameters to take effect.
//The macros for at_command are the same as the commands described in the
//Zigbee manual except for %V, V+ and 1S.  The macros for these commands are as follows:
//%V = VV, V+ = VP, 1S = S1.
int at_command_queue(uint8_t frame_id, uint8_t at_command, union params *param, int fd);

//The following function creates a transmit request frame.
//Macros for serial can be COORDINATOR for frames to be sent to the coordinator
//or BROADCAST for frames to be broadcast across the entire network.
//Macros for options can be DISABLE_ACK, ENABLE_ENC or EXTENDED_TX.
int tx_request(uint8_t frame_id, struct serial_num *serial, uint8_t bcast_radius,
               uint8_t options, uint8_t *message, int fd);

//The following function creates an explicit addressing frame.  The function is similar
//to the tx_request function except it takes 4 additional parameters.
int exp_address(uint8_t frame_id, struct serial_num *serial, uint8_t src_endpoint,
                uint8_t dest_endpoint, uint16_t cluster_id, uint16_t profile_id,
                uint8_t bcast_radius, uint8_t options, uint8_t *message, int fd);

//The following function creates a source route frame in the Zigbee module.
int create_route(uint8_t frame_id, struct serial_num *serial, uint8_t num_addresses,
                 uint16_t *addresses, int fd);

//The following function call gets any available rx Zigbee frames.
int get_zb_frame(unsigned char *rx_packet, size_t rx_packet_length, struct zb_rx *rx);

#endif
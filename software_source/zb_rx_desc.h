#ifndef ZB_RX_DESC_H
#define ZB_RX_DESC_H

#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include "zb_api.h"

//Forward declaration for Zigbee receive structure.
struct zb_rx;

//Command status.
#define OK                      0
#define ERROR                   1
#define INVALID_COMMAND         2
#define INVALID_PARAMETER       3
#define TX_FAILURE              4

//Modem status.
#define HARDWARE_RESET          0
#define WATCHDOG_TIMER_RESET    1
#define JOINED_NETWORK          2
#define DISASSOCIATED           3
#define COORDINATOR_STARTED     6
#define SECURITY_KEY_UPDATED    7
#define HIGH_VOLTAGE            0x0D
#define MODEM_RECONFIGURED      0x11

//Delivery status
#define SUCCESS                 0x00
#define MAC_ACK_FAILURE         0x01
#define CCA_FAILURE             0x02
#define INVALID_DEST_ENDPOINT   0x15
#define NETWORK_ACK_FAILURE     0x21
#define NOT_JOINED              0x22
#define SELF_ADDRESSED          0x23
#define ADDRESS_NOT_FOUND       0x24
#define ROUTE_NOT_FOUND         0x25
#define BCAST_SOURCE_FAILED     0x26
#define INVALID_BINDING_TBL_IND 0x2B
#define RESOURCE_ERROR1         0x2C
#define APS_BCAST_FAILED        0x2D
#define APS_UNICAST_FAILED      0x2E
#define RESOURCE_ERROR2         0x32
#define PAYLOAD_TOO_LARGE       0x74
#define INDIRECT_MESSAGE_RQ     0x75

//Discovery status
#define NO_DISCOVERY_OVERHEAD   0x00
#define ADDRESS_DISCOVERY       0x01
#define ROUTE_DISCOVERY         0x02
#define ADDRESS_AND_ROUTE       0x03
#define EXTENDED_TIMEOUT        0x04

//Discovery options
#define NO_DISCOVERY_OPTIONS    0x00
#define APPEND_DD_VALUE         0x01
#define LOCAL_ND                0x02
#define BOTH_DISC_OPTIONS       0x03

//Channel verification
#define CH_VERIFY_DISABLED      0x00
#define CH_VERIFY_ENABLED       0x01

//Encryption options
#define NO_ENC_OPTIONS          0x00
#define SEND_SECURITY_KEY       0x01
#define USE_TRUST_CENTER        0x02
#define BOTH_ENC_OPTIONS        0x03

//Receive options
#define PACKET_ACK              0x01
#define BCAST_PACKET            0x02
#define APS_ENCRYPTION          0x20
#define END_DEVICE_PACKET       0x40

//Device types
#define COORDINATOR             0x00
#define ROUTER                  0x01
#define END_DEVICE              0x02

//Source events
#define PUSHBUTTON              0x01
#define JOIN                    0x02
#define POWER_CYCLE             0x03

//API options
#define DEFAULT_API_OPTIONS     0x00
#define EXP_RX_INICATOR_FRAME   0x01
#define ZDO_PASSTHROUGH         0x02

//Baud rates
#define BAUD_1200               0x00
#define BAUD_2400               0x01
#define BAUD_4800               0x02
#define BAUD_9600               0x03
#define BAUD_19200              0x04
#define BAUD_38400              0x05
#define BAUD_57600              0x06
#define BAUD_115200             0x07

//Parity values
#define NO_PARITY               0x00
#define EVEN_PARITY             0x01
#define ODD_PARITY              0x02
#define MARK_PARITY             0x03

//Stop bits
#define STOP_BITS_1             0x00
#define STOP_BITS_2             0x01

//General DIO configurations
#define DIO_DISABLED            0x00
#define DIO_DIGITAL_INPUT_UNMOM 0x00
#define DIO_ANALOG_INPUT        0x02
#define DIO_DIGITAL_INPUT       0x03
#define DIO_DIGITAL_OUTPUT_LO   0x04
#define DIO_DIGITAL_OUTPUT_HI   0x05

//DIO7 Configuration
#define DIO7_CTS_FLOW_CONTROL   0x01
#define DIO7_RS485_LO_ENABLE    0x06
#define DIO7_RS485_HI_ENABLE    0x07

//DIO6 Configuration
#define DIO6_RTS_FLOW_CONTROL   0x01

//PWM0 Configuration
#define RSSI_PWM                0x01

//D0 Configuration
#define DIO0_COMMISH_BUTTON     0x01

//D5 Configuration
#define DIO5_ASSOC_LED          0x01

//RSSI PWM timer
#define RSSI_ALWAYS_ON          0xFF

//Association indication
#define JOINED_NTWRK            0x00
#define NO_PAN_FOUND            0x21
#define NO_VALID_PAN_FOUND      0x22
#define JOIN_NOT_ALLOWED        0x23
#define NO_JOINABLE_BEACONS     0x24
#define UNEXPECTED_STATE        0x25
#define JOIN_ATTEMPT_FAILED     0x27
#define COORD_START_FAILED      0x2A
#define EXISTING_COORD_CHECK    0x2B
#define LEAVE_NETWORK_FAILED    0x2C
#define DEVICE_NO_RESPONSE      0xAB
#define SEC_JOIN_ERR_UNSEC_KEY  0xAC
#define SEC_JOIN_ERR_NO_KEY     0xAD
#define SEC_JOIN_ERR_WRONG_KEY  0xAF
#define SCANNING_FOR_NETWORK    0xFF

//Sleep modes
#define SLEEP_DISABLED          0x00
#define PIN_SLEEP               0x01
#define CYCLIC_SLEEP            0x04
#define CYCLIC_SLEEP_PIN_WAKE   0x05

//Sleep options
#define WAKE_FOR_ST_TIME        0x02
#define SLEEP_ENTIRE_SN_SP_TIME 0x04

//Network reset options
#define RESET_NODE              0x00
#define RESET_NETWORK           0x01

//ND and DN response index values
#define MY_INDEX                0x00
#define SH_INDEX                0x02
#define SL_INDEX                0x06
#define NI_INDEX                0x0A

//IS index values
#define IS_NUM_SAMPLES          0x00
#define IS_DIG_MASK             0x01
#define IS_AN_MASK              0x03

//Digital mask values.
#define D_0                     0x0001
#define D_1                     0x0002
#define D_2                     0x0004
#define D_3                     0x0008
#define D_4                     0x0010
#define D_5                     0x0020
#define D_6                     0x0040
#define D_7                     0x0080
#define D_10                    0x0400
#define D_11                    0x0800
#define D_12                    0x1000

//Analog mask values.
#define ADC_0                   0x01
#define ADC_1                   0x02
#define ADC_2                   0x04
#define ADC_3                   0x08
#define ADC_VCC                 0x80

char *print_command_status(uint8_t command_status, char *status_description);
char *print_modem_status(uint8_t modem_status, char *status_description);
int   write_command_description(struct zb_rx *rx);
int   write_frame_description(struct zb_rx *rx);

#endif
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <termios.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <errno.h>
#include "zb_interface.h"

#define MODEMDEVICE "/dev/ttyUSB0"
#define BAUDRATE    B9600
#define BUFSZ       512
#define MAX_READ    256

int shutdown;

//Setting this to ESC_CHAE_ENABLED puts escape characters into
//the transmit frames and removes escape characters from the
//receive frames.
extern int esc_char;

//A linked list structure for storing Zigbee node data.
//One of these structures will be created for each Zigbee node.
struct zb_node {
    uint32_t serial_high;
    uint32_t serial_low;
    uint16_t address;
    uint8_t  node_type;
    char node_id[NID_LEN];
    struct zb_node *next;
};

//Pointers to beginning and end of zb_node linked list.
struct zb_node *list_start, *list_end;

//Function addToList is used to add a new structures
//to the linked list.  It returns nothing.
void add_to_list(struct zb_rx *rx) {
    struct zb_node *pzb_node;
    
    //Dynamically allocate memory for new struct.
    pzb_node = (struct zb_node*)malloc(sizeof(struct zb_node));
    
    if(!list_start) //Initialize linked list pointers if first file.
        list_start = list_end = pzb_node;
    else { //Update the end of the list.
        list_end->next = pzb_node;
        list_end = pzb_node;
    }   

    list_end->next = NULL;

    //Fill in list_end values.
    list_end->address     = rx->source_address;        
    list_end->serial_high = rx->source_serial_hi;
    list_end->serial_low  = rx->source_serial_lo;
    list_end->node_type   = rx->device_type;

    strcpy(list_end->node_id, rx->param_value.ni_value);
}

//Function free_list iterates over the link list and frees the
//dynamic memory used by the list.
void free_list() {
    struct zb_node *itt = list_start;
    struct zb_node *next_itt;

    while(itt) { //Iterate over entire list.
        next_itt = itt->next;
        free(itt);
        itt = next_itt;
    }
}

//print the node data from the linked list.
void print_list() {
    struct zb_node *itt = list_start;

    while(itt) { //Iterate over entire list.
        fprintf(stderr, "Serial High: %x, Serial Low: %x, Address: %x, Node Type: %s,\nNode ID: %s\n\n",
                itt->serial_high, itt->serial_low, itt->address, (itt->node_type == COORDINATOR) ?
                "Coordinator" : (itt->node_type == ROUTER) ? "Router" : (itt->node_type == END_DEVICE) ?
                "End Device" : "Unknown", itt->node_id);
        itt = itt->next;
    }
}

//Initialize the Zigbee com port.  Return 0 on success.
int init_termios(int fd, struct timeval *tv, fd_set *rfds) {
    struct termios options;

    bzero(&options, sizeof(options));
    options.c_cflag = BAUDRATE | CRTSCTS | CS8 | CLOCAL | CREAD;
    options.c_iflag = IGNPAR;
    options.c_oflag = 0;
        
    //Set input mode (non-canonical, no echo,...)
    options.c_lflag = 0;
         
    options.c_cc[VTIME]= 0; //Get all bytes as they come off the line.
    options.c_cc[VMIN] = 0; //No timeout and no minumum bytes.

    tcflush(fd, TCIFLUSH);
    tcsetattr(fd, TCSANOW, &options);

    FD_ZERO(rfds);         //Check Zigbee port for input.
    FD_SET(fd, rfds);

    return 0;
}

float calc_voltage(int i) {
    float voltage;
        voltage = (11 * ((float)(i * 1200) / 1024.0)) / 1000.0;
    return voltage;
}

void process_packet(struct zb_rx *rx) {
    int i = 0;
    
    fprintf(stdout, "%s\n", "HI");

    //For now, just deal with Node Discovery frames.
    if(rx->atcmd == ND)
        add_to_list(rx);

    //Print frame descriptions.
    if(rx->frame_description1[0])
        fprintf(stderr, "%s\n", rx->frame_description1);
    if(rx->frame_description2[0])
        fprintf(stderr, "%s\n", rx->frame_description2);
    if(rx->frame_description3[0])
        fprintf(stderr, "%s\n", rx->frame_description3);
    if(rx->frame_description4[0])
        fprintf(stderr, "%s\n", rx->frame_description4);

    //Print raw packet data.    
    for(i = 0; i < rx->length; i++)
        fprintf(stderr, "%x ", rx->payload[i]);
    fprintf(stderr, "\n");    
}

void *scan_rx(void *file_d) {
    int retval, packet_ready, rx_packet_size;
    unsigned char rx_packet[BUFSZ];
    int fd = (int)file_d;
    struct timeval tv;
    struct zb_rx rx;   
    fd_set rfds;

    memset(&rx, 0, sizeof(rx)); //Zero out rx structure.
    init_termios(fd, &tv, &rfds); //Initialize Zigbee serial port.

    //Capture all data as long as a shutdown is not indicated.
    while(!shutdown) {       
        rx_packet_size = read(fd, rx_packet, MAX_READ);

        get_zb_rx_frame(rx_packet, rx_packet_size);
                         
        while(get_rx_frame(&rx) == ZB_ERR_SUCCESS) {
        fprintf(stdout, "%s\n", "HI");
            process_packet(&rx);
            memset(&rx, 0, sizeof(rx)); //Zero out rx structure.
        }
        usleep(500000);
    }   
}

int main() {
    uint8_t buf[NID_LEN];
    int fd, ep_num = 1, rt_num = 1;   
    union  params param;
    struct serial_num sn;
    struct zb_node *itt;
    struct zb_tx tx;
    pthread_t t1;

    //Enable escaped characters (Only used when API = 2).
    //esc_char = ESC_CHAR_ENABLED;

    //Open Zigbee serial port.
    fd = open(MODEMDEVICE, O_RDWR | O_NOCTTY | O_NDELAY);
    if(fd == -1) {
        fprintf(stderr, "Open %s failed!: %s\n", MODEMDEVICE, strerror(errno));
        return -1;
    }       

    //Start thread to monitor incomming Zigbee data.
    pthread_create(&t1, NULL, &scan_rx, (void *)fd);

    //Discover nodes on network.
    at_command_queue(0x01, ND, 0, fd);

    //Wait for response so link list can be generated.
    sleep(5);

    //Print network node data.
    print_list();

    itt = list_start;

    //Read sampled data from all nodes.
    while(itt) {
        sn.serial_hi = itt->serial_high;
        sn.serial_lo = itt->serial_low;
        sn.address   = itt->address;
        read_remote_at_command(0x01, &sn, 0, IS, fd);
        itt = itt->next;
    }

    /*itt = list_start;

    while(itt) {
        sn.serial_hi = itt->serial_high;
        sn.serial_lo = itt->serial_low;
        sn.address   = itt->address;

        sprintf(buf, "A\x7E\x7D\x11\x13", ep_num++);                
        tx_request(0x01, &sn, 0xFF, 0, buf, fd);

        itt = itt->next;
    }*/


    /*itt = list_start;

    //Set node identifiers for all nodes.
    while(itt) {
        sn.serial_hi = itt->serial_high;
        sn.serial_lo = itt->serial_low;
        sn.address   = itt->address;

        if(itt->node_type == END_DEVICE) {
            sprintf(buf, "END POINT %d", ep_num++);
            strcpy(param.zb_nid, buf);
        }
        else if(itt->node_type == ROUTER) {
            sprintf(buf, "ROUTER %d", rt_num++);
            strcpy(param.zb_nid, buf);
        }
        else if(itt->node_type = COORDINATOR)
            strcpy(param.zb_nid, "COORDINATOR");
        else
            strcpy(param.zb_nid, "UNKNOWN");

        write_remote_at_command(0x01, &sn, APPLY_CHANGES, NI, &param, fd);

        itt = itt->next;
    }*/

    /*itt = list_start;

    //Save all names on nodes.
    while(itt) {
        sn.serial_hi = itt->serial_high;
        sn.serial_lo = itt->serial_low;
        sn.address   = itt->address;

        read_remote_at_command(0x01, &sn, APPLY_CHANGES, WR, fd);

        itt = itt->next;
    }*/

    itt = list_start;

    //Send test message to all endpoints.
   while(itt) {
        sn.serial_hi = itt->serial_high;
        sn.serial_lo = itt->serial_low;
        sn.address   = itt->address;

        if(itt->node_type == END_DEVICE) {
            sprintf(buf, "\x13\x06TEST Message %d", ep_num++);                
            tx_request(0x01, &sn, 0xFF, 0, buf, fd);
        }

        itt = itt->next;
    }

    while(1){
        


    }

    //Wait 2 seconds for responses before shutting down rx monitor.
    sleep(2);

    //Clean up resources.
    shutdown = 1;
    pthread_join(t1, NULL);
    free_list();
    close(fd);

    return 0;
}
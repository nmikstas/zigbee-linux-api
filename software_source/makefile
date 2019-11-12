all: run clean

run:
    gcc -c zb_api.c
    gcc -c zb_rx_desc.c
    gcc -c zb_tx_desc.c
    gcc -c zb_interface.c
    gcc control.c zb_api.o zb_rx_desc.o zb_tx_desc.o zb_interface.o -o control -lpthread

clean:
    rm -f zb_api *.o *.a
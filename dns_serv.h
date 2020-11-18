/**
 * VUT FIT Brno
 * 28.10.2020
 *
 * Authors:
 * Lukas Javorsky (xjavor20)
 * 
 * File: dns_serv.h
 *
 */

#ifndef DNS_SERV_H
#define DNS_SERV_H

#define PACKET_SIZE 512
#define ever (; ;)

typedef struct server
{
    int port;
	int listen_fd;

} server_t;

extern server_t dns_server;

/**
 * Initialize the dns server
 * @param port Which port is used for this dns
 */
void dns_init(int port);

/**
 * Creates the dns loop for clients
 */
void dns_loop(char *filter_fn, char *server);

/**
 * Masks the rcode bits to the 'rcode' value
 * @param rcode What rcode you want to return
 * @param buf Data buffer
 */
void mask_rcode(short rcode, char * buf);

/**
 * Set's the QR bit to 1
 * @param buf Data buffer
 */
void set_qr_bit(char * buf);

/**
 * Opens a socket for the communication with client
 */
void listen_sockets();

#endif //DNS_SERV_H
/**
 * VUT FIT Brno
 * 28.10.2020
 *
 * Authors:
 * Lukas Javorsky (xjavor20)
 * 
 * File: dns_serv.c
 *
 */

#include "dns_serv.h"
#include "dns_packet.h"
#include "error.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

server_t dns_server;

void dns_init(int port)
{
	dns_server.port = port;
	dns_server.listen_fd = 0;
}

void dns_loop(char *filter_fn, char *server)
{
    char buf[PACKET_SIZE+4];
    struct sockaddr_in sock_addr;
    dns_packet_t *pkt;
    socklen_t sock_addr_len = sizeof (sock_addr);
    int req_byte_size;
    int flags = 0;

    for ever
    {
        req_byte_size = recvfrom(dns_server.listen_fd, buf, PACKET_SIZE + 4, flags, (struct sockaddr *) &sock_addr, &sock_addr_len);
        
        pkt = calloc(1, sizeof (dns_packet_t));
        
        int res = dns_request_parse(pkt, buf, req_byte_size, filter_fn);
        // It is valid query
        if (res == 0)
        {   
            int client_sockfd, len;
            struct sockaddr_in serv_addr, from;

            assert((client_sockfd = socket(AF_INET, SOCK_DGRAM, 0)) > 0);

            memset(&serv_addr, 0, sizeof (serv_addr));
            serv_addr.sin_family = AF_INET; // IPv4 
            serv_addr.sin_addr.s_addr = inet_addr(server); 
            serv_addr.sin_port = htons(53);

            len = sizeof(serv_addr);
            int i;
            if((i = sendto(client_sockfd, buf, req_byte_size, flags, (struct sockaddr *) &serv_addr, len)) == -1)
            {
                // Given server is not correct
                mask_rcode(2, buf);
                set_qr_bit(buf);
                sendto(dns_server.listen_fd, buf, req_byte_size, 0, (struct sockaddr *)&sock_addr, sock_addr_len);
            }
            if (getsockname(client_sockfd, (struct sockaddr *) &from, &len) == -1)
                errorMsg("Operation getsockname failed\n");

            if ((i = recvfrom(client_sockfd, buf, PACKET_SIZE +4, flags, (struct sockaddr *) &from, &len)) == -1)   
                errorMsg("Failed to recieve from DNS server\n");
            else if (i > 0){
                // Send the answer from DNS to the client
                sendto(dns_server.listen_fd, buf, i, flags, (struct sockaddr *)&sock_addr, len);
            }
            close(client_sockfd);
        } else if (res == 1) // Not allowed RCODE = 5
        {
            // This domain is in black-list
            mask_rcode(5, buf);
            set_qr_bit(buf);
            sendto(dns_server.listen_fd, buf, req_byte_size, 0, (struct sockaddr *)&sock_addr, sock_addr_len);
        } else // Not implemented RCODE = 4
        {
            mask_rcode(4, buf);
            set_qr_bit(buf);
            sendto(dns_server.listen_fd, buf, req_byte_size, 0, (struct sockaddr *)&sock_addr, sock_addr_len);
        }
        free(pkt->data);
        free(pkt);
    }
}

void mask_rcode(short rcode, char * buf)
{
    short zero_the_rcode = 240;
    buf[3] = (buf[3] & zero_the_rcode) | rcode;
}

void set_qr_bit(char * buf)
{
    short qr = 128;
    buf[2] = buf[2] | qr;
}

int listen_sockets()
{
	struct sockaddr_in servaddr;
	int sockfd;

	assert((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) > 0);

	memset(&servaddr, 0, sizeof (servaddr));
    servaddr.sin_family = AF_INET; // IPv4 
    servaddr.sin_addr.s_addr = INADDR_ANY; 
    servaddr.sin_port = htons(dns_server.port); 

	if(bind(sockfd, (const struct sockaddr *) &servaddr, sizeof (servaddr)))
        return errorMsg("Socket bind was not successful. Try executing with 'sudo'");
	dns_server.listen_fd = sockfd;
    return EXIT_SUCCESS;
}

/**
 * VUT FIT Brno
 * 28.10.2020
 *
 * Authors:
 * Lukas Javorsky (xjavor20)
 * 
 * File: dns_packet.h
 *
 */

#ifndef DNS_PACKET_H
#define DNS_PACKET_H

#include <sys/types.h>

#define DNS_HEADER_SIZE 12

typedef struct dns_header
{
	u_int16_t id;
	u_int16_t qr:1;
	u_int16_t opcode:4;
	u_int16_t aa:1;
	u_int16_t tc:1;
	u_int16_t rd:1;
	u_int16_t ra:1;
	u_int16_t z:3;
	u_int16_t rcode:4;
	u_int16_t qdcount;
	u_int16_t ancount;
	u_int16_t nscount;
	u_int16_t arcount;

} dns_header_t;

typedef struct dns_packet
{
	dns_header_t header;
	char *data;
	u_int16_t data_size;

} dns_packet_t;

/**
 * Parse the request from client
 * @param pkt Packet that stores the DNS header in struct form and packet data
 * @param pkt_data Data recieved from the client
 * @param size Size of the data
 * @param filter_fn Filter filename
 * @return 0 if everything is correct, 1 if the domain is refused, 2 if the QTYPE is not implemented
 */
int dns_request_parse (struct dns_packet *pkt, void *pkt_data, u_int16_t size, char *filter_fn);

/**
 * Parse the DNS header
 * @param header DNS header pointer
 * @param pkt_data Data recieved from client
 */
void dns_header_parse (struct dns_header *header, void *pkt_data);

/**
 * Parse the question.
 * Checks for the domain name and QTYPE
 * @param pkt Packet that's gonna be parsed
 * @param filter_fn Filter filename
 * @return 0 if everything is correct, 1 if the domain is refused, 2 if the QTYPE is not implemented
 */
int dns_question_parse (struct dns_packet *pkt, char *filter_fn);

#endif //DNS_PACKET_H
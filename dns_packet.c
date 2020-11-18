/**
 * VUT FIT Brno
 * 28.10.2020
 *
 * Authors:
 * Lukas Javorsky (xjavor20)
 * 
 * File: dns_packet.c
 *
 */

#include "dns_packet.h"
#include "filter.h"

#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>



int dns_request_parse (dns_packet_t *pkt, void *pkt_data, u_int16_t pkt_size, char *filter_fn)
{
	dns_header_parse (&pkt->header, pkt_data);

	pkt->data = malloc (pkt_size - DNS_HEADER_SIZE);
	memcpy (pkt->data, pkt_data + DNS_HEADER_SIZE, pkt_size - DNS_HEADER_SIZE);
	pkt->data_size = pkt_size - DNS_HEADER_SIZE;

    int	i, result = 0;
	while (i < pkt->header.qdcount)
	{
		result = dns_question_parse (pkt, filter_fn);
		i++;
	}
	return result;
}

void dns_header_parse (dns_header_t *header, void *pkt_data)
{
	memcpy(header, pkt_data, DNS_HEADER_SIZE);

	header->id = ntohs(header->id);
    header->nscount = ntohs(header->nscount);
	header->arcount = ntohs(header->arcount);
	header->qdcount = ntohs(header->qdcount);
	header->ancount = ntohs(header->ancount);
}

int dns_question_parse (dns_packet_t *pkt, char *filter_fn)
{
	u_int16_t j, length;
	char *question = pkt->data;
    char domain[1000] = "";
	int i = 0;
	length = question[i++];

	do
	{
        if(strcmp(domain, ""))
        {
            char dot = '.';
            strncat(domain, &dot, 1);
        }
        
		for (j = 0; j < length; j++)
            strncat(domain, &question[i+j], sizeof(question[i+j]));
        
		i += length;
		length = question[i++];
	} while (i < pkt->data_size && length != 0);
    
    // Parse QTYPE octets
    uint16_t qtype = htons(question[i++])+question[i++];
    // Return that the QTYPE is not implemented
    if(qtype != 1) return 2;
    int result = filter_domain(filter_fn, domain);
	return result;
}
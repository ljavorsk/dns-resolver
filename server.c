/**
 * VUT FIT Brno
 * 28.10.2020
 *
 * Authors:
 * Lukas Javorsky (xjavor20)
 * 
 * File: server.c
 *
 */

#include "error.h"
#include "dns_serv.h"
#include <stdlib.h>
#include <unistd.h>


int main(int argc, char *argv[])
{
   int option;
   int server_flag, filter_flag, port_flag = 0;
   char *server;
   int port = 53;
   char *filter_file;
   
   // Parse and check arguments
   while((option = getopt(argc, argv, ":s:f:p:")) != -1){ 
      switch(option){
         case 's':
            server_flag++;
            server = optarg;
            break;
         case 'f':
            filter_flag++;

            // Check the file
            char *filename = optarg;
            int is_it_file = access(filename, F_OK);
            if(is_it_file) return errorMsg("Filter file doesn't exists");

            filter_file = optarg;
            break;
         case 'p':
            port_flag++;
            char *ptr;

            long tmp_port = strtol(optarg, &ptr, 10);
            if((*ptr) || tmp_port < 0 || tmp_port > 65535){   // There was something more than a number or number is invalid
                return errorMsg("Invalid port number");
            }

            port = (int) tmp_port;
            break;
         case ':':
            printf("\n");
            return errorMsg("You need to provide a value to every option");
         case '?':
            return errorMsg("Unknown option");
        }
   }

   if(server_flag != 1 || filter_flag != 1 || port_flag > 1){
        return errorMsg("You can only provide 3 options\n"
        "('-s server' and '-f filter' are mandatory, '-p port' is optional)");
   } 
   else{
      dns_init(port);
      listen_sockets();
      dns_loop(filter_file, server);
   }
}
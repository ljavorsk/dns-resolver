# Filtering DNS resolver

**Author:** Lukas Javorsky  
**Student ID:** xjavor20  
**School:** BUT FIT  
**Subject:** ISA (Network Applications and Network Administration)  
**Application language:** C

## Abstract
Local DNS resolver that resolves only **A** type queries.  
Any other query types are returned as **NOTIMP** (**RCODE = 4**).  
DNS resolver filters the permited domains which are listed in file given
by `-f` argument.  
User can specify custom port (`-p` argument) which will DNS resolver listen to.  
If not the port is **53** by default.  
If the query is correct, DNS resolver sends this query to the specified (`-s` argument) DNS server
and returns the answer to the client.  

## Usage
`./dns -s <server> [-p <port>] -f <filter_filename>`

## Example
`./dns -s "8.8.8.8" -p 4242 -f ./filer_domains.txt`

### Print help
`./dns --help`  
This command prints the help, to make user better understand how to use this tool.

## Not implemented
The IPv6 is not implemented in this resolver, so it won't work.  
Also you need to provide server as IP adress not as domain name in `-s` argument.  

# Filtering DNS resolver

## Abstract
Local DNS resolver that resolves only A type queries.  
Any other query types are returned as NOTIMP (RCODE = 4).  
DNS resolver filters the permited domains which are listed in file given
by -f argument.  
User can specify custom port (-p argument) which will DNS resolver listen to.  
If not the port is 53 by default.  
If the query is correct, DNS resolver sends this query to the specified (-s argument) DNS server
and returns the answer to the client.  

## Usage
`./dns -s <server> [-p <port>] -f <filter_filename>`

## Example
`./dns -s "8.8.8.8" -p 4242 -f ./filer_domains.txt`

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#define NO_IPV6 "NO_IPV6_AVAILABLE"
/*
    struct addrinfo {
        int              ai_flags;     // AI_PASSIVE, AI_CANONNAME, etc.
        int              ai_family;    // AF_INET, AF_INET6, AF_UNSPEC
        int              ai_socktype;  // SOCK_STREAM, SOCK_DGRAM
        int              ai_protocol;  // use 0 for "any"
        size_t           ai_addrlen;   // size of ai_addr in bytes
        struct sockaddr *ai_addr;      // struct sockaddr_in or _in6
        char            *ai_canonname; // full canonical hostname
    
        struct addrinfo *ai_next;      // linked list, next node
    };

    int getaddrinfo(const char *node,     // e.g. "www.example.com" or IP
                        const char *service,  // e.g. "http" or port number
                        const struct addrinfo *hints,
                        struct addrinfo **res);
*/

char *retip4(char *DOMAIN_NAME)
{
	struct addrinfo hints;
	memset(&hints, 0, sizeof(hints));
	hints.ai_flags = AI_PASSIVE; // FIll my IP
	hints.ai_family=AF_INET; //IPv4
	hints.ai_socktype = SOCK_STREAM; // TCP

	int status;
	struct addrinfo *res;
	void *addr;

	static char ipstr[INET_ADDRSTRLEN];
	
	if ((status = getaddrinfo(DOMAIN_NAME, NULL, &hints, &res)) != 0) 
	{
	        fprintf(stderr, " getaddrinfo: %s\n", gai_strerror(status)); // Write to stderr
	        exit(-1);
	}

	struct sockaddr_in *ipv4 = (struct sockaddr_in *)res->ai_addr;
	addr = &(ipv4->sin_addr);

	// convert the IP to a string and print it:
    inet_ntop(res->ai_family, addr, ipstr, sizeof(ipstr));
    freeaddrinfo(res);

	return ipstr;
}

char *retip6(char *DOMAIN_NAME)
{
	struct addrinfo hints;
	memset(&hints, 0, sizeof(hints));
	hints.ai_flags = AI_PASSIVE; // FIll my IP
	hints.ai_family=AF_INET6; //IPv6
	hints.ai_socktype = SOCK_STREAM; // TCP

	int status;
	struct addrinfo *res;
	void *addr;

	static char ipstr[INET6_ADDRSTRLEN];

	if ((status = getaddrinfo(DOMAIN_NAME, NULL, &hints, &res)) != 0) 
	{
	        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status)); // Write to stderr
	        exit(-1);
	}

	while(res != NULL)
	{
		if(res->ai_family == AF_INET6 )
		{
			struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)res->ai_addr;
	        addr = &(ipv6->sin6_addr);
	        inet_ntop(res->ai_family, addr, ipstr, sizeof(ipstr));
	        freeaddrinfo(res);
	        return ipstr;
		}
	res=res->ai_next;
	}

	return NO_IPV6;
}

void main(int argc, char *argv[])
{

	if(argc != 2)
	{
		printf("[-] Usage %s Hostname\n",argv[0]);
		exit(-1);
	}

	printf("IPv4 : %s\n",retip4(argv[1]));
	printf("IPv6 : %s\n",retip6(argv[1]));

}

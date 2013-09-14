#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/types.h>
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/ioctl.h>

int main()
{
	int clients[1024];
	int num_clients=0;
	int serverfd;
	struct sockaddr_in serveraddr;

	serverfd = socket(AF_INET,SOCK_STREAM,0);
	
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(40000);
	
	bind(serverfd,(struct sockaddr*) &serveraddr,sizeof(serveraddr));

	listen(serverfd,5);

	fd_set input,testfd;
	
	FD_ZERO(&input);
	FD_SET(serverfd,&input);

	while(1)
	{
		testfd = input;
		int fd;
		
		int result = select(FD_SETSIZE,&testfd,(fd_set*)0,(fd_set*)0,(struct timeval*)0);

		if(result == 0)
		{
			printf("timeout\n");
			exit(1);
		}
		if(result == -1)
		{
			printf("select error\n");
			exit(1);
		}
		for(fd=0;fd<FD_SETSIZE;fd++)
		{
			if(FD_ISSET(fd,&testfd) != 0)
			{
				if(fd == serverfd)
				{
					//struct sockadd
					int len = sizeof(struct sockaddr);
					int client = accept(serverfd,(struct sockaddr*)0,&len);
					clients[num_clients++] = client;
					FD_SET(client,&input);
					printf("new client,total %d\n",num_clients);
				}
				else
				{
					int nread;
					ioctl(fd,FIONREAD,&nread);
					if(nread == 0)
					{
						close(fd);
						FD_CLR(fd,&input);
						printf("remove clinet\n");
					}
					else
					{
						//read
					}
				}
			}
		}

	}
	exit(0);
}

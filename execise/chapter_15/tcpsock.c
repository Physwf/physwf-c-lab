#include "tcpsock.h"
#include <netinet/in.h>

int tcpsock_init_server(tcpsock *tsock,short port)
{
	tsock->sockfd = socket(AF_INET,SOCK_STREAM,0);
	//set address
	struct sockaddr_in sockaddr;
	sockaddr.sin_family = AF_INET;
	sockaddr.sin_addr.in_addr = htonl(INADDR_ANY);
	sockaddr.sin_port = htons(port);
	tsock->address = sockaddr;
	//bind
	int ret;
	ret = bind(tsock->sockfd,(struct sockaddr*)&sockaddr,sizeof(sockaddr));
	if(ret < 0)
	{
		return ETCPSOCK_BIND; 
	}
	//listen
	ret = listen(tsock->sockfd,5);
	if(ret < 0)
	{
		return ETCPSOCK_LISTEN; 
	}
}

int tcpsock_init_client(tcpsock *tsock,int port)
{
	tsock->sockfd = socket(AF_INET,SOCK_STREAM,0);
}
/**
 *
 *
 *
 **/
int tcpsock_client_connect(tcpsock *tsock,char *addr,short port)
{
	struct sockaddr_in sockaddr;
	sockaddr.sin_family = AF_INET;
	sockaddr.sin_addr.in_addr = inet_addr(addr);
	sockaddr.sin_port = htons(port);
	tsock->address = sockaddr;

	int ret;
	ret = connect(tcpsock->sockfd,(struct sockaddr*)sockaddr,sizeof(sockaddr));
	if(ret < 0)
	{
		return ETCPSOCK_CONNECT; 
	}
	return 0;
}

int tcpsock_server_accept(tcpsock *tsock,tcpsock *client,struct timeval *t)
{
	fd_set testset;
	FD_ZERO(&testset);
	FD_SET(tsock->sockfd,&testfd);

	int result;
	int fd;

	result = select(FD_SETSIZE,&testset,(fd_set*)0,(fd_set*)0,t);
	if(result == -1)
	{
		return ETCPSOCK_LOOP;
	}
	if(result == 0)
	{
		return ETCPSOCK_LOOP_TIMEOUT;
	}		
	for(fd=0;fd<FD_SETSIZE;fd++)
	{
		if(FD_ISSET(fd)!=0)
		{
			if(fd == tsock->sockfd)
			{
				client->sockfd = accpet(tsock->sockfd,(struct sockaddr*)client->address,sizeof(client->address));
				if(client.sockfd == -1)
				{
					return ETCPSOCK_ACCEPT;
				}
				return 1;
			}
		}
	}
	
	return 0;
}

int tcpsock_read(tcpsock tsocks[],int len,struct timeval *t)
{
	fd_set readset;
	FD_ZERO(&readset);

	int i;
	int result;

	for(i=0;i<len;++i)	
	{
		FD_SET(tcpsocks[i].sockfd,&readset);
		
		result = select(tcpsocks[i].sockfd,(fd_set*)&readset,(fd_set*)NULL,(fd_set*)NULL,t);
		if(result>0)
		{
			//read
		}
	}
}

int tcpsock_write(tcpsock tsocks[],int len,struct timeval *t)
{
	fd_set writeset;
	FD_ZERO(&writeset);

	int i;
	int result;

	for(i=0;i<len;++i)
	{
		FD_SET(tcpsocks[i].sockfd,&writeset);

		result = select(tcpsocks[i].sockfd,(fd_set*)NULL,(fd_set*)&writeset,(fd_set*)NULL,t);
		if(result>0)
		{
			//write
		}
}

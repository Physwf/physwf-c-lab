#include <netdb.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>

int main()
{
	char *a = "127.0.0.1";
	struct in_addr n;
	if(inet_aton(a,&n) == 0)
	{
		printf("error in inet_aton\n");
		return 1;
	}
	
	struct hostent *host = gethostbyaddr(&n,sizeof(n),AF_INET);
	int len=0;
	int i=0;
	char alias[8];
	if(host != NULL)
	{
		printf("%s\n",host->h_name);
		printf("%d\n",sizeof(host->h_aliases));
		
		len = sizeof(host->h_aliases)/sizeof(host->h_aliases[0]);
		printf("%d\n",len);	

		if(host->h_aliases[0] == NULL)
		{
			printf("null value\n");
			return 2;
		}

		for(;i<len;++i)
		{
			printf("%s\n",host->h_aliases[0]);	
		}
	}
	return 0;
}

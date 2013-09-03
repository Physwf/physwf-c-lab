#include <stdio.h>
#include <stdlib.h>

int main()
{
	FILE * file;
	void * buffer;
	
	file = fopen("draft1.txt","r");
	if(file == NULL)
	{
		printf("fopen error!");
		exit(1);
	}
	
	buffer = malloc(1024);
	size_t len = fread(buffer,1,20,file);
	if(len == -1)
	{
		printf("fread error!");
		exit(2);
	}

	printf("read len:%d\n",len);	
	printf("the file content is:%s\n",(char*)buffer);
	fclose(file);
	exit(0);
}

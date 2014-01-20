#include "utils.h"

long t_read(const char* filename,const char*** text)
{
	long length=0;
	char *buffer;
	FILE *infile = fopen(filename,"r");
	if(infile == NULL) 
	{
		printf("Can't open file:%s\n",filename);
		return -1;
	}
	fseek(infile,0,SEEK_END);
	length = ftell(infile);
	fseek(infile,0,SEEK_SET);
	
	// printf("%d",length);
	buffer = (char*)calloc(length,sizeof(char));
	if(buffer == NULL)
	{
		printf("Allocate memory error!\n");
		return -1;
	}
	fread(buffer,sizeof(char),length,infile);
	fclose(infile);
	
	// printf("%s",buffer);
	int numline;
	char *pc;
	for(pc = strchr(buffer,'\n'),numline=1;pc!=NULL;pc=strchr(pc,'\n'),numline++)
	{
		if(*pc == '\n') pc++;
	}
	printf("%d",numline);
	const char ** t;
	t = (const char**)calloc(numline+1,sizeof(char*));
	t[0] = buffer;
	for(pc = strchr(buffer,'\n'),numline=1;pc!=NULL;pc=strchr(pc,'\n'))
	{
		//if(*pc == '\n') *pc++='\0';
        if(*pc == '\n') *pc++;
		if(pc != NULL) t[numline++] = pc;
	}
	t[numline] = NULL;
	*text = t;
	return length;
}
void t_print(const char* filename)
{
	char c;
	int numline=0;
	FILE *file = fopen(filename,"r");
	if(file ==NULL) 
	{
		printf("Cannot open file:%s",filename);
		return;
	}
	while((c = fgetc(file))!=EOF)
	{
		if(c == '\n') printf("\\n\n%d",++numline);
		else if(c == '\r') printf("\\r");
		else printf("%c",c);
	};
}

void pointer_test(int ***px,const char ***pc)
{
	int a = 13;
	int b = 14;
	*px = (int **)calloc(2,sizeof(int*));
	*px[0] =&a;
	*px[1] =&b;
	printf("%d\n",***px++);
	printf("%d\n",***px);
	
	const char *c1 = "a1";
	const char *c2 = "b1";
	*pc = (const char **)calloc(4,sizeof(char*));
	*pc[0] = c1;
	*pc[1] = c2;
	printf("%s\n",**pc++);
	printf("%s\n",**pc);
}

int __main(int argc,char** argv)
{
	const char *a = "0";
	const char **text=&a;
	long len = t_read("../RedBook/chapter_1/triangles.vert",&text);
	// printf("%s\n",text[0]);
	while(*text)
	{
		printf("%s\n",*text++);
	}
	getchar();
	return 0;
}
#include "utils.h"

long t_read(const char* filename,char*** text)
{
	long length=0;
	char *buffer;
	FILE *infile = fopen(filename,"r");
	if(infile == NULL) 
	{
		printf("Can't open file:%s",filename);
		return -1;
	}
	fseek(infile,0,SEEK_END);
	length = ftell(infile);
	fseek(infile,0,SEEK_SET);
	
	// printf("%d",length);
	buffer = (char*)calloc(length,sizeof(char));
	if(buffer == NULL)
	{
		printf("Allocate memory error!");
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
	char ** t;
	t = (char**)calloc(numline+1,sizeof(char*));
	t[0] = buffer;
	for(pc = strchr(buffer,'\n'),numline=1;pc!=NULL;pc=strchr(pc,'\n'))
	{
		if(*pc == '\n') *pc++='\0';
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

void pointer_test(int ***px,char ***pc)
{
	int a = 13;
	int b = 14;
	*px = (int **)calloc(2,sizeof(int*));
	*px[0] =&a;
	*px[1] =&b;
	printf("%d\n",***px++);
	printf("%d\n",***px);
	
	char *c1 = "a1";
	char *c2 = "b1";
	*pc = (char **)calloc(4,sizeof(char*));
	*pc[0] = c1;
	*pc[1] = c2;
	printf("%s\n",**pc++);
	printf("%s\n",**pc);
}

int main(int argc,char** argv)
{
	char *a = "0";
	char **text=&a;
	long len = t_read("../RedBook/chapter_1/triangles.vert",&text);
	// printf("%s\n",text[0]);
	while(*text)
	{
		printf("%s\n",*text++);
	}
	// int **x;
	// char ** c;
	// pointer_test(&x,&c);
	// printf("%d\n",(**x++));
	// printf("%d\n",**x);
	
	
	// int **y = (int **)calloc(2,sizeof(int*));
	// int a = 15;
	// int b = 16;
	// y[0] = &a;
	// y[1] = &b;
	// printf("%d",**y++);
	// printf("%d",**y);
	getchar();
	return 0;
}
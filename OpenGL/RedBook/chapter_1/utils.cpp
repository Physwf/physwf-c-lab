#include "utils.h"

long t_read(const char* filename,char*** text)
{
	long length;
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
	// printf("%d",numline);
	*text = (char**)calloc(numline+1,sizeof(char*));
	*text[0] = buffer;
	for(pc = strchr(buffer,'\n'),numline=1;pc!=NULL;pc=strchr(pc,'\n'))
	{
		if(*pc == '\n') *pc++='\0';
		if(pc != NULL) *text[numline++] = pc;
	}
	*text[numline] = NULL;
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

int main(int argc,char** argv)
{
	// t_print("../RedBook/chapter_1/triangles.vert");
	char **text=NULL;
	long len = t_read("../RedBook/chapter_1/triangles.vert",&text);
	// while(*text)
	// {
		// printf("%d",strlen(*text));
		// printf("%s\n",*text++);
	// }
	getchar();
	return 0;
}
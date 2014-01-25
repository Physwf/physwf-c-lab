#include "utils.h"

int t_read(const char* filename,const char*** text,int** lengths)
{
	int size=0;
	char *buffer;
	FILE *infile = fopen(filename,"r");
	if(infile == NULL) 
	{
		printf("Can't open file:%s\n",filename);
		return 0;
	}
	fseek(infile,0,SEEK_END);
	size = ftell(infile);
	fseek(infile,0,SEEK_SET);
	
	// printf("%d",size);
	buffer = (char*)calloc(size,sizeof(char));
	if(buffer == NULL)
	{
		printf("Allocate memory error!\n");
		return 0;
	}
	fread(buffer,sizeof(char),size,infile);
	fclose(infile);
	
	// printf("%s",buffer);
	int numline;
	char *pc;
	for(pc = strchr(buffer,'\n'),numline=1;pc!=NULL;pc=strchr(pc,'\n'),numline++)
	{
		if(*pc == '\n') pc++;
	}
	printf("%s numline:%d\n",filename,numline);
	int *lens = (int *)calloc(numline,sizeof(int));
	const char ** t;
	t = (const char**)calloc(numline+1,sizeof(char*));
	t[0] = buffer;
    lens[0] = strchr(buffer,'\n') - buffer;
	for(pc = strchr(buffer,'\n'),numline=1;pc!=NULL;pc=strchr(pc,'\n'))
	{
        if(*pc == '\n') 
		{
			*pc++=NULL;
			// pc++;
            if (strchr(pc,'\n') !=NULL) {
                lens[numline]= strchr(pc,'\n') - pc;
            }
		}
		if(pc != NULL) t[numline++] = pc;
	}
	t[numline] = NULL;
	*text = t;
    *lengths = lens;
	printf("numline end%d\n",numline);
	return numline;
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

int __main(int argc,char** argv)
{
    const char ** text;
    int *lengths;

    int numlines = t_read("./triangles.vert",&text,&lengths);
	printf("numline%d\n",numlines);
    for (int i=0; i<numlines; i++) {
        printf("len:%d\n",lengths[i]);
        printf("%s\n",text[i]);
    }
//    t_print("./triangles.vert");
    getchar();
	return 0;
}
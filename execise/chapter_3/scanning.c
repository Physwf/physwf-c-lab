#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

void list_dir(char *path)
{
	DIR *pDir;
	struct dirent *pEnt;
	char childpath[512];
	pDir = opendir(path);
	
	memset(childpath,0,sizeof(childpath));
	while((pEnt = readdir(pDir)) != NULL)
	{
		if(strcmp(pEnt->d_name,".") == 0 || strcmp(pEnt->d_name,"..") == 0) continue;
		if(pEnt->d_type & DT_DIR)
		{
			sprintf(childpath,"%s/%s",path,pEnt->d_name);
			printf("%s\n",childpath);
			list_dir(childpath);
		}
	}
}

int main(int argc, char **argv)
{
	list_dir(argv[1]);	
	return 0;
}

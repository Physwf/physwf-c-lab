#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <stack>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char **argv)
{
	char *root_path;
	DIR *root;
	
	std::stack<DIR*> dir_stack;
	
	if(argc <= 1)
	{
		printf("no directory supplied!\n");
		exit(1);
	}
	root_path = argv[1];
	//struct stat *root_stat;
	//stat(root_path,root_stat);
	//if(S_ISDIR(root_stat->st_mode))
	//{
	//	printf("root is dir\n");
	//}
	
	root = opendir(root_path);
	if(root == NULL)
	{
		printf("Root directory error!\n");
		exit(1);
	}
	chdir(root_path);

	dir_stack.push(root);
	DIR *cur_dir;
	struct dirent *entry = NULL;
	while(!dir_stack.empty())
	{
		cur_dir = dir_stack.top();
		dir_stack.pop();
		
		struct stat *fstat;
		while((entry = readdir(cur_dir))!=NULL)
		{
			stat(entry->d_name,fstat);
			//if(S_ISDIR(fstat->st_mode))
			//{
			//	DIR *dir = opendir(entry->d_name);
			//	printf("find dir:%s\n",entry->d_name);
				//dir_stack.push(dir);
			//	printf("dir\n");
			//	continue;
			//}
			if(S_ISREG(fstat->st_mode))
			{
				printf("the file name is:%s \nthe mtime is:%d\n",entry->d_name,fstat->st_mtime);
			}
		}	
	}
	
	exit(0);	
}

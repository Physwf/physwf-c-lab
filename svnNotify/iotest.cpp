#define _WIN32_WINNT 0x0500
#include <stdio.h>
#include <windows.h>


 
int dirMonitor(void)
{	
	HANDLE hFileRead;
	LPSTR fileName = "text";
	
	hFileRead = CreateFile(fileName,GENERIC_READ,FILE_SHARE_READ|FILE_SHARE_WRITE,NULL,OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS,NULL);
	

	char notify[1024];
	DWORD cbBytes;
	
	FILE_NOTIFY_INFORMATION *pnotify = (FILE_NOTIFY_INFORMATION *) notify;
	FILE_NOTIFY_INFORMATION *temp;
	BOOL ret;
	while(TRUE)
	{
		ret = ReadDirectoryChangesW(
								hFileRead,&notify,sizeof(notify),FALSE,
								FILE_NOTIFY_CHANGE_FILE_NAME | FILE_NOTIFY_CHANGE_LAST_WRITE,
								&cbBytes,NULL,NULL);
		if(!ret) continue;		
		temp = pnotify;
		printf("File Changed!\n");
		switch(temp->Action)
		{
			case FILE_ACTION_MODIFIED :
				printf("File Modified!!\n");
				break;
			case FILE_ACTION_RENAMED_OLD_NAME: 
				printf("Filename Changed!\n");
				break;
		}
	}
	
	return 0;
}

DWORD WINAPI monitorThread(LPVOID params)
{
	dirMonitor();
	return 0;
}
	
int main(void)
{
	DWORD tId;
	HANDLE hThread;
	LPVOID params;
	hThread = CreateThread(NULL,0,monitorThread,params,0,&tId);
	if(hThread == NULL)
	{
		printf("Thread Failed!\n");
		return 1;
	}
	WaitForSingleObject(hThread,INFINITE);
	return 0;
}
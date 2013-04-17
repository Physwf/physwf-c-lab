// PswTool.cpp : 定义控制台应用程序的入口点。
//
#define UNICODE 1
#include "stdafx.h"
void CharToTchar (const char * _char, TCHAR * tchar)  
{  
    int iLength ;  
  
    iLength = MultiByteToWideChar (CP_ACP, 0, _char, strlen (_char) + 1, NULL, 0) ;  
    MultiByteToWideChar (CP_ACP, 0, _char, strlen (_char) + 1, tchar, iLength) ;  
}  
// 目录数据段[标志位+nameLen][name]
// 文件数据段[标志位+nameLen][name][date]
DWORD ListAllFiles(TCHAR* szDir,HANDLE hFile)
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;
	TCHAR szFind[MAX_PATH];
	TCHAR szFullPath[MAX_PATH];
	TCHAR szFileName[MAX_PATH];
	//_tprintf (TEXT("szDir:%s\n"), szDir);
	lstrcpy(szFind,szDir);  
    lstrcat(szFind,TEXT("\\*"));  
	//_tprintf (TEXT("szFind:%s\n"), szFind);
	hFind = FindFirstFile(szFind, &FindFileData);
	UINT32 error = 0;
	if (hFind == INVALID_HANDLE_VALUE) 
	{
		return GetLastError();
	} 
	else 
	{
		do
		{
			;
			if( lstrcmp(FindFileData.cFileName,TEXT(".")) == 0  || lstrcmp(FindFileData.cFileName,TEXT("..")) == 0 )
			{
				//printf("<..>\n");
				continue;
			}
			
			wsprintf(szFileName,TEXT("%s"),FindFileData.cFileName);
			wsprintf(szFullPath,TEXT("%s\\%s"),szDir,FindFileData.cFileName);
			printf("%s\n",szFileName);
			//_tprintf (TEXT("FullPath:%s\n"), szFullPath);
			//_tprintf (TEXT("FileName:%s\n"), FindFileData.cFileName);
			if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				printf("<DIR>%s\n",FindFileData.cFileName);
				DWORD nBytes;
				char * dirName = (char*) FindFileData.cFileName;
				DWORD a=0xFEFF;
				WriteFile(hFile,&a,sizeof(a),&nBytes,NULL);//这里sizeof(a),就修改为 2 因为只占2个字节。
				WriteFile(hFile,dirName,sizeof(dirName),&nBytes,NULL);
				ListAllFiles(szFullPath,hFile);
			}
			else
			{
				//_tprintf (TEXT("FullPath:%s\n"), szFullPath);
				//_tprintf (TEXT("FileName:%s\n"), FindFileData.cFileName);
			}

			//error = GetLastError();
			if(error == ERROR_NO_MORE_FILES)
			{
				_tprintf (TEXT("No more files!\n"));
				error = 0;
				return 0;
			}
					
		}
		while(FindNextFile(hFind,&FindFileData));
		FindClose(hFind);
		return 0;
   }
}

void _tmain(int argc, TCHAR *argv[])
{
  
	LPTSTR shellDir = TEXT("E:\\physwf-flash-lab\\FbProj\\PswGame\\PswGame_Shell\\resource");
	LPCTSTR keyDir = L"C://Users//joe//Desktop//key.txt";
	TCHAR szPath[MAX_PATH];
	HANDLE hFile = CreateFile(keyDir,GENERIC_WRITE,FILE_SHARE_READ,NULL,CREATE_NEW|OPEN_EXISTING,NULL,NULL);
	if(hFile == INVALID_HANDLE_VALUE)
	{
		printf("can't create file");
		getchar();
	}
	if( argc != 2 )
	{
		_tprintf(TEXT("Usage: %s [target_file]\n"), argv[0]);
		//return;
	}

	_tprintf (TEXT("Target file is %s\n"), shellDir);
	
	ListAllFiles(shellDir,hFile);
	getchar();
}

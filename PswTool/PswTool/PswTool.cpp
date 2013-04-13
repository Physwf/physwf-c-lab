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

DWORD ListAllFiles(TCHAR* szDir)
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;
	TCHAR szFind[MAX_PATH];
	TCHAR szFullPath[MAX_PATH];
	_tprintf (TEXT("szDir:%s\n"), szDir);
	lstrcpy(szFind,szDir);  
    lstrcat(szFind,TEXT("\\*"));  
	_tprintf (TEXT("szFind:%s\n"), szFind);
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
				printf("<..>\n");
				continue;
			}
			wsprintf(szFullPath,TEXT("%s\\%s"),szDir,FindFileData.cFileName);
			_tprintf (TEXT("FullPath:%s\n"), szFullPath);
			_tprintf (TEXT("FileName:%s\n"), FindFileData.cFileName);
			if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				printf("<DIR>\n");
				ListAllFiles(szFullPath);
			}
			else
			{
				_tprintf (TEXT("The first file found is %s\n"), FindFileData.cFileName);
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
  
   const char *shellDir = "F:\\physwf-flash-lab\\FbProj\\PswGame\\PswGame_Shell\\resource\\effects\\*";
   TCHAR szPath[MAX_PATH];
   CharToTchar(shellDir,szPath);
   if( argc != 2 )
   {
      _tprintf(TEXT("Usage: %s [target_file]\n"), argv[0]);
      return;
   }

   _tprintf (TEXT("Target file is %s\n"), argv[1]);

   ListAllFiles(argv[1]);
}

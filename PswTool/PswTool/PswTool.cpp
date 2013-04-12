// PswTool.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	LPSTR sehllDir = "E:\\physwf-flash-lab\\FbProj\\PswGame\\PswGame_Shell\\resource\\effects\\*.*";
	WIN32_FIND_DATA findData;
	HANDLE hFirstFile;
	UINT32 errorcode;
	hFirstFile = FindFirstFile((LPCTSTR)sehllDir,&findData);
	
	if(!hFirstFile) return 0;

	if(hFirstFile)
	{
		do
		{
			printf("%u\t\n",findData.ftCreationTime);
			FindNextFile(hFirstFile,&findData);
			errorcode=GetLastError();
			printf("%u\t\n",errorcode);
			printf("%u\t\n",ERROR_NO_MORE_FILES);
		}
		while(hFirstFile!=INVALID_HANDLE_VALUE && errorcode!=ERROR_NO_MORE_FILES);
	}
	getchar();
	return 0;
}


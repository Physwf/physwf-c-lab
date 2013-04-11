// PswTool.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	LPSTR sehllDir = "E:\\SkyDrive\\文档\\";
	WIN32_FIND_DATA * findData = NULL;
	HANDLE hFirstFile;

	hFirstFile = FindFirstFile(sehllDir,findData);
	
	if(!hFirstFile) return 0;

	if(hFirstFile)
	{
		do
		{
			printf("%s\t\t",findData->cFileName);
		}
		while(FindNextFile(hFirstFile,findData));
	}
	return 0;
}


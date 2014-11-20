#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <stdlib.h>
#pragma   comment   (linker,   "/ENTRY:mainCRTStartup ") 
#pragma   comment   (linker,   "/subsystem:windows ") 

/*功能：删除字符串中指定的字符
  参数：str中存放字符串
       remove中存放要删除的字符
*/
int RemoveChars(char str[],const char substr[])
{
    char const * subP;
    char *strP;
    char *temp;
    int flag = TRUE;

    strP = str;
    if((!*str) || *substr == '\0')/***如果主串为空或子串为空字符串，则返回*/
        return FALSE;

    while(*strP)
    {        
        temp = strP;
        for(subP=substr; *subP; subP++)
        {
            if(*strP == *subP)/***如果当前的主串和子串字符相等*/
            {
                strP++;/**//***则主串指针向前移一个字符*/
                flag = FALSE;/**//*设置为false，防止后续的主串指针，重复移动*/
                continue;
            }
            break;
        }
        
        if(*subP == '\0') /***如果subP指向末尾的'\0'则表示子串匹配成功*/
        {
            while(*temp++ = *strP++)/***进行字符复制*/
                ;/***空语句*/
            break;
        }
        if(flag)
            strP++;
    }
    return TRUE;
}

void main()
{
	// AllocConsole();
	// freopen("conin$", "r+t", stdin);   
	// freopen("conout$", "w+t", stdout);   
	// freopen("conout$", "w+t", stderr);
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;
	int argc; 
	TCHAR SourceFilePath[MAX_PATH];
	TCHAR InstallPath[MAX_PATH];
	TCHAR TargetPath[MAX_PATH];
	// lstrcpy(SourceFilePath, TEXT("../svnLog/*.txt"));
	
	// GetCurrentDirectory(MAX_PATH,InstallPath);
	GetModuleFileName(NULL,InstallPath,MAX_PATH);
	RemoveChars(InstallPath,"bin\\rename.exe");
	printf(InstallPath);
	sprintf(SourceFilePath,"%s%s", InstallPath,"svnLog\\*.txt");
	printf(SourceFilePath);
	
	// system("pause");
	hFind = FindFirstFile(SourceFilePath, &FindFileData);
	if (hFind == INVALID_HANDLE_VALUE) 
	{
	  printf ("FindFirstFile failed (%d)\n", GetLastError());
	  // system("pause");
	  return;
	} 
	else 
	{
	  _tprintf (TEXT("The first file found is %s\n"), FindFileData.cFileName);
	  TCHAR * s = "2.txt";
		SYSTEMTIME time;
		GetLocalTime(&time);
		// printf("%d",time.wYear);
		// char *n;
		sprintf(TargetPath,"%s%s%d%s%d%s%d%s%d%s%d%s%d%s", InstallPath , "svnLog\\",time.wYear,"-", time.wMonth,"-", time.wDay,"-",time.wHour,"-",time.wMinute,"-",time.wSecond,".txt");
		// sprintf(InstallPath,"%s%s", "../svnLog/",FindFileData.cFileName);
		sprintf(SourceFilePath,"%s%s%s", InstallPath , "svnLog\\", FindFileData.cFileName);
		printf(SourceFilePath);
		printf("\n");
		printf(TargetPath);
	  int ret = MoveFile((LPSTR)SourceFilePath,(LPSTR)TargetPath); 
	  printf("%d",ret);
	  // system("pause");
	  FindClose(hFind);
	}
	
	// if(lstrcmp(FindFileData.cFileName,TEXT("snn")) == 0 )
	// {
		// FindNextFile(hFind,&FindFileData);
		// printf("%s\n",FindFileData.cFileName);
		// system("pause");
		// lstrcpy(argv, TEXT("svnLog"));
		// hFind = FindFirstFile(argv,&FindFileData);
		// hFind = FindFirstFile(FindFileData.cFileName,&FindFileData);
		
		// if (hFind == INVALID_HANDLE_VALUE) 
		// {
		  // printf ("FFindFirstFile failed (%d)\n", GetLastError());
		  // system("pause");
		  // return;
		// } 
		// FindNextFile(hFind,&FindFileData);
		// printf("%s\n",FindFileData.cFileName);
		// TCHAR * s = "2.txt";
		// MoveFile(FindFileData.cFileName,(LPSTR)s);
		// printf("success");

	// }
			

	// printf("haha%s\n",FindFileData.cFileName);
	// system("pause");
	
}

// GetLocalTime(&st);
// sprintf(msg,"%0.4d %0.2d %0.2d %0.2d %0.2d",st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute);
// printf(msg);
// MovieFile(fileinfo.cFileName,msg);
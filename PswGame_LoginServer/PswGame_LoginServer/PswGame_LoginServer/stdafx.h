// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#include "targetver.h"

#include <winsock2.h>
#include <windows.h> 
#include <stdio.h>
#include <tchar.h>
#include <odbcinst.h>
#include <sql.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <sqlucode.h>
#include <odbcss.h>
/*
1���ڳ���ͷ�����ϣ�#pragma comment(lib, "xxx.lib")����Ҫ�ӷֺŽ�����
2������--����--����--����/��ģ���м����Ǹ�lib
*/
#pragma comment(lib,"user32.lib")
#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib,"odbc32.lib")
#pragma comment(lib,"Kernel32.lib")

// TODO: �ڴ˴����ó�����Ҫ������ͷ�ļ�

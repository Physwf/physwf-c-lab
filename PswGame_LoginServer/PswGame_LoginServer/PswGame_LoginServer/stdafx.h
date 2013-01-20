// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
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
1：在程序头部加上：#pragma comment(lib, "xxx.lib")不须要加分号结束。
2。工程--设置--连接--对像/库模块中加入那个lib
*/
#pragma comment(lib,"user32.lib")
#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib,"odbc32.lib")
#pragma comment(lib,"Kernel32.lib")

// TODO: 在此处引用程序需要的其他头文件

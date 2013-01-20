#pragma once

// 包括 SDKDDKVer.h 将定义最高版本的可用 Windows 平台。

// 如果要为以前的 Windows 平台生成应用程序，请包括 WinSDKVer.h，并将
// WIN32_WINNT 宏设置为要支持的平台，然后再包括 SDKDDKVer.h。
#ifndef WINVER // 指定要求的最低平台是 Windows Vista。
#define WINVER 0x0501 // 将此值更改为相应的值，以适用于 Windows 的其他版本。
#endif

#ifndef _WIN32_WINNT // 指定要求的最低平台是 Windows Vista。
#define _WIN32_WINNT 0x0501 // 将此值更改为相应的值，以适用于 Windows 的其他版本。
#endif
#include <SDKDDKVer.h>
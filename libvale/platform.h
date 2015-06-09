#ifndef _VALE_PLATFORM_H
#define _VALE_PLATFORM_H 

#if defined(_USRDLL)
	#define VALE_DLL __declspec(dllexport)
	#define EXPIMP_TEMPLATE
#else
	#define VALE_DLL _declspec(dllimport)
	#define EXPIMP_TEMPLATE extern
#endif

#endif
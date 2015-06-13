#ifndef _LOG_H
#define _LOG_H

#include <stdarg.h>
#include <stdio.h>

#include "platform.h"

class VALE_DLL Log
{
public:
	Log();
	~Log();
public:
	static void initialize();
	static void fatal(const char* format,...);
	static void error(const char* format, ...);
	static void warn(const char* format, ...);
	static void info(const char* format, ...);
	static void debug(const char* format, ...);
	static void trace(const char* format, ...);
private:
	enum Level {
		LFATAL,
		LERROR,
		LWARN,
		LINFO,
		LDEBUG,
		LTRACE
	};
private:
	static void log(Level level,const char* format, va_list args);

};
#endif
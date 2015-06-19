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
#ifdef DEBUG
#define LOG_FATAL(format,...) Log::fatal(format,__VA_ARGS__)
#define LOG_ERROR(format,...) Log::error(format,__VA_ARGS__)
#define LOG_WARN(format,...) Log::warn(format,__VA_ARGS__)
#define LOG_INFO(format,...) Log::info(format,__VA_ARGS__)
#define LOG_DEBUG(format,...) Log::debug(format,__VA_ARGS__)
#define LOG_TRACE(format,...) Log::trace(format,__VA_ARGS__)
#else
#define LOG_FATAL(format,...)
#define LOG_ERROR(format,...)
#define LOG_WARN(format,...)
#define LOG_INFO(format,...)
#define LOG_DEBUG(format,...)
#define LOG_TRACE(format,...)
//#define LOG_FATAL(format,...) (#ifdef DEBUG Log::fatal(format,__VA_ARGS__); #endif)
//#define LOG_DEBUG(format,...) (#ifdef DEBUG Log::debug(format,__VA_ARGS__); #endif)
#endif
#endif
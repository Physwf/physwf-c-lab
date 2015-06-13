#include "Log.h"

Log::Log()
{

}

Log::~Log()
{

}

void Log::initialize()
{

}

void Log::fatal(const char* format, ...)
{
	va_list args;
	va_start(args, format);
	log(LFATAL, format, args);
	va_end(args);
}

void Log::error(const char* format, ...)
{

}

void Log::warn(const char* format, ...)
{

}

void Log::info(const char* format, ...)
{
	va_list args;
	va_start(args, format);
	log(LINFO, format, args);
	va_end(args);
}

void Log::debug(const char* format, ...)
{
	va_list args;
	va_start(args, format);
	log(LDEBUG, format, args);
	va_end(args);
}

void Log::trace(const char* format, ...)
{

}

void Log::log(Level level, const char* format, va_list args)
{
	switch (level)
	{
	case Log::LFATAL:
		printf("[Fatal] ");
		break;
	case Log::LERROR:
		printf("[Error] ");
		break;
	case Log::LWARN:
		printf("[Warning] ");
		break;
	case Log::LINFO:
		printf("[Info] ");
		break;
	case Log::LDEBUG:
		printf("[Debug] ");
		break;
	case Log::LTRACE:
		printf("[Trace] ");
		break;
	default:
		break;
	}
	vprintf(format, args);
	printf("\n");
}


#include <stdio.h>
#include <stdarg.h>

class Log {
	public:
		static void init(const char* filename);
		static void info(const char* format, ...);
		static void fatal(const char* format, ...);
		static void log(const char* format, ...);
		static void close();
	private:
		static FILE* mStream;
};
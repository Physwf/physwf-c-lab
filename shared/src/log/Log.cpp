#include <log/Log.h>

void Log::init(const char* filename)
{
	if( (mStream = fopen(filename,"wb")) == NULL){
		printf("Open file: %s failed!\n",filename);
	}
};

void Log::close()
{
	if(mStream)
		fclose(mStream);
};

void Log::info(const char* format, ...)
{
	if(mStream) {
		va_list args;
		va_start(args, format);
		vfprintf(mStream, format, args);
		vfprintf(mStream, "\n", args);
		fflush(mStream);
		va_end(args);
	}
};

void Log::fatal(const char* format, ...)
{

};

void Log::log(const char* format, ...)
{

};


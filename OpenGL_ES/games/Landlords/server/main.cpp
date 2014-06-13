#include "game.h"
#include <log/Log.h>

FILE* Log::mStream = NULL;

int main()
{
	Log::init("LLserver.log");
	init();
	return 0;
}
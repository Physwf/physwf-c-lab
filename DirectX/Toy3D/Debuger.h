#ifndef _DEBUGER_H_
#define _DEBUGER_H_

#include <DxErr.h>
#include <windows.h>
#include <sstream>

namespace Toy3D
{
	template <typename T> void Debug_Trace(T t)
	{
		std::stringstream str;
		str << t;
		DXTRACE_MSG(str.str().c_str());
	}
}
#endif
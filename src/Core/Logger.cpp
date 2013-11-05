#include "AKLogger.h"
#include <stdarg.h>

namespace ACTK
{
	const int MAX_DEBUG_LINE_LEN = 1024;

	// Helper function designed to push and pop
	EventLogFN::EventLogFN(const char* function, ...)
	{
		char buffer[MAX_DEBUG_LINE_LEN];
		va_list args; 
		va_start(args, function);

		#if defined(WINVER) || defined(_XBOX)
			int buf = _vsnprintf_s(buffer, MAX_DEBUG_LINE_LEN, function, args); 
		#else
			int buf = vsnprintf(buffer, MAX_DEBUG_LINE_LEN, function, args); 
		#endif

		va_end(args);

		EventLogger::GetInstance().pushFunction(buffer);
	}

	EventLogFN::~EventLogFN()
	{
		EventLogger::GetInstance().popFunction();
	}

}
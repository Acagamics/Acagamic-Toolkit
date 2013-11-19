#include "AKLogger.h"
#include <stdarg.h>
#include <memory>
#include <assert.h>
#include <cstring>
#include <string>
#include <iostream>

#ifdef _WIN32
#include <Windows.h>
#endif

namespace ACTK
{
	static std::shared_ptr<EventLogger> Instance;

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

	EventLogger::EventLogger()
	{
		m_loggedEvent = false;
		m_initialized = false;
		m_previousStackLevel = 0;
		m_callStack.reserve(32);
	}

	EventLogger::~EventLogger()
	{
		release();
	}

	void EventLogger::SetInstance(EventLogger& logger)
	{
		Instance = std::shared_ptr<EventLogger>(&logger, [](EventLogger* ptr){});
	}

	EventLogger& EventLogger::GetInstance()
	{
		if(Instance.get() == nullptr)
		{
			Instance = std::shared_ptr<EventLogger>(new EventLogger());
			Instance->init(std::string("Log.txt").c_str());
		}
		return *Instance.get();
	}

	// Initialize stereaming file
	void EventLogger::initLogFile()
	{
		m_logStream.open("Log.txt", std::fstream::out);

		if (m_logStream.is_open())
		{
			m_logStream.clear();
		}
	}


	// Initialize and shut down the event logging system
	bool EventLogger::init(const char* logName)
	{
		if(isInitialized())
			return false;

		// ToDo: STREAMING DATEI ÖFFNEN UND LEEREN
		initLogFile();

		m_initialized = true;
		m_loggedEvent = true;
		m_previousStackLevel = 0;

		return true;
	}

	void EventLogger::release()
	{
		// ToDo: DATEI SCHLIEßEN UND FREIGEBEN
		m_logStream.close();

		m_initialized = false;
	}

	void EventLogger::logInfo(const char* text, ...)
	{
		if(!isInitialized())
			return;
		char buffer[MAX_DEBUG_LINE_LEN];
		va_list args; 
		va_start(args, text);

	#if defined(WINVER) || defined(_XBOX)
		int buf = _vsnprintf_s(buffer, MAX_DEBUG_LINE_LEN, text, args); 
	#else
		int buf = vsnprintf(buffer, MAX_DEBUG_LINE_LEN, text, args); 
	#endif

		assert((buf >= 0) && (buf < MAX_DEBUG_LINE_LEN)); 
		va_end(args);

		// Log output to debug windows and/or disk depending on options
		logOutput(buffer, 0);
	}


    void EventLogger::logInit(const char* text, ...)
	{
		if(!isInitialized())
			return;
		char buffer[MAX_DEBUG_LINE_LEN];
		va_list args; 
		va_start(args, text);

	#if defined(WINVER) || defined(_XBOX)
		int buf = _vsnprintf_s(buffer, MAX_DEBUG_LINE_LEN, text, args); 
	#else
		int buf = vsnprintf(buffer, MAX_DEBUG_LINE_LEN, text, args); 
	#endif

		assert((buf >= 0) && (buf < MAX_DEBUG_LINE_LEN)); 
		va_end(args);

		// Log output to debug windows and/or disk depending on options
		logOutput(buffer, 0);
	}

    void EventLogger::logError(const char* text, ...)
	{
		if(!isInitialized())
			return;
		char buffer[MAX_DEBUG_LINE_LEN];
		va_list args; 
		va_start(args, text);

	#if defined(WINVER) || defined(_XBOX)
		int buf = _vsnprintf_s(buffer, MAX_DEBUG_LINE_LEN, text, args); 
	#else
		int buf = vsnprintf(buffer, MAX_DEBUG_LINE_LEN, text, args); 
	#endif

		assert((buf >= 0) && (buf < MAX_DEBUG_LINE_LEN)); 
		va_end(args);

		// Log output to debug windows and/or disk depending on options
		logOutput(buffer, 0);
	}

	void EventLogger::logAssert(bool contidion, const char* file, long line, const char* description)
	{
		if(!contidion)
		{
			logError(std::string(std::string(description) + std::string(" - in file %s at line %u.")).c_str(), file, line);
			
			#ifdef _DEBUG
				assert(contidion);
			#endif
		}
	}

	void EventLogger::pushFunction(const char* name) 
	{
		if(!isInitialized())
			return;
		m_callStack.push_back(name); 
	}

	void EventLogger::popFunction()
	{
		if(!isInitialized() || m_callStack.empty())
			return;
		m_callStack.pop_back();
		if(m_previousStackLevel >= m_callStack.size())
			logCallStack();
	}


	////////////////////////////////////
	// Common logging functions
	void EventLogger::logOutput(char* buffer, unsigned int flags)
	{
		// Strip any unnecessary newline characters at the end of the buffer
        int i = strlen(buffer);
		if(i == 0)
			return;
		if(buffer[i - 1] == '\n')
			buffer[i - 1] = 0;


		// Indicate that we have some info to print, so write the stack info
		m_loggedEvent = true;

		// Update the call stack output
		logCallStack();

		//  HIER DEN INHALT VON BUFFER IN DIE DATEI SCHREIBEN
		m_logStream << buffer << '\n';

		debugOutput(buffer);
	}


	void EventLogger::logCallStack()
	{
		unsigned int currentStackLevel = m_callStack.size();

		while(m_previousStackLevel < currentStackLevel)
		{
			m_previousStackLevel++;
		}

		while(m_previousStackLevel > currentStackLevel)
		{
			m_previousStackLevel--;
		}
    
	}

	////////////////////////////////////
	// Debug output functions
	void EventLogger::debugOutput(const char* buffer)
	{
#ifdef _WIN32
		char buf[MAX_DEBUG_LINE_LEN];
        sprintf_s(buf, "%s\n", buffer);
		std::cout << buf;
		OutputDebugString(buf);
#endif
	}

}

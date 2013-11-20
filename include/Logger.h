#pragma once
#include <vector>
#include <fstream>

// Low Loglevel means that less important logs will be displayed
#ifndef LOG_LEVEL
	#ifdef _DEBUG
		#define LOG_LEVEL	0
	#else
		#define LOG_LEVEL	2
	#endif
#endif

#if LOG_LEVEL < 1
	#define LOG_INFO	ACTK::EventLogger::GetInstance().logInfo
#else
	#define LOG_INFO
#endif

#if LOG_LEVEL < 2
	#define LOG_INIT	ACTK::EventLogger::GetInstance().logInit
#else
	#define LOG_INIT
#endif

#if LOG_LEVEL < 3
	#define LOG_ERROR	ACTK::EventLogger::GetInstance().logError
#else
	#define LOG_ERROR
#endif

#define LOG_FATAL(var_1)			ACTK::EventLogger::GetInstance().logAssert(false, __FILE__, __LINE__, var_1)
#define LOG_ASSERT(var_1, var_2)	ACTK::EventLogger::GetInstance().logAssert(var_1, __FILE__, __LINE__, var_2)

namespace ACTK
{
	//----------------------------------------------------------------------------
    // EventLogger
    //----------------------------------------------------------------------------
	class EventLogger
	{
    protected:
        EventLogger();

    private:
		EventLogger( const EventLogger& ){}; // You shall not copy
        EventLogger& operator=( const EventLogger& ) {return *this;}

	public:
		static void SetInstance(EventLogger&);
		static EventLogger& GetInstance();

		~EventLogger();

		// Initialize and shut down the event logging system

		// Initialize log file
		void initLogFile();

		// Stream-Datei laden, die beschrieben wird
        bool init(const char* logName);

		// Stream-Datei freigeben
        void release();

		// Is the event logging system initialized?
        bool isInitialized() { return m_initialized; }

		// Log in die Datei schreiben (Die ... Notation kann man von EventLogFN übernehmen)
        void logInfo(const char* text, ...);
		void logInit(const char* text, ...);
        void logError(const char* text, ...);
		void logAssert(bool contidion, const char* file, long line, const char* description);

	private:
        void logOutput(char* buffer, unsigned int flags);

        // Debug output function
        void debugOutput(const char* buffer);

        bool            m_loggedEvent;
        unsigned int    m_previousStackLevel;
        bool            m_initialized;
		std::ofstream   m_logStream;
	};
}
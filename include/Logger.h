#pragma once
#include <vector>
#include <fstream>

// Chose one of this LogLevels to define LOG_LEVEL
#define LOG_LEVEL_ALL 0
#define LOG_LEVEL_DEBUG 1
#define LOG_LEVEL_WARNING 2
#define LOG_LEVEL_ERROR 3
#define LOG_LEVEL_OFF 5

// Low Loglevel means that less important logs will be displayed
#ifndef LOG_LEVEL
	#ifdef _DEBUG
		#define LOG_LEVEL	LOG_LEVEL_DEBUG
	#else
		#define LOG_LEVEL	LOG_LEVEL_ERROR
	#endif
#endif

#if LOG_LEVEL <= LOG_LEVEL_DEBUG
	#define LOG_DEBUG	ACTK::EventLogger::GetInstance().logDebug
#else
	#define LOG_DEBUG
#endif

#if LOG_LEVEL <= LOG_LEVEL_WARNING
	#define LOG_WARNING	ACTK::EventLogger::GetInstance().logWarning
#else
	#define LOG_WARNING
#endif

#if LOG_LEVEL <= LOG_LEVEL_ERROR
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
        void logDebug(const char* text, ...);
		void logWarning(const char* text, ...);
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
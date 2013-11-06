#pragma once
#include "ACTK.h"
#include <vector>

#define LOG_LEVEL		0
#define FN				ACTK::EventLogFN obj____unique_name

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
	// Helper function designed to push and pop
    class EventLogFN
    {
    public:
		// EcentLogFN("Klasse::Funktion(%s, %u)", "FooBar", 50);
        EventLogFN(const char* function, ...);
        ~EventLogFN();
    };

	// "stack" typedef
    typedef std::vector<const char*> CharPtrVec;

	#define LOG_SIZE_LARGE      0x00000040
    #define LOG_SIZE_SMALL      0x00000080

    #define LOG_BOLD            0x00000100
    #define LOG_ITALICS         0x00000200
    #define LOG_UNDERLINE       0x00000400

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
		static EventLogger& SetInstance(const EventLogger&);
		static EventLogger& GetInstance();

		~EventLogger();

		// Initialize and shut down the event logging system

		// ToDo: Stream-Datei laden, die beschrieben wird
        bool init(const char* logName);

		// ToDo: Stream-Datei freigeben
        void release();

		// Is the event logging system initialized?
        bool isInitialized() { return m_initialized; }

		// Log an event (with or without formatting flags)

		// ToDo: Log in die Datei schreiben (Die ... Notation kann man von EventLogFN übernehmen)
        void logInfo(const char* text, ...);
		void logInit(const char* text, ...);
        void logError(const char* text, ...);
		void logAssert(bool contidion, const char* file, long line, const char* description);

		// Push a function onto the call stack
        void pushFunction(const char* name);
        // Pop a function off the call stack
        void popFunction();

	private:
        void logOutput(char* buffer, unsigned int flags);
        void logCallStack();

        // Debug output function
        void debugOutput(const char* buffer);

		CharPtrVec		m_callStack;
        bool            m_loggedEvent;
        unsigned int    m_previousStackLevel;
        bool            m_initialized;
	};
}
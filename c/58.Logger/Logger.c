#include "Logger.h"
#include "LogConfig.h"

#include <stdlib.h>				/* atexit */
#include <stdio.h>				/* FILE, fopen, fwrite, fclose */

#include <sys/syscall.h>		/* syscall(SYS_gettid) */
#include <sys/types.h>			/* getpid */
#include <unistd.h>				/* getpid */

#include <sys/time.h>			/* gettimeofday */
#include <time.h>				/* struct* tm, localtime, strftime */
#include <string.h>				/* strlen */

/* #define NDEBUG 1 */
#include <assert.h>

#define LOG_FORMAT_BUFFER_SIZE		1024
#define TIME_STAMP_BUFFER_SIZE		32
/* converts "LOG_​DEBUG" to "D" */
#define LOG_LEVEL_LETTER(L)			L[4]

static Log* g_log = NULL;
/* 2016-4-29​ 22:43:20.244​ 40059​ 1299​ I query​​ dequeue@reader.c:9​ Queued​ tasks: 4 */
static char g_logFormat[] = "%s %d %ld %c %s %s@%s:%d %s\n";


struct Log
{
	FILE*  m_logFilePtr;
	pid_t  m_pid;			/**< Process unique ID */
	Config m_config;		/**< Structure to be passed to GetConfig */
};


static Log*  LogCreate(char* _configFileName);
static void  LogDestroy(Log** _log);
static void  LogClose();
static void  GetTimeStampString(char*_buffer, size_t _bufferSize);
static void  LogFormat(char* _buffer, pid_t _pid, int _level, char* _moduleName, const char* _functionName,
						char* _fileName, int _lineNum, char* _message);
static int   a2i(char* _str);
static char  i2a(int _i);


Log* GetLog(char* _configFileName)
{
	return (g_log) ? g_log : LogCreate(_configFileName);
}

void LogWrite(Log* _log, int _level, const char* _functionName,
			  char* _fileName, int _lineNum, char* _message)
{
	static char buffer[LOG_FORMAT_BUFFER_SIZE];		/* Not thread safe! */
	
	assert(_log);
	
	if (_level < a2i(_log->m_config.m_level))
	{
		return;
	}

	LogFormat(buffer, _log->m_pid, _level, _log->m_config.m_moduleName,
				_functionName, _fileName, _lineNum, _message);

	fwrite(buffer, 1, strlen(buffer), _log->m_logFilePtr);
}

/* A callback function to be executed on exit */
void LogClose()
{
	if (g_log)
	{
		LogDestroy(&g_log);
	}
}

static Log* LogCreate(char* _configFileName)
{
	g_log = malloc(sizeof(Log));
	if(!g_log)
	{
		return NULL;
	}
	
	GetConfig(_configFileName, &g_log->m_config);
	
	if(NULL == (g_log->m_logFilePtr = fopen(g_log->m_config.m_logFileName, "a")))
	{
		free(g_log);
		return NULL;
	}	
	
	/* returns 0 if successful; nonzero otherwise */
	atexit(LogClose);

	g_log->m_pid = getpid();

	return g_log;
}

static void LogDestroy(Log** _log)
{	
	/*LOG_WRITE(*_log, "Logger", "Destroying log");*/
	
	fclose((*_log)->m_logFilePtr);
	free(*_log);

	*_log = NULL;
}


/**
 * log entery example:
 * 2016-4-29​ 22:43:20.244​ 40059​ 1299​ I query​​ dequeue@reader.c:9​ Queued​ tasks: 4
 */
static void LogFormat(char* _buffer, pid_t _pid, int _level, char* _moduleName, const char* _functionName,
					  char* _fileName, int _lineNum, char* _message)
{
	char timeStampBuffer[TIME_STAMP_BUFFER_SIZE];
	
	GetTimeStampString(timeStampBuffer, TIME_STAMP_BUFFER_SIZE);

	snprintf(_buffer, LOG_FORMAT_BUFFER_SIZE, g_logFormat,
				timeStampBuffer, _pid, syscall(SYS_gettid), i2a(_level), _moduleName,
				_functionName, _fileName, _lineNum, _message);
}

/**
 * @brief Obtains current time and date and copies it to a destination array 
 *			in the form of a string in the foloowing format: 2017-08-17 19:45:44.763
 */
static void GetTimeStampString(char*_buffer, size_t _bufferSize)
{
	struct timeval tv;		/* Contains the number of seconds and microseconds since the Epoch. */
    struct tm* tm_info;
	long   milliseconds;

    assert(_buffer);
    assert(_bufferSize);

	gettimeofday(&tv, NULL);
	/* Convert to a tm struct. */
	tm_info = localtime(&tv.tv_sec);

    strftime(_buffer, _bufferSize, "%Y-%m-%d %H:%M:%S", tm_info);
	
	milliseconds = tv.tv_usec / 1000;

 	sprintf(_buffer, "%s.%03ld", _buffer, milliseconds);
}

static char i2a(int _i)
{
	static char lut[] = {'T', 'D', 'I', 'W', 'E', 'C', 'S', 'F'};
	
	assert(_i >= 0);
	assert(_i <= 7);
	
	return lut[_i];
}

/**
 * @brief get the enum value of the log level string
 * @details Instead of using lut like this:
 *			{"LOG_TRACE", "LOG_DEBUG", "LOG_INFO", "LOG_WARNING", "LOG_ERROR",
 *			"LOG_CRITICAL", "LOG_SEVERE", "LOG_FATAL", "LOG_NONE"};
 *			to get the enum value of the string, we can use	a hash table
 *			and have O(1) complexity.
 * @return log level
 *
 * Example: "LOG_DEBUG" ==> "D" ==> 3 ==> 1
 */
static int a2i(char* _str)
{
	static int hashTable[26] = {0, 0, 5, 1, 4, 7, 0, 0, 2, 0, 0, 0, 0, 8,
									0, 0, 0, 6, 0, 0, 0, 0, 3, 0, 0, 0};
	assert(strlen(_str) >= 8);
	assert(strlen(_str) <= 12);
	
	return hashTable[LOG_LEVEL_LETTER(_str) - 'A'];
}






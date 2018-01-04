#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <stdio.h> /* sprintf */

/** 
 * @brief Implemet Logger module
 * @details the logger appends formated log enteries to a log file 
 *			the enteries contain user provided as well as automaticaly generated data
 *			the logger is automaticaly destroyd on exit
 * @author Author Ariel Davidov (arik.davidov@gmail.com) 
*/

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wvariadic-macros"

/**
 * @brief Write a new log entery to a log file
 * @details The macro recives the user provided parameters and expands to LogWrite function (see below)
 * 			adding the automaticaly generated parameters.
 * @param[in] LOG pointer to a user provided Log
 * @param[in] LEVEL log level of the current log entery
 * @param[in] MESSAGE formated message string
 * @param[in] ... additional arguments to be inserted to the MESSAGE
 */

#define LOG_WRITE(LOG, LEVEL, MESSAGE, ...) \
				  do{char str[1024]; sprintf(str, MESSAGE, ##__VA_ARGS__); \
				  LogWrite(LOG, LEVEL, __func__, __FILE__, __LINE__, str);} while(0)
				  
#pragma GCC diagnostic pop

typedef struct Log Log;

typedef enum
{
	LOG_TRACE = 0,	/**< Trace​ message​ usually​ very​ detailed			*/
	LOG_DEBUG,		/**< A​ message​ useful​ for​ debugging					*/
	LOG_INFO,		/**< Informative​ message							*/
	LOG_WARNING,	/**< Warning										*/
	LOG_ERROR,		/**< An​ error​ occurred								*/
	LOG_CRITICAL,	/**< Critical​ error									*/
	LOG_SEVERE,		/**< Server​ error​ requiring​ immediate​ intervention	*/
	LOG_FATAL,		/**< Fatal​ error​ signaling​ an​ emergency				*/
	LOG_NONE		/**< Used​ only​ in​ configuration​ file				*/
} Level;


/** 
 * @brief Obtain a pointer to a log, create a new log if not exist
 * @return pointer to a Log
 */
Log* GetLog();

/** 
 * @brief Write a new log entery to a log file
 * @details This function is not meant to be used directly by the user
 * 			The LOG_WRITE macro recives the user provided parameters and expands to this function
 * 			adding the automaticaly generated parameters.
 * 			log entery example:
 * 			2016-4-29​ 22:43:20.244​ 40059​ 1299​ I query​​ dequeue@reader.c:9​ Queued​ tasks: 4
 * @param[in] _log pointer to a user provided Log
 * @param[in] _level user provided level of the current log entery
 * @param[in] _functionName automaticly generated name of the current function
 * @param[in] _fileName automaticly generated name of the current source file
 * @param[in] _lineNum automaticly generated line number of the current source file
 * @param[in] _message automaticly generated from user provided formated message
 *						string and it's additional arguments
 * @return void
 * 
 * @warning Compile with -std=gnu99 flag.
 */
void LogWrite(Log* _log, int _level, const char* _functionName,
			  char* _fileName, int _lineNum, char* _message);

#endif	/* __LOGGER_H__ */











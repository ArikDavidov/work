#ifndef __LOG_CONFIG_H__
#define __LOG_CONFIG_H__

#define BUFFER_SIZE 128

typedef struct 
{
	char m_moduleName[BUFFER_SIZE];
	char m_level[BUFFER_SIZE];
	char m_logFilePath[BUFFER_SIZE];
	char m_logFileName[BUFFER_SIZE];
} Config;


/** 
 * @brief Obtain a pointer to a log, create a new log if not exist
 * @param[in] _configFilename pointer to a user provided Log
 * @param[in] _config pointer to a user provided Log
 * @return void
 */
void GetConfig(char* _configFilename, Config* _config);


#endif	/* __LOG_CONFIG_H__ */















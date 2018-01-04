#include "LogConfig.h"

#include <stdio.h>			/* FILE */
#include <string.h>			/* strcmp, strcpy */
#include <assert.h>			/* assert */

#define LOGGER_DEFAULT_MODULE		"#"
#define LOGGER_DEFAULT_LEVEL		"LOG_TRACE"
#define LOGGER_DEFAULT_FILE_PATH	"/home/arik/Desktop/work/58.Logger"
#define LOGGER_DEFAULT_FILE_NAME	"Logger.txt"

#define BUFFER_SIZE 128

static void ConfigParse(FILE* _fd, Config* _config);
static void ParseSettings(FILE* _fd, Config* _config);
static void FillMissingWithDefault(Config* _config);


void GetConfig(char* _configFileName, Config* _config)
{
	FILE* fd = NULL;
	
	assert(_config);
	
	if(NULL != (fd = fopen(_configFileName, "r")))
	{
		ConfigParse(fd, _config);
		fclose(fd);
	}
	
	FillMissingWithDefault(_config);
}

static void ConfigParse(FILE* _fd, Config* _config)
{
	char line[BUFFER_SIZE];
	char str[BUFFER_SIZE];
	
	assert(_fd);
	assert(_config);
	
	while(fgets(line , BUFFER_SIZE, _fd))
	{
		sscanf(line, " [%[^] ][^\n]", str);
		if (!strcmp(str, LOGGER_DEFAULT_MODULE))
		{
			ParseSettings(_fd, _config);
		}
	}
}

static void ParseSettings(FILE* _fd, Config* _config)
{
	char line[BUFFER_SIZE];
	char key[BUFFER_SIZE];
	char value[BUFFER_SIZE];

	assert(_fd);
	assert(_config);
	
	while(fgets(line , BUFFER_SIZE, _fd))
	{
		if (2 != sscanf(line, " %s = %s ", key, value))
		{
			break;
		}		

		if (!strcmp(key, "Level"))
		{
			strcpy(_config->m_level, value);
		} 
		else if (!strcmp(key, "Path"))
		{
			strcpy(_config->m_logFilePath, value);
		}
		else if (!strcmp(key, "File"))
		{
			strcpy(_config->m_logFileName, value);
		}
	}
}

static void FillMissingWithDefault(Config* _config)
{
	assert(_config);
	
	if (!_config->m_moduleName)
	{
		strcpy(_config->m_moduleName, LOGGER_DEFAULT_MODULE);
	}

	if (!_config->m_level)
	{
		strcpy(_config->m_level, LOGGER_DEFAULT_LEVEL);
	}

	if (!_config->m_logFilePath)
	{
		strcpy(_config->m_logFilePath, LOGGER_DEFAULT_FILE_PATH);
	}

	if (!_config->m_logFileName)
	{
		strcpy(_config->m_logFileName, LOGGER_DEFAULT_FILE_NAME);
	}
}








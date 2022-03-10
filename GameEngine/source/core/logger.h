#pragma once
#include <string>


enum LogType
{
	LOG_TYPE_UNKNOWN = 0x00,
	LOG_TYPE_INFO = 0x01,
	LOG_TYPE_WARNING = 0x02,
	LOG_TYPE_ERROR = 0x03,
	LOG_TYPE_CRITICAL = 0x04,
};

class Logger
{
public:
	static Logger* Create(const std::string& _filename);
	virtual ~Logger();

	static void Log(const std::string& _message, LogType _type);

protected:
	Logger();
};
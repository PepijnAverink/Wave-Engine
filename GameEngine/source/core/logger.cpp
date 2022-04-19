#include "stdafx.h"

Logger* Logger::Create(const std::string& _filename)
{
	return new Logger();
}

Logger::Logger()
{ }

Logger::~Logger()
{ }

void Logger::Log(const std::string& _message, LogType _type)
{
	switch (_type)
	{
	case LogType::LOG_TYPE_INFO:
		printf("[INFO] %s\n", _message.c_str());
		break;
	case LogType::LOG_TYPE_WARNING:
		printf("[WARNING] %s\n", _message.c_str());
		break;
	case LogType::LOG_TYPE_ERROR:
		printf("[ERROR] %s\n", _message.c_str());
		break;
	case LogType::LOG_TYPE_CRITICAL:
		printf("[Critical] %s\n", _message.c_str());
		break;
	}
}
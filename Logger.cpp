#include "Logger.h"
#include <time.h>
#include <ctime>
#include <iostream>

void Logger::LogInformation(const char* message, const char* className)
{
	Log(message, LogLevel::Info, className);
}

void Logger::LogError(const char* message, std::exception& exception, const char* className)
{
	std::string fullMessage = std::string(message) + " - Exception: " + exception.what();
	Log(fullMessage.c_str(), LogLevel::Error, className);
}

void Logger::LogError(const char* message, const char* className)
{	
	Log(message, LogLevel::Error, className);
}


void Logger::Log(const char* message, LogLevel level, const char* className)
{
	std::cout << "[" << GetCurrentUTCTime() << "]"
		<< "[" << LogLevelToString(level) << "]"
		<< (className ? "[" + std::string(className) + "]" : "")
		<< " " << message << std::endl;
}

std::string Logger::GetCurrentUTCTime()
{
	auto currentTime = std::time(0);
	tm utcTime;

	gmtime_s(&utcTime, &currentTime);
	char timeBuffer[26];
	asctime_s(timeBuffer, sizeof(timeBuffer), &utcTime);

	timeBuffer[strlen(timeBuffer) - 1] = '\0';
	return std::string(timeBuffer);
}

std::string Logger::LogLevelToString(LogLevel logLevel)
{
	switch (logLevel)
	{
		case Info:
			return "Info";		
		case Error:
			return "Error";
		default:
			return "Default";
	}
}

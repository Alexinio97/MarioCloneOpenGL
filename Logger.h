#pragma once
#include <string>

enum LogLevel {
	Info = 0,
	Error = 1
};


class Logger
{
public:
	// no need to declare nullptr again in method definitions Logger.cpp
	void LogInformation(const char* message, const char* className = nullptr);

	void LogError(const char* message, std::exception& exception, const char* className = nullptr);
	void LogError(const char* message, const char* className = nullptr);

private:
	void Log(const char* message, LogLevel level, const char* className = nullptr);
	std::string GetCurrentUTCTime();
	std::string LogLevelToString(LogLevel logLevel);
};




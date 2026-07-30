#pragma once
#include <string>
#include <iostream>

namespace logger
{
	enum class LogType
	{
		DEBUG,
		INFO,
		WARNING,
		ERROR
	};

	inline std::string prefix;

	inline void setPrefix(LogType logType) 
	{
		
		switch (logType)
		{
		case LogType::DEBUG:
			prefix = "[DEBUG]";
			break;
		case LogType::INFO:
			prefix = "[INFO]";
			break;
		case LogType::WARNING:
			prefix = "[WARNING]";
			break;
		case LogType::ERROR:
			prefix = "[ERROR]";
			break;
		default:
			prefix = "[INFO]";
			break;
		}
	}

	// Log a string message with a specified log type (default is INFO)
	inline void log(std::string message, LogType logType = LogType::INFO) 
	{
		setPrefix(logType);
		std::cout << prefix << "::| " << message << std::endl;
	}

	// Template function: Prints the value passed to it to the console
	template <typename T>
	inline void print(const T& value)
	{
		std::cout << value << std::endl;
	}
}
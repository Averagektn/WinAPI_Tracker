#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <windows.h>

class Logger
{
public:
	Logger(std::string filePath, char separator);
	~Logger();

	void LogLn(POINT point);
	void LogLn(POINTFLOAT point);
	void LogLn(std::string info);

	void Log(POINT point);
	void Log(POINTFLOAT point);
	void Log(std::string info);
protected:
	std::ofstream outputFile;
	std::string filePath;
	char separator;
};

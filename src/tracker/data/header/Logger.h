#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <windows.h>

class Logger
{
public:
	Logger(std::string filePath, CHAR separator);
	~Logger();

	VOID LogLn(POINT point);
	VOID LogLn(POINTFLOAT point);
	VOID LogLn(std::string info);

	VOID Log(POINT point);
	VOID Log(POINTFLOAT point);
	VOID Log(std::string info);
protected:
	std::ofstream outputFile;
	std::string filePath;

	CHAR separator;
};

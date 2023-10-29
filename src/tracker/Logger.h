#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <windows.h>

class Logger
{
public:
	Logger(std::string filePath, char separator);

	void LogLn(POINT point);
	void LogLn(POINTFLOAT point);
	void LogLn(std::string info);
	void Log(std::string info);

	~Logger();

protected:
	std::ofstream outputFile;
	std::string filePath;
	char separator;

private:

};

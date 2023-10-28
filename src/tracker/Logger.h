#pragma once

#include <string>
#include <iostream>
#include <fstream>

class Logger
{
public:
	Logger(std::string filePath);

	void LogLn(std::string info);
	void Log(std::string info);

protected:
	std::ofstream outputFile;
	std::string filePath;

private:

};

#include "../header/Logger.h"

Logger::Logger(std::string filePath, CHAR separator)
{
	this->separator = separator;
	this->filePath = filePath;

	outputFile.open(filePath, std::ios::out | std::ios::trunc);

	if (!outputFile.is_open())
	{
		std::cerr << "Error: Could not open file " << filePath << std::endl;
	}
}

VOID Logger::LogLn(POINT point)
{
	std::string str = std::to_string(point.x) + separator + std::to_string(point.y);

	LogLn(str);
}

VOID Logger::LogLn(POINTFLOAT point)
{
	std::string str = std::to_string(point.x) + separator + std::to_string(point.y);

	LogLn(str);
}

VOID Logger::Log(POINT point)
{
	std::string str = std::to_string(point.x) + separator + std::to_string(point.y);

	LogLn(str);
}

VOID Logger::Log(POINTFLOAT point)
{
	std::string str = std::to_string(point.x) + separator + std::to_string(point.y);

	Log(str);
}

VOID Logger::LogLn(std::string info)
{
	if (outputFile.is_open())
	{
		outputFile << info << std::endl;
	}
	else
	{
		std::cerr << "File " << filePath << " does not exist" << std::endl;
	}
}

VOID Logger::Log(std::string info)
{
	if (outputFile.is_open())
	{
		outputFile << info;
	}
	else
	{
		std::cerr << "File " << filePath << " does not exist" << std::endl;
	}
}

Logger::~Logger()
{
	if (outputFile.is_open())
	{
		outputFile.close();
	}
}

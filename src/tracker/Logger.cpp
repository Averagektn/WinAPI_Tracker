#include "Logger.h"

Logger::Logger(std::string filePath)
{
    this->filePath = filePath;
    outputFile.open(filePath, std::ios::out | std::ios::trunc);
}

void Logger::LogLn(std::string info)
{
    if (outputFile.is_open()) {
        outputFile << info << std::endl;
    }
    else 
    {
        std::cerr << "File " << filePath << " does not exist" << std::endl;
    }
}

void Logger::Log(std::string info)
{
    if (outputFile.is_open()) {
        outputFile << info;
    }
    else 
    {
        std::cerr << "File " << filePath << " does not exist" << std::endl;
    }
}
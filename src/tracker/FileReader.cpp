#include "FileReader.h"

FileReader::FileReader(std::string filePath)
{
    this->filePath = filePath;
    inputFile.open(filePath);

    if (!inputFile.is_open())
    {
        std::cerr << "Error: Could not open file " << filePath << std::endl;
    }
}

std::string FileReader::ReadLn()
{
    std::string line;
    std::getline(inputFile, line);
    return line;
}

std::string FileReader::Read(int length)
{
    std::string content;
    char c;
    int count = 0;

    while (inputFile.get(c) && count < length)
    {
        content += c;
        count++;
    }

    return content;
}

FileReader::~FileReader()
{
    if (inputFile.is_open())
    {
        inputFile.close();
    }
}

#include "../header/FileReader.h"

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

std::string FileReader::Read(INT length)
{
	std::string content;
	CHAR c;
	INT count = 0;

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

VOID FileReader::Restart()
{
	inputFile.seekg(0, std::ios::beg);
}

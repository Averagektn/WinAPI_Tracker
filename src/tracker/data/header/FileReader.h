#pragma once

#include <string>
#include <iostream>
#include <fstream>

class FileReader
{
public:
	FileReader(std::string filePath);
	~FileReader();

	std::string ReadLn();
	std::string Read(int length);
protected:
	std::ifstream inputFile;
	std::string filePath;
};

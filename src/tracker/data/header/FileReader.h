#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <windows.h>

class FileReader
{
public:
	FileReader(std::string filePath);
	~FileReader();

	std::string ReadLn();
	std::string Read(INT length);
protected:
	std::ifstream inputFile;
	std::string filePath;
};

#pragma once

#include <string>
#include <iostream>
#include <fstream>

class FileReader
{
public:
	FileReader(std::string filePath);

	std::string ReadLn();
	std::string Read(int length);

	~FileReader();

protected:
	std::ifstream inputFile;
	std::string filePath;

private:

};

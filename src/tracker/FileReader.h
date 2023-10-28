#pragma once

#include <string>

class FileReader
{
public:
	FileReader(std::string filePath);

	std::string ReadLn();
	std::string Read(int length);

protected:

private:

};

#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <windows.h>

/// <summary>
///		Reads data from file
/// </summary>
class FileReader
{
public:
	/// <summary>
	///		Opens file for reading
	/// </summary>
	/// <param name="filePath">
	///		File to open
	/// </param>
	FileReader(std::string filePath);

	/// <summary>
	///		Closes file
	/// </summary>
	~FileReader();

	/// <summary>
	///		Returns file pointer to the beginning
	/// </summary>
	VOID Restart();

	/// <summary>
	///		Reads new line from file
	/// </summary>
	/// <returns>
	///		New line
	/// </returns>
	std::string ReadLn();

	/// <summary>
	///		Reads specified number of symbols
	/// </summary>
	/// <param name="length">
	///		Symbols number
	/// </param>
	/// <returns>
	///		String[length]
	/// </returns>
	std::string Read(INT length);
protected:
	std::ifstream inputFile;
	std::string filePath;
};

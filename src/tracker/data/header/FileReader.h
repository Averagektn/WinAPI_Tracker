#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <windows.h>

/// <summary>
/// 
/// </summary>
class FileReader
{
public:
	/// <summary>
	/// 
	/// </summary>
	/// <param name="filePath">
	/// 
	/// </param>
	FileReader(std::string filePath);

	/// <summary>
	/// 
	/// </summary>
	~FileReader();

	/// <summary>
	/// 
	/// </summary>
	/// <returns>
	/// 
	/// </returns>
	VOID Restart();

	/// <summary>
	/// 
	/// </summary>
	/// <returns>
	/// 
	/// </returns>
	std::string ReadLn();

	/// <summary>
	/// 
	/// </summary>
	/// <param name="length">
	/// 
	/// </param>
	/// <returns>
	/// 
	/// </returns>
	std::string Read(INT length);
protected:
	std::ifstream inputFile;
	std::string filePath;
};

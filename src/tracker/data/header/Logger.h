#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <windows.h>

/// <summary>
/// 
/// </summary>
class Logger
{
public:
	/// <summary>
	/// 
	/// </summary>
	/// <param name="filePath">
	/// 
	/// </param>
	/// <param name="separator">
	/// 
	/// </param>
	Logger(std::string filePath, CHAR separator);

	/// <summary>
	/// 
	/// </summary>
	~Logger();

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
	/// <param name="point">
	/// 
	/// </param>
	/// <returns>
	/// 
	/// </returns>
	VOID LogLn(POINT point);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="point">
	/// 
	/// </param>
	/// <returns>
	/// 
	/// </returns>
	VOID LogLn(POINTFLOAT point);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="info">
	/// 
	/// </param>
	/// <returns>
	/// 
	/// </returns>
	VOID LogLn(std::string info);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="point">
	/// 
	/// </param>
	/// <returns>
	/// 
	/// </returns>
	VOID Log(POINT point);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="point">
	/// 
	/// </param>
	/// <returns>
	/// 
	/// </returns>
	VOID Log(POINTFLOAT point);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="info">
	/// 
	/// </param>
	/// <returns
	/// 
	/// ></returns>
	VOID Log(std::string info);
protected:
	std::ofstream outputFile;
	std::string filePath;

	CHAR separator;
};

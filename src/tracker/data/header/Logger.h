#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <windows.h>

/// <summary>
///		Logger implementation
/// </summary>
class Logger
{
public:
	/// <summary>
	///		Creates file
	/// </summary>
	/// <param name="filePath">
	///		File to create
	/// </param>
	/// <param name="separator">
	///		File separator
	/// </param>
	Logger(std::string filePath, CHAR separator);

	/// <summary>
	///		Closes file
	/// </summary>
	~Logger();

	/// <summary>
	///		Puts file pointer to the beginning of the file
	/// </summary>
	VOID Restart();

	/// <summary>
	///		Logs point coordinates as (POINT.X + SEPARATOR + POINT.Y + "\n")
	/// </summary>
	/// <param name="point">
	///		Point to log
	/// </param>
	VOID LogLn(POINT point);

	/// <summary>
	///		Logs point coordinates as (POINTFLOAT.X + SEPARATOR + POINTFLOAT.Y + "\n")
	/// </summary>
	/// <param name="point">
	///		Point to log
	/// </param>
	VOID LogLn(POINTFLOAT point);

	/// <summary>
	///		Logs string in file + "\n"
	/// </summary>
	/// <param name="info">
	///		String to log
	/// </param>
	VOID LogLn(std::string info);

	/// <summary>
	///		Logs point coordinates as (POINT.X + SEPARATOR + POINT.Y)
	/// </summary>
	/// <param name="point">
	///		Point to log
	/// </param>
	VOID Log(POINT point);

	/// <summary>
	///		Logs point coordinates as (POINTFLOAT.X + SEPARATOR + POINTFLOAT.Y)
	/// </summary>
	/// <param name="point">
	///		Point to log
	/// </param>
	VOID Log(POINTFLOAT point);

	/// <summary>
	///		Logs string in file
	/// </summary>
	/// <param name="info">
	///		String to log
	/// </param>
	VOID Log(std::string info);
protected:
	std::ofstream outputFile;
	std::string filePath;

	CHAR separator;
};

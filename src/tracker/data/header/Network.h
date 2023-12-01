#pragma once

#include <Winsock2.h>
#include <WS2tcpip.h>
#include <string>
#include <iostream>
#include <Windows.h>

/// <summary>
///		Network connection with remote server. TCP. Handshaking algorithm: Server->BYTE(23) Client->BYTE(ANY) 
/// </summary>
class Network
{
public:
	/// <summary>
	///		Crates socket on specified port
	/// </summary>
	/// <param name="serverAddress">
	///		Server IP
	/// </param>
	/// <param name="serverPort">
	///		Server port
	/// </param>
	Network(const CHAR* serverAddress, INT serverPort);

	/// <summary>
	///		Closes connection
	/// </summary>
	~Network();

	/// <summary>
	///		Establishes connection
	/// </summary>
	/// <returns>
	///		TRUE if connection is established
	/// </returns>
	BOOL Connect();

	/// <summary>
	///		Gets next pair of coordinates
	/// </summary>
	/// <param name="point">
	///		Point to be initialized
	/// </param>
	/// <returns>
	///		TRUE if point received
	/// </returns>
	BOOL NextXY(POINTFLOAT& point);
	/// <summary>
	///		Gets next pair of coordinates
	/// </summary>
	/// <param name="point">
	///		Point to be initialized
	/// </param>
	/// <returns>
	///		TRUE if point received
	/// </returns>
	BOOL NextYZ(POINTFLOAT& point);
	/// <summary>
	///		Gets next pair of coordinates
	/// </summary>
	/// <param name="point">
	///		Point to be initialized
	/// </param>
	/// <returns>
	///		TRUE if point received
	/// </returns>
	BOOL NextXZ(POINTFLOAT& point);
	/// <summary>
	///		Gets next pair of coordinates
	/// </summary>
	/// <param name="point">
	///		Point to be initialized
	/// </param>
	/// <returns>
	///		TRUE if point received
	/// </returns>
	BOOL NextZX(POINTFLOAT& point);
	/// <summary>
	///		Gets next pair of coordinates
	/// </summary>
	/// <param name="point">
	///		Point to be initialized
	/// </param>
	/// <returns>
	///		TRUE if point received
	/// </returns>
	BOOL NextZY(POINTFLOAT& point);
	/// <summary>
	///		Gets next pair of coordinates
	/// </summary>
	/// <param name="point">
	///		Point to be initialized
	/// </param>
	/// <returns>
	///		TRUE if point received
	/// </returns>
	BOOL NextYX(POINTFLOAT& point);

	/// <summary>
	///		Gets IP address from textbox
	/// </summary>
	/// <param name="hText">
	///		Textbox handle
	/// </param>
	/// <returns>
	///		Char array as string with IP address
	/// </returns>
	static const CHAR* GetIp(HWND hText);
private:
	/// <summary>
	///		Gets another coordinate. Coordinate is FLOAT value in radians
	/// </summary>
	/// <param name="coord">
	///		Coordinate to initialize
	/// </param>
	/// <returns>
	///		TRUE if value is received
	/// </returns>
	BOOL GetCoord(FLOAT& coord);

	const CHAR* serverAddress_;
	INT serverPort_;

	WSADATA wsaData_;
	SOCKET clientSocket_;
	sockaddr_in serverAddressInfo_;
};

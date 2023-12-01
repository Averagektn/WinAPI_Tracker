#pragma once

#include <Winsock2.h>
#include <WS2tcpip.h>
#include <string>
#include <iostream>
#include <Windows.h>

/// <summary>
/// 
/// </summary>
class Network
{
public:
	/// <summary>
	/// 
	/// </summary>
	/// <param name="serverAddress">
	/// 
	/// </param>
	/// <param name="serverPort">
	/// 
	/// </param>
	Network(const CHAR* serverAddress, INT serverPort);

	/// <summary>
	/// 
	/// </summary>
	~Network();

	/// <summary>
	/// 
	/// </summary>
	/// <returns>
	/// 
	/// </returns>
	BOOL Connect();

	/// <summary>
	/// 
	/// </summary>
	/// <param name="point">
	/// 
	/// </param>
	/// <returns>
	/// 
	/// </returns>
	BOOL NextXY(POINTFLOAT& point);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="point">
	/// 
	/// </param>
	/// <returns>
	/// 
	/// </returns>
	BOOL NextYZ(POINTFLOAT& point);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="point">
	/// 
	/// </param>
	/// <returns>
	/// 
	/// </returns>
	BOOL NextXZ(POINTFLOAT& point);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="point">
	/// 
	/// </param>
	/// <returns>
	/// 
	/// </returns>
	BOOL NextZX(POINTFLOAT& point);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="point">
	/// 
	/// </param>
	/// <returns>
	/// 
	/// </returns>
	BOOL NextZY(POINTFLOAT& point);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="point">
	/// 
	/// </param>
	/// <returns>
	/// 
	/// </returns>
	BOOL NextYX(POINTFLOAT& point);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="hText">
	/// 
	/// </param>
	/// <returns>
	/// 
	/// </returns>
	static const CHAR* GetIp(HWND hText);
private:
	/// <summary>
	/// 
	/// </summary>
	/// <param name="coord">
	/// 
	/// </param>
	/// <returns>
	/// 
	/// </returns>
	BOOL GetCoord(FLOAT& coord);

	const CHAR* serverAddress_;
	INT serverPort_;

	WSADATA wsaData_;
	SOCKET clientSocket_;
	sockaddr_in serverAddressInfo_;
};

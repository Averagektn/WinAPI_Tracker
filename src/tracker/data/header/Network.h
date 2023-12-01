#pragma once

#include <Winsock2.h>
#include <WS2tcpip.h>
#include <string>
#include <iostream>
#include <Windows.h>

#include "Logger.h"

class Network
{
public:
	Network(const CHAR* serverAddress, INT serverPort);
	~Network();

	BOOL Connect();

	BOOL NextXY(POINTFLOAT& point);
	BOOL NextYZ(POINTFLOAT& point);
	BOOL NextXZ(POINTFLOAT& point);
	BOOL NextZX(POINTFLOAT& point);
	BOOL NextZY(POINTFLOAT& point);
	BOOL NextYX(POINTFLOAT& point);

	static const CHAR* GetIp(HWND hText);
protected:
	BOOL GetCoord(FLOAT& coord);
private:
	const CHAR* serverAddress_;
	INT serverPort_;

	WSADATA wsaData_;
	SOCKET clientSocket_;
	sockaddr_in serverAddressInfo_;
};


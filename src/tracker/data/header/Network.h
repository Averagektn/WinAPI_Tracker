#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Winsock2.h>
#include <WS2tcpip.h>
#include <string>
#include <iostream>
#include <Windows.h>
#include "Logger.h"

#pragma comment(lib, "Ws2_32.lib")

class Network
{
public:
	Network(const char* serverAddress, int serverPort);
	~Network();

	bool Connect();

	bool NextXY(POINTFLOAT& point);
	bool NextYZ(POINTFLOAT& point);
	bool NextXZ(POINTFLOAT& point);
	bool NextZX(POINTFLOAT& point);
	bool NextZY(POINTFLOAT& point);
	bool NextYX(POINTFLOAT& point);

	static const char* GetIp(HWND hText);
protected:
	bool GetCoord(float& coord);
private:
	const char* serverAddress_;
	int serverPort_;
	WSADATA wsaData_;
	SOCKET clientSocket_;
	sockaddr_in serverAddressInfo_;
	Logger logger;
};


#include "../header/Network.h"

Network::Network(const CHAR* serverAddress, INT serverPort) :
	serverAddress_(serverAddress), serverPort_(serverPort), clientSocket_(INVALID_SOCKET), serverAddressInfo_()
{
	if (WSAStartup(MAKEWORD(2, 2), &wsaData_) != 0)
	{
		std::cerr << "Failed to initialize Winsock\n";
	}
}

Network::~Network()
{
	if (clientSocket_ != INVALID_SOCKET)
	{
		closesocket(clientSocket_);
	}

	WSACleanup();
}

BOOL Network::Connect()
{
	CHAR receivedByte;
	INT bytesRead, bytesSent;

	clientSocket_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (clientSocket_ == INVALID_SOCKET)
	{
		std::cerr << "Failed to create socket\n";
		return FALSE;
	}

	serverAddressInfo_.sin_family = AF_INET;
	serverAddressInfo_.sin_port = htons(serverPort_);
	inet_pton(AF_INET, serverAddress_, &serverAddressInfo_.sin_addr);

	if (connect(clientSocket_, (struct sockaddr*)&serverAddressInfo_, sizeof(serverAddressInfo_)) == SOCKET_ERROR)
	{
		closesocket(clientSocket_);
		return FALSE;
	}

	bytesRead = recv(clientSocket_, &receivedByte, sizeof(receivedByte), 0);
	if (bytesRead == SOCKET_ERROR || bytesRead == 0 || receivedByte != 23)
	{
		closesocket(clientSocket_);
		return FALSE;
	}

	bytesSent = send(clientSocket_, &receivedByte, sizeof(receivedByte), 0);
	if (bytesSent == SOCKET_ERROR)
	{
		closesocket(clientSocket_);
		return FALSE;
	}

	return TRUE;
}

BOOL Network::NextXY(POINTFLOAT& point)
{
	FLOAT x, y, z;

	if (GetCoord(x) && GetCoord(y) && GetCoord(z))
	{
		point = { x, y };

		return TRUE;
	}

	return FALSE;
}

BOOL Network::NextYZ(POINTFLOAT& point)
{
	FLOAT x, y, z;

	if (GetCoord(x) && GetCoord(y) && GetCoord(z))
	{
		point = { y, z };
		return TRUE;
	}

	return FALSE;
}

BOOL Network::NextXZ(POINTFLOAT& point)
{
	FLOAT x, y, z;

	if (GetCoord(x) && GetCoord(y) && GetCoord(z))
	{
		point = { x, z };

		return TRUE;
	}

	return FALSE;
}

BOOL Network::NextZX(POINTFLOAT& point)
{
	FLOAT x, y, z;

	if (GetCoord(x) && GetCoord(y) && GetCoord(z))
	{
		point = { z, x };

		return TRUE;
	}

	return FALSE;
}

BOOL Network::NextZY(POINTFLOAT& point)
{
	FLOAT x, y, z;

	if (GetCoord(x) && GetCoord(y) && GetCoord(z))
	{
		point = { z, y };

		return TRUE;
	}

	return FALSE;
}

BOOL Network::NextYX(POINTFLOAT& point)
{
	FLOAT x, y, z;

	if (GetCoord(x) && GetCoord(y) && GetCoord(z))
	{
		point = { y, x };

		return TRUE;
	}

	return FALSE;
}

const CHAR* Network::GetIp(HWND hText)
{
	INT textLength = GetWindowTextLength(hText);
	LPWSTR buffer = new wchar_t[textLength + 1];

	GetWindowText(hText, buffer, textLength + 1);

	INT bufferSize = WideCharToMultiByte(CP_UTF8, 0, buffer, -1, NULL, 0, NULL, NULL);
	CHAR* charBuffer = new char[bufferSize];
	WideCharToMultiByte(CP_UTF8, 0, buffer, -1, charBuffer, bufferSize, NULL, NULL);

	const PCHAR ip = new CHAR[bufferSize];
	strcpy_s(const_cast<PCHAR>(ip), bufferSize, charBuffer);

	delete[] buffer;
	delete[] charBuffer;

	return ip;
}

BOOL Network::GetCoord(FLOAT& coord)
{
	CHAR buffer[4];
	INT bytesRead = recv(clientSocket_, buffer, sizeof(buffer), 0);

	if (bytesRead == SOCKET_ERROR)
	{
		return FALSE;
	}
	else if (bytesRead == 0)
	{
		return FALSE;
	}
	else if (bytesRead != sizeof(buffer))
	{
		return FALSE;
	}

	coord = reinterpret_cast<PFLOAT>(buffer)[0];

	return TRUE;
}

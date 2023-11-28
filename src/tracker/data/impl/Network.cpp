#include "../header/Network.h"

Network::Network(const char* serverAddress, int serverPort) :
	logger("data\\received\\network.txt", ' '),
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

bool Network::Connect()
{
	char receivedByte;
	int bytesRead, bytesSent;

	clientSocket_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (clientSocket_ == INVALID_SOCKET)
	{
		std::cerr << "Failed to create socket\n";
		return false;
	}

	serverAddressInfo_.sin_family = AF_INET;
	serverAddressInfo_.sin_port = htons(serverPort_);
	inet_pton(AF_INET, serverAddress_, &serverAddressInfo_.sin_addr);

	if (connect(clientSocket_, (struct sockaddr*)&serverAddressInfo_, sizeof(serverAddressInfo_)) == SOCKET_ERROR)
	{
		closesocket(clientSocket_);
		return false;
	}

	bytesRead = recv(clientSocket_, &receivedByte, sizeof(receivedByte), 0);
	if (bytesRead == SOCKET_ERROR || bytesRead == 0 || receivedByte != 23)
	{
		closesocket(clientSocket_);
		return false;
	}

	bytesSent = send(clientSocket_, &receivedByte, sizeof(receivedByte), 0);
	if (bytesSent == SOCKET_ERROR)
	{
		closesocket(clientSocket_);
		return false;
	}

	return true;
}

bool Network::NextXY(POINTFLOAT& point)
{
	float x, y, z;

	if (GetCoord(x) && GetCoord(y) && GetCoord(z))
	{
		point = { x, y };

		return true;
	}

	return false;
}

bool Network::NextYZ(POINTFLOAT& point)
{
	float x, y, z;

	if (GetCoord(x) && GetCoord(y) && GetCoord(z))
	{
		point = { y, z };
		return true;
	}

	return false;
}

bool Network::NextXZ(POINTFLOAT& point)
{
	float x, y, z;

	if (GetCoord(x) && GetCoord(y) && GetCoord(z))
	{
		point = { x, z };

		return true;
	}

	return false;
}

bool Network::NextZX(POINTFLOAT& point)
{
	float x, y, z;

	if (GetCoord(x) && GetCoord(y) && GetCoord(z))
	{
		point = { z, x };

		return true;
	}

	return false;
}

bool Network::NextZY(POINTFLOAT& point)
{
	float x, y, z;

	if (GetCoord(x) && GetCoord(y) && GetCoord(z))
	{
		point = { z, y };

		return true;
	}

	return false;
}

bool Network::NextYX(POINTFLOAT& point)
{
	float x, y, z;

	if (GetCoord(x) && GetCoord(y) && GetCoord(z))
	{
		point = { y, x };

		return true;
	}

	return false;
}

const char* Network::GetIp(HWND hText)
{
	int textLength = GetWindowTextLength(hText);
	wchar_t* buffer = new wchar_t[textLength + 1];

	GetWindowText(hText, buffer, textLength + 1);

	int bufferSize = WideCharToMultiByte(CP_UTF8, 0, buffer, -1, nullptr, 0, nullptr, nullptr);
	char* charBuffer = new char[bufferSize];
	WideCharToMultiByte(CP_UTF8, 0, buffer, -1, charBuffer, bufferSize, nullptr, nullptr);

	const char* ip = new char[bufferSize];
	strcpy_s(const_cast<char*>(ip), bufferSize, charBuffer);

	delete[] buffer;
	delete[] charBuffer;

	return ip;
}

bool Network::GetCoord(float& coord)
{
	char buffer[4];
	int bytesRead = recv(clientSocket_, buffer, sizeof(buffer), 0);

	if (bytesRead == SOCKET_ERROR)
	{
		return false;
	}
	else if (bytesRead == 0)
	{
		return false;
	}
	else if (bytesRead != sizeof(buffer))
	{
		return false;
	}

	coord = reinterpret_cast<float*>(buffer)[0];

	return true;
}

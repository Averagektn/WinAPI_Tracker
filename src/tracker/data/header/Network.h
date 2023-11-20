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
    Network(const char* serverAddress, int serverPort) : 
        logger("network.txt", ' '), serverAddress_(serverAddress), serverPort_(serverPort), clientSocket_(INVALID_SOCKET), 
        serverAddressInfo_()
    {
        if (WSAStartup(MAKEWORD(2, 2), &wsaData_) != 0) 
        {
            std::cerr << "Failed to initialize Winsock\n";
        }
    }

    ~Network() 
    {
        if (clientSocket_ != INVALID_SOCKET) 
        {
            closesocket(clientSocket_);
        }
        WSACleanup();
    }

    bool Connect() 
    {
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

        char receivedByte;
        int bytesRead = recv(clientSocket_, &receivedByte, sizeof(receivedByte), 0);
        if (bytesRead == SOCKET_ERROR || bytesRead == 0 || receivedByte != 23) 
         {
            closesocket(clientSocket_);
            return false;
        }

        int bytesSent = send(clientSocket_, &receivedByte, sizeof(receivedByte), 0);
        if (bytesSent == SOCKET_ERROR) 
         {
            closesocket(clientSocket_);
            return false;
        }

        return true;
    }

    bool ReadData(float& float1, float& float2, float& float3) {
        char buffer[12];
        int bytesRead = recv(clientSocket_, buffer, sizeof(buffer), 0);

        if (bytesRead == SOCKET_ERROR) {
            return false;
        }
        else if (bytesRead == 0) {
            return false;
        }
        else if (bytesRead != sizeof(buffer)) {
            return false;
        }

        float* floatArray = reinterpret_cast<float*>(buffer);
        float1 = floatArray[0];
        float2 = floatArray[1];
        float3 = floatArray[2];

        logger.Log(std::to_string(float1) + " " + std::to_string(float2) + " " + std::to_string(float3));

        return true;
    }

    bool NextXY(POINTFLOAT& point)
    {
        float x, y, z;

        if (ReadData(x, y, z))
        {
            point = {x, y};

            return true;
        }

        return false;
    }

    POINTFLOAT NextYZ() 
    {
        float x, y, z;

        if (ReadData(x, y, z)) 
        {
            return POINTFLOAT{ y, z };
        }

        return POINTFLOAT{ 0, 0 };
    }

    POINTFLOAT NextXZ()
    {
        float x, y, z;

        if (ReadData(x, y, z))
        {
            return POINTFLOAT{ x, z };
        }

        return POINTFLOAT{ 0, 0 };
    }

private:
    const char* serverAddress_;
    int serverPort_;
    WSADATA wsaData_;
    SOCKET clientSocket_;
    sockaddr_in serverAddressInfo_;
    Logger logger;
};


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
        logger("dataset_working.txt", ' '), serverAddress_(serverAddress), serverPort_(serverPort), clientSocket_(INVALID_SOCKET), 
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

    bool GetCoord(float& coord) {
        char buffer[4];
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
        coord = floatArray[0];

        return true;
    }

    bool NextXY(POINTFLOAT& point)
    {
        float x, y, z;
        
        if (GetCoord(x) && GetCoord(y) && GetCoord(z))
        {
            point = {x, y};

            return true;
        }

        return false;
    }

    bool NextYZ(POINTFLOAT& point)
    {
        float x, y, z;

        if (GetCoord(x) && GetCoord(y) && GetCoord(z))
        {
            point = { y, z };
            return true;
        }

        return false;
    }

    bool NextXZ(POINTFLOAT& point)
    {
        float x, y, z;

        if (GetCoord(x) && GetCoord(y) && GetCoord(z))
        {
            point = { x, z };

            return true;
        }

        return false;
    }

    bool NextZX(POINTFLOAT& point)
    {
        float x, y, z;

        if (GetCoord(x) && GetCoord(y) && GetCoord(z))
        {
            point = { z, x };

            return true;
        }

        return false;
    }

    bool NextZY(POINTFLOAT& point)
    {
        float x, y, z;

        if (GetCoord(x) && GetCoord(y) && GetCoord(z))
        {
            point = { z, y };

            return true;
        }

        return false;
    }

    bool NextYX(POINTFLOAT& point)
    {
        float x, y, z;

        if (GetCoord(x) && GetCoord(y) && GetCoord(z))
        {
            point = { y, x };

            return true;
        }

        return false;
    }

private:
    const char* serverAddress_;
    int serverPort_;
    WSADATA wsaData_;
    SOCKET clientSocket_;
    sockaddr_in serverAddressInfo_;
    Logger logger;
};


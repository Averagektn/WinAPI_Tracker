#include "Converter.h"

Converter::Converter(int width, int height, float maxAngleX, float maxAngleY)
{
    // 720
    maxCoordX = width;
    maxCoordY = height;
    
    // 180
    this->maxAngleX = maxAngleX;
    this->maxAngleY = maxAngleY;
    
    // 360
    angleWidth = maxAngleX * 2;
    angleHeight = maxAngleY * 2;

    // 360
    maxLogCoordX = width / 2;
    maxLogCoordY = height / 2;
}

int Converter::ToCoordX(float angle)
{
    angle += maxAngleX;

    return (int)round(angle * maxCoordX / angleWidth);
}

int Converter::ToCoordY(float angle)
{
    angle += maxAngleY;

    return (int)round(angle * maxCoordY / angleHeight);
}

int Converter::ToCoordX_Log(int logCoord)
{
    return logCoord + maxLogCoordX;
}

int Converter::ToCoordY_Log(int logCoord)
{
    return maxLogCoordY - logCoord;
}

POINT Converter::ToCoord(std::string str)
{
    POINT result = { 0, 0 }; 
    std::istringstream iss(str);

    if (iss >> result.x >> result.y) 
    {
        return result;
    }
    return result;
}

POINT Converter::ToCoord(POINTFLOAT point)
{
    return { ToCoordX(point.x), ToCoordY(point.y) };
}

POINT Converter::ToCoord(POINT logPoint)
{
    return { ToCoordX_Log(logPoint.x), ToCoordY_Log(logPoint.y) };
}

float Converter::ToAngleX(int coord)
{
    return ToLogCoordX(coord) * angleWidth / maxCoordX;
}

float Converter::ToAngleY(int coord)
{
    return ToLogCoordY(coord) * angleHeight / maxCoordY;
}

float Converter::ToAngleX_Log(int logCoord)
{
    return ToAngleX(logCoord + maxLogCoordX);
}

float Converter::ToAngleY_Log(int logCoord)
{
    return ToAngleX(logCoord + maxLogCoordY);
}

POINTFLOAT Converter::ToAngle(std::string str)
{
    POINTFLOAT result = { 0, 0 };
    std::istringstream iss(str);

    if (iss >> result.x >> result.y)
    {
        return result;
    }
    return result;
}

POINTFLOAT Converter::ToAngle(POINT point)
{
    return { ToAngleX(point.x), ToAngleY(point.y) };
}

POINTFLOAT Converter::ToAngle_Log(POINT logPoint)
{
    return { ToAngleX_Log(logPoint.x), ToAngleY_Log(logPoint.y) };
}

int Converter::ToLogCoordX(int coord)
{
    return coord - maxLogCoordX;
}

int Converter::ToLogCoordY(int coord)
{
    return maxLogCoordY - coord;
}

int Converter::ToLogCoordX_Angle(float angle)
{
    return ToLogCoordX(ToCoordX(angle));
}

int Converter::ToLogCoordY_Angle(float angle)
{
    return ToLogCoordY(ToCoordY(angle));
}

POINT Converter::ToLogCoord(POINTFLOAT point)
{
    return { ToLogCoordX_Angle(point.x), ToLogCoordY_Angle(point.y) };
}

POINT Converter::ToLogCoord(POINT point)
{
    return { ToLogCoordX(point.x), ToLogCoordY(point.y) };
}

POINT Converter::ToLogCoord(std::string str)
{
    return ToCoord(str);
}

POINT Converter::ToLogCoord_FromCoordString(std::string str)
{
    return ToLogCoord(ToCoord(str));
}

POINT Converter::ToLogCoord_FromAngleString(std::string str)
{
    return ToLogCoord(ToAngle(str));
}

POINT Converter::ToCoord_FromLogCoordString(std::string str)
{
    return ToCoord(ToLogCoord(str));
}

POINT Converter::ToCoord_FromAngleString(std::string str)
{
    return ToCoord(ToAngle(str));
}

POINTFLOAT Converter::ToAngle_FromLogCoordString(std::string str)
{
    return ToAngle(ToLogCoord(str));
}

POINTFLOAT Converter::ToAngle_FromCoordString(std::string str)
{
    return ToAngle(ToCoord(str));
}

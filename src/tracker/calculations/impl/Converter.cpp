#include "../header/Converter.h"

Converter::Converter(INT width, INT height, FLOAT maxAngleX, FLOAT maxAngleY)
{
	maxCoordX = width;
	maxCoordY = height;

	this->maxAngleX = maxAngleX;
	this->maxAngleY = maxAngleY;

	angleWidth = maxAngleX * 2;
	angleHeight = maxAngleY * 2;

	maxLogCoordX = width / 2;
	maxLogCoordY = height / 2;
}

INT Converter::ToCoordX(FLOAT angle)
{
	angle = -angle + maxAngleX;

	return (INT)round(angle * maxCoordX / angleWidth);
}

INT Converter::ToCoordY(FLOAT angle)
{
	angle = -angle + maxAngleY;

	return (INT)round(angle * maxCoordY / angleHeight);
}

INT Converter::ToCoordX_Log(INT logCoord) const
{
	return logCoord + maxLogCoordX;
}

INT Converter::ToCoordY_Log(INT logCoord) const
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

FLOAT Converter::ToAngleX(INT coord) const
{
	return ToLogCoordX(coord) * angleWidth / maxCoordX;
}

FLOAT Converter::ToAngleY(INT coord) const
{
	return ToLogCoordY(coord) * angleHeight / maxCoordY;
}

FLOAT Converter::ToAngleX_Log(INT logCoord) const
{
	return ToAngleX(logCoord + maxLogCoordX);
}

FLOAT Converter::ToAngleY_Log(INT logCoord) const
{
	return ToAngleX(logCoord + maxLogCoordY);
}

POINTFLOAT Converter::ToAngle(std::string str)
{
	POINTFLOAT result = { 0, 0 };

	str = ReplaceCommas(str);
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

INT Converter::ToLogCoordX(INT coord) const
{
	return coord - maxLogCoordX;
}

INT Converter::ToLogCoordY(INT coord) const
{
	return maxLogCoordY - coord;
}

INT Converter::ToLogCoordX_Angle(FLOAT angle)
{
	return ToLogCoordX(ToCoordX(angle));
}

INT Converter::ToLogCoordY_Angle(FLOAT angle)
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

FLOAT Converter::ToAngle_FromRadian(FLOAT radian)
{
	return radian * 180 / 3.14;
}

FLOAT Converter::ToRadian_FromAngle(FLOAT angle)
{
	return angle * 3.14 / 180;
}

POINTFLOAT Converter::ToAngle_FromRadian(POINTFLOAT radian)
{
	return POINTFLOAT{ ToAngle_FromRadian(radian.x), ToAngle_FromRadian(radian.y) };
}

POINTFLOAT Converter::ToRadian_FromAngle(POINTFLOAT angle)
{
	return POINTFLOAT{ ToRadian_FromAngle(angle.x), ToRadian_FromAngle(angle.y) };
}

FLOAT Converter::GetFloat_FromWindowText(HWND hWnd)
{
	wchar_t buffer[256];
	GetWindowText(hWnd, buffer, 256);

	std::wstring wstrX(buffer);
	std::string strX(wstrX.begin(), wstrX.end());

	return std::stof(strX);
}

INT Converter::GetValue(std::string str)
{
	INT result = 0;
	std::istringstream iss(str);

	if (iss >> result)
	{
		return result;
	}

	return result;
}

std::string Converter::ReplaceCommas(std::string str)
{
	size_t pos = str.find(",");

	while (pos != std::string::npos)
	{
		str.replace(pos, 1, ".");
		pos = str.find(",", pos + 1);
	}

	return str;
}

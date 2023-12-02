#include "..\\header\\Control.h"

Control::Control(HWND hWnd)
{
	this->hWnd = hWnd;
	GetClientRect(hWnd, &clientRect);
}

VOID Control::Scale(HWND hControl)
{
	RECT clientRect;
	GetClientRect(hWnd, &clientRect);

	FLOAT xScale = (FLOAT)clientRect.right / this->clientRect.right;
	FLOAT yScale = (FLOAT)clientRect.bottom / this->clientRect.bottom;

	RECT controlRect;
	GetClientRect(hControl, &controlRect);

	POINT controlPoint = { 0, 0 };
	MapWindowPoints(hControl, hWnd, &controlPoint, 1);

	INT x = controlPoint.x * xScale;
	INT y = controlPoint.y * yScale;
	INT width = (controlRect.right - controlRect.left) * xScale;
	INT height = (controlRect.bottom - controlRect.top) * yScale;

	ScaleFont(hControl, xScale, yScale);

	MoveWindow(hControl, x, y, width, height, TRUE);
}

VOID Control::ScaleComboBox(HWND hControl, INT nItems)
{
	RECT clientRect;
	GetClientRect(hWnd, &clientRect);

	FLOAT xScale = (FLOAT)clientRect.right / this->clientRect.right;
	FLOAT yScale = (FLOAT)clientRect.bottom / this->clientRect.bottom;

	RECT controlRect;
	GetClientRect(hControl, &controlRect);

	POINT controlPoint = { 0, 0 };
	MapWindowPoints(hControl, hWnd, &controlPoint, 1);

	INT x = controlPoint.x * xScale;
	INT y = controlPoint.y * yScale;
	INT width = (controlRect.right - controlRect.left) * xScale;
	INT height = clientRect.bottom;

	ScaleFont(hControl, xScale, yScale);

	MoveWindow(hControl, x, y, width, height, TRUE);
}

VOID Control::UpdateClientRect()
{
	GetClientRect(hWnd, &clientRect);
}

VOID Control::SetClientRect(RECT clientRect)
{
	this->clientRect = clientRect;
}

VOID Control::SetWindowHandle(HWND hWnd)
{
	this->hWnd = hWnd;
}

HWND Control::GetWindowHandle() const
{
	return hWnd;
}

RECT Control::GetCurrentClientRect() const
{
	return clientRect;
}

VOID Control::ScaleFont(HWND hControl, FLOAT xScale, FLOAT yScale)
{
	HFONT hButtonFont = (HFONT)SendMessage(hControl, WM_GETFONT, 0, 0);
	LOGFONT lf{};

	GetObject(hButtonFont, sizeof(LOGFONT), &lf);

	lf.lfWidth *= xScale;
	lf.lfHeight *= yScale;

	HFONT hNewFont = CreateFontIndirect(&lf);
	SendMessage(hControl, WM_SETFONT, (WPARAM)hNewFont, TRUE);
}

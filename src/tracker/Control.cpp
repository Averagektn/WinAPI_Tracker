#include "Control.h"

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
    INT height = (controlRect.bottom - controlRect.top) * yScale * nItems;

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

VOID Control::SetWindowHandler(HWND hWnd)
{
    this->hWnd = hWnd;
}

HWND Control::GetWindowHandler() const
{
    return hWnd;
}

RECT Control::GetCurrentClientRect() const
{
    return clientRect;
}

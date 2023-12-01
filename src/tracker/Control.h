#pragma once

#include <windows.h>

class Control
{
public:
	Control(HWND hWnd);

	VOID Scale(HWND hControl);
	VOID ScaleComboBox(HWND hControl, INT nItems);

	VOID UpdateClientRect();

	VOID SetClientRect(RECT clientRect);
	VOID SetWindowHandler(HWND hWnd);

	HWND GetWindowHandler() const;
	RECT GetCurrentClientRect() const;
private:
	HWND hWnd;
	RECT clientRect;
};


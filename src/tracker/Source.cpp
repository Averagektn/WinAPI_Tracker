#include <windows.h>
#include <gdiplus.h>
#include "Constants.h"
#include "Functions.h"
#include "Cursor.h"

#define TIMER_LOG 1
#define TIMER_LOAD 2

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) 
{
	WNDCLASSEX wcex;
	HWND hWnd;
	MSG msg;
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;

	Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_DBLCLKS;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = HBRUSH(CreateSolidBrush(RGB(255, 255, 255)));
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = ProjConst::PROJ_NAME;
	wcex.hIconSm = wcex.hIcon;
	RegisterClassEx(&wcex);

	hWnd = CreateWindow(ProjConst::PROJ_NAME, ProjConst::WND_CAPTION, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, ProjConst::WND_DEF_WIDTH, ProjConst::WND_DEF_HEIGHT,
		NULL, NULL, hInstance, NULL);

	SetTimer(hWnd, TIMER_LOG, 20, NULL);
	SetTimer(hWnd, TIMER_LOAD, 40, NULL);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	Gdiplus::GdiplusShutdown(gdiplusToken);

	return (int)msg.wParam;
}

Cursor cursor(Gdiplus::Color(255,255,0,0), ProjConst::WND_DEF_WIDTH / 2, ProjConst::WND_DEF_HEIGHT / 2, 10);

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) 
{
	HDC hdc;
	PAINTSTRUCT ps;

	switch (message) 
	{
	case WM_TIMER:
		if (wParam == TIMER_LOG) 
		{

		}
		if (wParam == TIMER_LOAD) 
		{

		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		cursor.Draw(hdc);

		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

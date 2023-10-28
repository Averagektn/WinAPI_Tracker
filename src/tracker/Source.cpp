#include <windows.h>
#include <gdiplus.h>
#include <d2d1.h>
#include "Constants.h"
#include "Functions.h"
#include "Cursor.h"

#define TIMER_LOG 1
#define TIMER_LOAD 2

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

ID2D1HwndRenderTarget* renderTarget;

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

	ID2D1Factory* d2dFactory;
	D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &d2dFactory);

	D2D1_RENDER_TARGET_PROPERTIES renderProps = D2D1::RenderTargetProperties(
		D2D1_RENDER_TARGET_TYPE_HARDWARE,
		D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED)
	);

	RECT clientRect;
	GetClientRect(hWnd, &clientRect);
	D2D1_SIZE_U size = D2D1::SizeU(
		clientRect.right - clientRect.left,
		clientRect.bottom - clientRect.top
	);

	d2dFactory->CreateHwndRenderTarget(
		renderProps,
		D2D1::HwndRenderTargetProperties(hWnd, size),
		&renderTarget
	);

	SetTimer(hWnd, TIMER_LOG, 17, NULL);
	SetTimer(hWnd, TIMER_LOAD, 40, NULL);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	KillTimer(hWnd, TIMER_LOG);
	KillTimer(hWnd, TIMER_LOAD);
	Gdiplus::GdiplusShutdown(gdiplusToken);

	return (int)msg.wParam;
}

Cursor cursor(ProjConst::WND_DEF_WIDTH / 2, ProjConst::WND_DEF_HEIGHT / 2, 10);
bool isLeftPressed = false;
bool isRightPressed = false;
bool isUpPressed = false;
bool isDownPressed = false;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) 
{
	HDC hdc;
	PAINTSTRUCT ps;

	switch (message) 
	{
	case WM_TIMER:
		if (wParam == TIMER_LOG) 
		{
			int xSpeed = ProjConst::SPEED;
			int ySpeed = ProjConst::SPEED;
			if (isUpPressed)
			{
				cursor.AddCoordY(-ProjConst::SPEED);
			}
			if (isDownPressed)
			{
				cursor.AddCoordY(ProjConst::SPEED);
			}
			if (isLeftPressed)
			{
				cursor.AddCoordX(-ProjConst::SPEED);
			}
			if (isRightPressed)
			{
				cursor.AddCoordX(ProjConst::SPEED);
			}
			InvalidateRect(hWnd, NULL, TRUE);
		}
		//if (wParam == TIMER_LOAD) 
		//{
		
		//}
		break;
	case WM_KEYDOWN:
		if (wParam == VK_LEFT) 
		{
			isLeftPressed = true;
		}
		if (wParam == VK_RIGHT) 
		{
			isRightPressed = true;
		}
		if (wParam == VK_UP)
		{
			isUpPressed = true;
		}
		if (wParam == VK_DOWN)
		{
			isDownPressed = true;
		}
		break;
	case WM_KEYUP:
		if (wParam == VK_LEFT) 
		{
			isLeftPressed = false;
		}
		if (wParam == VK_RIGHT) 
		{
			isRightPressed = false;
		}
		if (wParam == VK_UP)
		{
			isUpPressed = false;
		}
		if (wParam == VK_DOWN)
		{
			isDownPressed = false;
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		//cursor.Draw(hdc);
		//cursor.DrawDoubleBuffer(hdc);
		// ���������� �� ������-������� � ������� Direct2D
		renderTarget->BeginDraw();
		renderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));
		cursor.Draw(renderTarget);
		renderTarget->EndDraw();

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
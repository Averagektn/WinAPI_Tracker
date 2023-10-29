#include <windows.h>
#include <wingdi.h>
#include <d2d1.h>
#include "Constants.h"

#include "Cursor.h"
#include "Target.h"
#include "Logger.h"
#include "Axis.h"
#include "FileReader.h"
#include "Converter.h"
#include "PathDrawer.h"

#include <wincodec.h>
#pragma comment(lib, "windowscodecs.lib")

#define TIMER_LOG 1
#define TIMER_LOAD 2

ID2D1HwndRenderTarget* renderTarget;
// def rb = 704, 681
Cursor cursor(352, 340, ProjConst::CURSOR_RADIUS);
Target target(1000, 1000, 10);
Logger coordLogger("coords.txt", ' ');
Logger angleLogger("angles.txt", ' ');
FileReader reader("centers.txt");

bool isLeftPressed = false;
bool isRightPressed = false;
bool isUpPressed = false;
bool isDownPressed = false;
bool isGame = true;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) 
{
	WNDCLASSEX wcex;
	HWND hWnd;
	MSG msg;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_DBLCLKS;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = HBRUSH(CreateSolidBrush(ProjConst::WND_DEF_COLOR));
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = ProjConst::PROJ_NAME;
	wcex.hIconSm = wcex.hIcon;
	RegisterClassEx(&wcex);

	hWnd = CreateWindow(ProjConst::PROJ_NAME, ProjConst::WND_CAPTION, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, ProjConst::WND_DEF_WIDTH, ProjConst::WND_DEF_HEIGHT,
		NULL, NULL, hInstance, NULL);

	ID2D1Factory* d2dFactory;
	D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &d2dFactory);

	D2D1_RENDER_TARGET_PROPERTIES renderProps = D2D1::RenderTargetProperties
	(
		D2D1_RENDER_TARGET_TYPE_HARDWARE,
		D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED)
	);

	RECT clientRect;
	GetClientRect(hWnd, &clientRect);
	D2D1_SIZE_U size = D2D1::SizeU(clientRect.right - clientRect.left, clientRect.bottom - clientRect.top);

	d2dFactory->CreateHwndRenderTarget(renderProps, D2D1::HwndRenderTargetProperties(hWnd, size), &renderTarget);

	SetTimer(hWnd, TIMER_LOG, ProjConst::LOG_TIMEOUT, NULL);
	SetTimer(hWnd, TIMER_LOAD, ProjConst::LOAD_TIMEOUT, NULL);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}

bool SaveBitmapToFile(HBITMAP hBitmap, const wchar_t* filename);

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) 
{
	HDC hdc;
	PAINTSTRUCT ps;

	RECT clientRect;
	GetClientRect(hWnd, &clientRect);
	Converter converter(clientRect.right, clientRect.bottom, 180.0f, 180.0f);

	Axis xAxis(clientRect.left, clientRect.bottom / 2, clientRect.right, clientRect.bottom / 2);
	Axis yAxis(clientRect.right / 2, clientRect.top, clientRect.right / 2, clientRect.bottom);

	switch (message) 
	{
	case WM_TIMER:
		if (wParam == TIMER_LOG) 
		{
			int xSpeed = 0;
			int ySpeed = 0;
			int speed = ProjConst::SPEED;

			POINT center = cursor.Shot();
			coordLogger.LogLn(converter.ToLogCoord(center));
			angleLogger.LogLn(converter.ToAngle(center));

			if ((isUpPressed || isDownPressed) && (isLeftPressed || isRightPressed))
			{
				speed /= ProjConst::DIAGONAL_SPEED_CORRECTION;
			}

			if (isUpPressed)
			{
				ySpeed -= speed;
			}
			if (isDownPressed)
			{
				ySpeed += speed;
			}
			if (isLeftPressed)
			{
				xSpeed -= speed;
			}
			if (isRightPressed)
			{
				xSpeed += speed;
			}

			if (cursor.GetLeft() <= clientRect.left && xSpeed < 0)
			{
				xSpeed = 0;
			}
			if (cursor.GetRight() >= clientRect.right && xSpeed > 0)
			{
				xSpeed = 0;
			}
			if (cursor.GetTop() <= clientRect.top && ySpeed < 0)
			{
				ySpeed = 0;
			}
			if (cursor.GetBottom() >= clientRect.bottom && ySpeed > 0)
			{
				ySpeed = 0;
			}

			cursor.AddCoordX(xSpeed);
			cursor.AddCoordY(ySpeed);

			InvalidateRect(hWnd, NULL, TRUE);
		}
		if (wParam == TIMER_LOAD) 
		{
			std::string nextLine = reader.ReadLn();

			if (nextLine.empty())
			{
				target.SetCenter({ 1000, 1000 });
				cursor.SetCenter({ 1000, 1000 });
				isGame = false;
				KillTimer(hWnd, TIMER_LOG);
				KillTimer(hWnd, TIMER_LOAD);
				//MessageBox(hWnd, L"No more targets", L"No more targets", MB_OK);
				// path drawing
				// graph drawing
				// statistics output
				// statistics log

				InvalidateRect(hWnd, NULL, TRUE);
			}
			else
			{
				target.SetCenter(converter.ToCoord_FromLogCoordString(nextLine));
				// convert to float point
				// convert to coordinates from angles
				// log angles
			}
		}
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
		renderTarget->BeginDraw();
		renderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));

		xAxis.Draw(renderTarget, ProjConst::DEF_AXIS_COLOR);
		yAxis.Draw(renderTarget, ProjConst::DEF_AXIS_COLOR);
		target.Draw(renderTarget, ProjConst::DEF_TARGET_COLOR);
		cursor.Draw(renderTarget, ProjConst::DEF_CURSOR_COLOR);
		if (!isGame)
		{
			PathDrawer drawer("coords.txt", converter);
			drawer.Draw(renderTarget, ProjConst::DEF_PATH_COLOR);
		}

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

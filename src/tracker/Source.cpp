#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <iostream>
#include <d2d1.h>

#include "config\\Constants.h"

#include "data\\header\\Network.h"
#include "data\\header\\Logger.h"
#include "data\\header\\FileReader.h"

#include "calculations\\header\\Converter.h"

#include "view\\header\\Cursor.h"
#include "view\\header\\Target.h"
#include "view\\header\\Axis.h"
#include "view\\header\\PathDrawer.h"
#include "view\\header\\Graph.h"

constexpr auto TIMER_LOG = 1;
constexpr auto TIMER_LOAD = 2;
constexpr auto TIMER_TARGET = 3;
constexpr auto TIMER_PAINT = 4;
constexpr auto TIMER_CALIBRATION = 5;

constexpr auto BTN_START = 1;
constexpr auto TXT_IP = 2;
constexpr auto BTN_CALIBRATION = 3;
constexpr auto TXT_ANGLE_X = 4;
constexpr auto TXT_ANGLE_Y = 5;
constexpr auto BTN_CALIBRATE_X = 6;
constexpr auto BTN_CALIBRATE_Y = 7;
constexpr auto BTN_CENTRALIZE = 8;

// def rb = 704, 681
Cursor cursor(0, 0, ProjConst::CURSOR_RADIUS, { 0,0,0,0 });
Cursor enemy(0, 0, 10, { 0,0,0,0 });
Target target(0, 0, 20, { 0,0,0,0 });

// User data
Logger user_RealLogger("data\\user\\realCoords.txt", ' ');
Logger user_CoordLogger("data\\user\\coords.txt", ' ');
Logger user_AngleLogger("data\\user\\angles.txt", ' ');
Logger user_RadianLogger("data\\user\\radians.txt", ' ');

// Enemy data
Logger enemy_RealLogger("data\\enemy\\realCoords.txt", ' ');
Logger enemy_CoordLogger("data\\enemy\\coords.txt", ' ');
Logger enemy_AngleLogger("data\\enemy\\angles.txt", ' ');
Logger enemy_RadianLogger("data\\enemy\\radians.txt", ' ');

FileReader reader("data\\target\\target.txt");

bool isCalibrating = false;
bool isCalibratingX = false;
bool isCalibratingY = false;

bool isLeftPressed = false;
bool isRightPressed = false;
bool isUpPressed = false;
bool isDownPressed = false;

bool isGame = true;

long userPoints = 0;
long enemyPoints = 0;

float maxXAngle = ProjConst::DEF_MAX_X_ANGLE;
float maxYAngle = ProjConst::DEF_MAX_Y_ANGLE;

float centerAngleX = 0;
float centerAngleY = 0;

ID2D1HwndRenderTarget* renderTarget;
ID2D1Factory* d2dFactory;
D2D1_RENDER_TARGET_PROPERTIES renderProps = D2D1::RenderTargetProperties
(
	D2D1_RENDER_TARGET_TYPE_HARDWARE,
	D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED)
);

HWND hTxtIP, hTxtAngleX, hTxtAngleY, hBtnCalibrateX, hBtnCalibrateY;
HWND hWndMain, hWndPaint;

LRESULT CALLBACK WndProcPaint(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WndProcMain(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

// Network multithreading
POINTFLOAT currentAngles;
HANDLE hThread;
BOOL isReceiving = false;
static DWORD WINAPI NetworkThread(LPVOID lpParam)
{
	POINTFLOAT radianPoint;

	Network network(Network::GetIp(hTxtIP), ProjConst::DEF_PORT);
	network.Connect();

	while (isReceiving)
	{
		if (network.NextXY(radianPoint))
		{
			currentAngles = Converter::ToAngle_FromRadian(radianPoint);
			currentAngles.x += centerAngleX;
			currentAngles.y += centerAngleY;
		}
	}

	return 0;
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wcexMain
	{
		sizeof(WNDCLASSEX), CS_DBLCLKS, WndProcMain, 0, 0, hInstance, LoadIcon(NULL, IDI_APPLICATION),
		LoadCursor(NULL, IDC_ARROW), HBRUSH(CreateSolidBrush(ProjConst::WND_DEF_COLOR)), NULL, ProjConst::MAIN_WND_NAME,
		wcexMain.hIcon
	};
	WNDCLASSEX wcexPaint
	{
		sizeof(WNDCLASSEX), CS_DBLCLKS, WndProcPaint, 0, 0, hInstance, LoadIcon(NULL, IDI_APPLICATION),
		LoadCursor(NULL, IDC_ARROW), HBRUSH(CreateSolidBrush(ProjConst::WND_DEF_COLOR)), NULL, ProjConst::PROJ_NAME,
		wcexPaint.hIcon
	};
	MSG msg;

	RegisterClassEx(&wcexMain);

	// Initial window
	hWndMain = CreateWindow(wcexMain.lpszClassName, ProjConst::WND_CAPTION, WS_SYSMENU,
		CW_USEDEFAULT, CW_USEDEFAULT, ProjConst::WND_DEF_WIDTH, ProjConst::WND_DEF_HEIGHT,
		NULL, NULL, hInstance, NULL);

	// Text box
	int xCoord = ProjConst::WND_DEF_WIDTH / 2 - ProjConst::CONTROL_DEF_WIDTH / 2;
	hTxtIP = CreateWindowEx(0, L"EDIT", L"192.168.150.3", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL,
		xCoord, 50, ProjConst::CONTROL_DEF_WIDTH, ProjConst::CONTROL_DEF_HEIGHT, hWndMain, (HMENU)TXT_IP, hInstance, NULL);
	hTxtAngleX = CreateWindowEx(0, L"EDIT", L"20.0", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, xCoord, 130,
		ProjConst::CONTROL_DEF_WIDTH, ProjConst::CONTROL_DEF_HEIGHT, hWndMain, (HMENU)TXT_ANGLE_X, hInstance, NULL);
	hTxtAngleY = CreateWindowEx(0, L"EDIT", L"20.0", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, xCoord, 270,
		ProjConst::CONTROL_DEF_WIDTH, ProjConst::CONTROL_DEF_HEIGHT, hWndMain, (HMENU)TXT_ANGLE_Y, hInstance, NULL);

	// Button
	hBtnCalibrateX = CreateWindowEx(0, L"BUTTON", L"Calibrate X", WS_VISIBLE | WS_CHILD | WS_DISABLED, xCoord, 170,
		ProjConst::CONTROL_DEF_WIDTH, ProjConst::BTN_DEF_HEIGHT, hWndMain, (HMENU)BTN_CALIBRATE_X, hInstance, NULL);
	hBtnCalibrateY = CreateWindowEx(0, L"BUTTON", L"Calibrate Y", WS_VISIBLE | WS_CHILD | WS_DISABLED, xCoord, 310,
		ProjConst::CONTROL_DEF_WIDTH, ProjConst::BTN_DEF_HEIGHT, hWndMain, (HMENU)BTN_CALIBRATE_Y, hInstance, NULL);
	CreateWindowEx(0, L"BUTTON", L"Centralize", WS_VISIBLE | WS_CHILD, xCoord, 370,
		ProjConst::CONTROL_DEF_WIDTH, ProjConst::BTN_DEF_HEIGHT, hWndMain, (HMENU)BTN_CENTRALIZE, hInstance, NULL);
	CreateWindowEx(0, L"BUTTON", L"Calibration", WS_VISIBLE | WS_CHILD, xCoord, 430, ProjConst::CONTROL_DEF_WIDTH,
		ProjConst::BTN_DEF_HEIGHT, hWndMain, (HMENU)BTN_CALIBRATION, hInstance, NULL);
	CreateWindowEx(0, L"BUTTON", L"Start", WS_VISIBLE | WS_CHILD, xCoord, 490, ProjConst::CONTROL_DEF_WIDTH,
		ProjConst::BTN_DEF_HEIGHT, hWndMain, (HMENU)BTN_START, hInstance, NULL);

	// Label
	CreateWindowEx(0, L"STATIC", L"IP", WS_CHILD | WS_VISIBLE, xCoord, 10, ProjConst::CONTROL_DEF_WIDTH,
		ProjConst::CONTROL_DEF_HEIGHT, hWndMain, NULL, hInstance, NULL);
	CreateWindowEx(0, L"STATIC", L"Max X angle", WS_CHILD | WS_VISIBLE, xCoord, 90, ProjConst::CONTROL_DEF_WIDTH,
		ProjConst::CONTROL_DEF_HEIGHT, hWndMain, NULL, hInstance, NULL);
	CreateWindowEx(0, L"STATIC", L"Max Y angle", WS_CHILD | WS_VISIBLE, xCoord, 230, ProjConst::CONTROL_DEF_WIDTH,
		ProjConst::CONTROL_DEF_HEIGHT, hWndMain, NULL, hInstance, NULL);

	RegisterClassEx(&wcexPaint);

	hWndPaint = CreateWindow(wcexPaint.lpszClassName, ProjConst::WND_CAPTION, WS_SYSMENU | WS_MAXIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT, ProjConst::WND_DEF_WIDTH, ProjConst::WND_DEF_HEIGHT, NULL, NULL, hInstance, NULL);

	ShowWindow(hWndMain, nCmdShow);
	UpdateWindow(hWndMain);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}

LRESULT CALLBACK WndProcMain(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
		if (LOWORD(wParam) == BTN_START)
		{
			userPoints = 0;
			enemyPoints = 0;

			KillTimer(hWnd, TIMER_CALIBRATION);

			isGame = true;
			isReceiving = true;

			if (hThread == NULL)
			{
				hThread = CreateThread(NULL, 0, NetworkThread, NULL, 0, NULL);
			}
			if (hThread == NULL)
			{
				return 1;
			}

			SetTimer(hWndPaint, TIMER_LOG, ProjConst::DEF_TIMER_TIME, NULL);
			SetTimer(hWndPaint, TIMER_LOAD, ProjConst::DEF_TIMER_TIME, NULL);
			SetTimer(hWndPaint, TIMER_PAINT, ProjConst::DEF_TIMER_TIME, NULL);

			target.SetCenter(Converter::ToCoord(reader.ReadLn()));
			target.SetDelay(Converter::GetValue(reader.ReadLn()));
			SetTimer(hWndPaint, TIMER_TARGET, target.GetDelay(), NULL);

			ShowWindow(hWndMain, SW_HIDE);
			ShowWindow(hWndPaint, SW_SHOW);
		}
		else if (LOWORD(wParam) == BTN_CALIBRATION)
		{
			if (isCalibrating)
			{
				KillTimer(hWnd, TIMER_CALIBRATION);

				isReceiving = false;
				WaitForSingleObject(hThread, ProjConst::TIMER_WAITING);
				CloseHandle(hThread);

				EnableWindow(hBtnCalibrateX, FALSE);
				EnableWindow(hBtnCalibrateY, FALSE);

				isCalibratingX = false;
				isCalibratingY = false;
				isCalibrating = false;
			}
			else
			{
				SetTimer(hWnd, TIMER_CALIBRATION, ProjConst::DEF_TIMER_TIME, NULL);

				isReceiving = true;

				hThread = CreateThread(NULL, 0, NetworkThread, NULL, 0, NULL);
				if (hThread == NULL)
				{
					return 1;
				}

				EnableWindow(hBtnCalibrateX, TRUE);
				EnableWindow(hBtnCalibrateY, TRUE);

				isCalibratingX = true;
				isCalibratingY = true;
				isCalibrating = true;
			}
		}
		else if (LOWORD(wParam) == BTN_CALIBRATE_X)
		{
			maxXAngle = std::abs(Converter::GetFloat_FromWindowText(hTxtAngleX)) + ProjConst::DX_ANGLE;

			EnableWindow(hBtnCalibrateX, FALSE);

			isCalibratingX = false;
		}
		else if (LOWORD(wParam) == BTN_CALIBRATE_Y)
		{
			maxYAngle = std::abs(Converter::GetFloat_FromWindowText(hTxtAngleY)) + ProjConst::DY_ANGLE;

			EnableWindow(hBtnCalibrateY, FALSE);

			isCalibratingY = false;
		}
		else if (LOWORD(wParam) == BTN_CENTRALIZE)
		{
			centerAngleX = -Converter::GetFloat_FromWindowText(hTxtAngleX);
			centerAngleY = -Converter::GetFloat_FromWindowText(hTxtAngleY);
		}
		break;
	case WM_TIMER:
		if (wParam == TIMER_CALIBRATION)
		{
			wchar_t buffer[50];

			if (isCalibratingX)
			{
				_snwprintf_s(buffer, 50, L"%.2f", currentAngles.x);
				SetWindowTextW(hTxtAngleX, buffer);
			}

			if (isCalibratingY)
			{
				_snwprintf_s(buffer, 50, L"%.2f", currentAngles.y);
				SetWindowTextW(hTxtAngleY, buffer);
			}
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

LRESULT CALLBACK WndProcPaint(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	RECT clientRect;
	GetClientRect(hWnd, &clientRect);

	Converter converter(clientRect.right, clientRect.bottom, maxXAngle, maxYAngle);

	Axis xAxis(clientRect.left, clientRect.bottom / 2, clientRect.right, clientRect.bottom / 2);
	Axis yAxis(clientRect.right / 2, clientRect.top, clientRect.right / 2, clientRect.bottom);

	switch (message)
	{
	case WM_CREATE:
		D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &d2dFactory);

		cursor.SetCenter({ clientRect.right / 2, clientRect.bottom / 2 });
		cursor.SetOldRect(clientRect);
		target.SetOldRect(clientRect);
		enemy.SetOldRect(clientRect);
		break;
	WM_SHOW:
		cursor.SetCenter({ clientRect.right / 2, clientRect.bottom / 2 });
		cursor.SetOldRect(clientRect);
		target.SetOldRect(clientRect);
		enemy.SetOldRect(clientRect);
		break;
	case WM_SIZE:
		D2D1_SIZE_U size = D2D1::SizeU(clientRect.right - clientRect.left, clientRect.bottom - clientRect.top);
		d2dFactory->CreateHwndRenderTarget(renderProps, D2D1::HwndRenderTargetProperties(hWnd, size), &renderTarget);

		cursor.Scale(clientRect);
		enemy.Scale(clientRect);
		target.Scale(clientRect);
		break;
	case WM_LBUTTONDOWN:
		enemy.SetCenter(POINT{ 0, 0 });
		cursor.SetCenter({ 0, 0 });

		isGame = false;
		isReceiving = false;

		KillTimer(hWnd, TIMER_LOG);
		KillTimer(hWnd, TIMER_LOAD);
		KillTimer(hWnd, TIMER_TARGET);
		KillTimer(hWnd, TIMER_PAINT);

		WaitForSingleObject(hThread, ProjConst::TIMER_WAITING);
		CloseHandle(hThread);
		hThread = NULL;

		if (userPoints > enemyPoints)
		{
			MessageBox(hWnd, L"User won", L"Congratulations", MB_OK);
		}
		else
		{
			MessageBox(hWnd, L"Enemy won", L"Sorry", MB_OK);
		}

		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_TIMER:
		if (wParam == TIMER_LOG)
		{
			int xSpeed = 0;
			int ySpeed = 0;
			int speed = ProjConst::SPEED;

			POINT center = cursor.Shot();

			user_AngleLogger.LogLn(converter.ToAngle(center));
			user_CoordLogger.LogLn(converter.ToLogCoord(center));
			user_RealLogger.LogLn(center);
			user_RadianLogger.LogLn(converter.ToRadian_FromAngle(converter.ToAngle(center)));

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

			if (enemy.Contains(cursor.Shot()))
			{
				userPoints += ProjConst::DEF_ENEMY_POINTS_INC;
			}
		}

		if (wParam == TIMER_LOAD)
		{
			POINTFLOAT nextPoint;
			POINT newCenter;

			nextPoint = currentAngles;
			newCenter = converter.ToCoord(nextPoint);

			enemy.SetCenter(newCenter);

			if (target.Contains(enemy.Shot()))
			{
				enemyPoints += ProjConst::DEF_ENEMY_POINTS_INC;
			}

			enemy_CoordLogger.LogLn(converter.ToLogCoord(newCenter));
			enemy_AngleLogger.LogLn(nextPoint);
			enemy_RealLogger.LogLn(newCenter);
			enemy_RadianLogger.LogLn(converter.ToRadian_FromAngle(nextPoint));

			wchar_t buffer[50];
			_snwprintf_s(buffer, 50, L"%d %d", userPoints, enemyPoints);
			SetWindowTextW(hWnd, buffer);
		}
		if (wParam == TIMER_PAINT)
		{
			InvalidateRect(hWnd, NULL, TRUE);
		}
		if (wParam == TIMER_TARGET)
		{
			target.SetCenter(Converter::ToCoord(reader.ReadLn()));
			target.SetDelay(Converter::GetValue(reader.ReadLn()));

			KillTimer(hWnd, TIMER_TARGET);
			SetTimer(hWnd, TIMER_TARGET, target.GetDelay(), NULL);
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
		enemy.Draw(renderTarget, ProjConst::DEF_TARGET_COLOR);
		cursor.Draw(renderTarget, ProjConst::DEF_CURSOR_COLOR);
		target.Draw(renderTarget, D2D1::ColorF::Green);

		if (!isGame)
		{
			//Graph enemy_graph("data\\enemy\\coords.txt", converter);
			//enemy_graph.DrawWindRose(renderTarget, D2D1::ColorF::DarkSlateGray, converter, 4, 360);

			Graph user_graph("data\\user\\coords.txt", converter);
			user_graph.DrawWindRose(renderTarget, D2D1::ColorF::DimGray, converter, 4, 360);

			PathDrawer enemy_drawer("data\\enemy\\coords.txt", converter);
			enemy_drawer.Draw(renderTarget, D2D1::ColorF::Blue);

			PathDrawer user_drawer("data\\user\\coords.txt", converter);
			user_drawer.Draw(renderTarget, D2D1::ColorF::Red);
		}

		renderTarget->EndDraw();

		EndPaint(hWnd, &ps);
		break;
	case WM_CLOSE:
		isGame = false;
		isReceiving = false;

		KillTimer(hWnd, TIMER_LOG);
		KillTimer(hWnd, TIMER_LOAD);
		KillTimer(hWnd, TIMER_TARGET);
		KillTimer(hWnd, TIMER_PAINT);

		if (hThread != NULL)
		{
			WaitForSingleObject(hThread, ProjConst::TIMER_WAITING);
			CloseHandle(hThread);
			hThread = NULL;
		}

		ShowWindow(hWndPaint, SW_HIDE);
		ShowWindow(hWndMain, SW_SHOW);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

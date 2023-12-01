#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <iostream>
#include <d2d1.h>

#include "Control.h"

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

Cursor cursor(0, 0, constant::CURSOR_RADIUS, { 0, 0, 0, 0 }, constant::SPEED);
Target enemy(0, 0, constant::ENEMY_RADIUS, { 0, 0, 0, 0 });
Target target(0, 0, constant::TARGET_RADIUS, { 0, 0, 0, 0 });

// User data
Logger user_RealLogger(constant::FILEPATH_USER_REAL_COORDINATES, constant::DEF_SEPARATOR);
Logger user_CoordLogger(constant::FILEPATH_USER_COORDINATES, constant::DEF_SEPARATOR);
Logger user_AngleLogger(constant::FILEPATH_USER_ANGLES, constant::DEF_SEPARATOR);
Logger user_RadianLogger(constant::FILEPATH_USER_RADIANS, constant::DEF_SEPARATOR);

// Enemy data
Logger enemy_RealLogger(constant::FILEPATH_ENEMY_REAL_COORDINATES, constant::DEF_SEPARATOR);
Logger enemy_CoordLogger(constant::FILEPATH_ENEMY_COORDINATES, constant::DEF_SEPARATOR);
Logger enemy_AngleLogger(constant::FILEPATH_ENEMY_ANGLES, constant::DEF_SEPARATOR);
Logger enemy_RadianLogger(constant::FILEPATH_ENEMY_RADIANS, constant::DEF_SEPARATOR);

// Target coordinates
FileReader reader(constant::FILEPATH_TARGET_COORDINATES);

// Constols scaling
Control* scaler;

BOOL isCalibrating = FALSE;
BOOL isCalibratingX = FALSE;
BOOL isCalibratingY = FALSE;

BOOL isLeftPressed = FALSE;
BOOL isRightPressed = FALSE;
BOOL isUpPressed = FALSE;
BOOL isDownPressed = FALSE;

BOOL isGame = TRUE;

LONG userPoints = 0;
LONG enemyPoints = 0;

FLOAT maxXAngle = constant::DEF_MAX_X_ANGLE;
FLOAT maxYAngle = constant::DEF_MAX_Y_ANGLE;

FLOAT centerAngleX = 0;
FLOAT centerAngleY = 0;

ID2D1HwndRenderTarget* renderTarget;
ID2D1Factory* d2dFactory;
D2D1_RENDER_TARGET_PROPERTIES renderProps = D2D1::RenderTargetProperties
(
	D2D1_RENDER_TARGET_TYPE_HARDWARE,
	D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED)
);

HWND hWndMain, hWndPaint;

LRESULT CALLBACK WndProcPaint(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WndProcMain(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

// Network multithreading
HANDLE hThread;
POINTFLOAT currentAngles;
BOOL isReceiving = FALSE;
static DWORD WINAPI NetworkThread(LPVOID lpParam)
{
	POINTFLOAT radianPoint;

	Network network(constant::DEF_IP, constant::DEF_PORT);
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

INT APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wcexMain
	{
		sizeof(WNDCLASSEX), CS_DBLCLKS, WndProcMain, 0, 0, hInstance, LoadIcon(NULL, IDI_APPLICATION),
		LoadCursor(NULL, IDC_ARROW), HBRUSH(CreateSolidBrush(constant::WND_DEF_COLOR)), NULL, constant::MAIN_WND_NAME,
		wcexMain.hIcon
	};
	WNDCLASSEX wcexPaint
	{
		sizeof(WNDCLASSEX), CS_DBLCLKS, WndProcPaint, 0, 0, hInstance, LoadIcon(NULL, IDI_APPLICATION),
		LoadCursor(NULL, IDC_ARROW), NULL, NULL, constant::PAINT_WND_NAME,
		wcexPaint.hIcon
	};
	MSG msg;

	RegisterClassEx(&wcexMain);

	// Initial window
	hWndMain = CreateWindow(wcexMain.lpszClassName, constant::MAIN_WND_NAME, WS_SYSMENU,
		CW_USEDEFAULT, CW_USEDEFAULT, constant::WND_DEF_WIDTH, constant::WND_DEF_HEIGHT,
		NULL, NULL, hInstance, NULL);

	INT resolutionArrSize = sizeof(constant::SCREEN_WIDTH) / sizeof(constant::SCREEN_WIDTH[0]);
	INT screenWidth = GetSystemMetrics(SM_CXSCREEN);
	INT screenHeight = GetSystemMetrics(SM_CYSCREEN);
	scaler = new Control(hWndMain);

	// Text box
	INT xCoord = constant::WND_DEF_WIDTH / 2 - constant::CONTROL_DEF_WIDTH / 2;
	//HWND hTxtIP = CreateWindowEx(0, L"EDIT", constant::DEF_IP, WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, xCoord, 50,
	//	constant::CONTROL_DEF_WIDTH, constant::CONTROL_DEF_HEIGHT, hWndMain, (HMENU)constant::TXT_IP, hInstance, NULL);
	//SendMessage(hTxtIP, WM_SETFONT, (WPARAM)constant::DEF_FONT, TRUE);
	HWND hTxtAngleX = CreateWindowEx(0, L"EDIT", constant::DEF_MAX_X_ANGLE_STR, WS_VISIBLE | WS_CHILD | WS_BORDER | 
		ES_AUTOHSCROLL, xCoord, 50, constant::CONTROL_DEF_WIDTH, constant::CONTROL_DEF_HEIGHT, hWndMain, 
		(HMENU)constant::TXT_ANGLE_X, hInstance, NULL);
	SendMessage(hTxtAngleX, WM_SETFONT, (WPARAM)constant::DEF_FONT, TRUE);
	HWND hTxtAngleY = CreateWindowEx(0, L"EDIT", constant::DEF_MAX_Y_ANGLE_STR, WS_VISIBLE | WS_CHILD | WS_BORDER | 
		ES_AUTOHSCROLL, xCoord, 190, constant::CONTROL_DEF_WIDTH, constant::CONTROL_DEF_HEIGHT, hWndMain, 
		(HMENU)constant::TXT_ANGLE_Y, hInstance, NULL);
	SendMessage(hTxtAngleY, WM_SETFONT, (WPARAM)constant::DEF_FONT, TRUE);

	// Button
	HWND hBtnCalibrateX = CreateWindowEx(0, L"BUTTON", L"Calibrate X", WS_VISIBLE | WS_CHILD | WS_DISABLED, xCoord, 90,
		constant::CONTROL_DEF_WIDTH, constant::BTN_DEF_HEIGHT, hWndMain, (HMENU)constant::BTN_CALIBRATE_X, hInstance, NULL);
	SendMessage(hBtnCalibrateX, WM_SETFONT, (WPARAM)constant::DEF_FONT, TRUE);
	HWND hBtnCalibrateY = CreateWindowEx(0, L"BUTTON", L"Calibrate Y", WS_VISIBLE | WS_CHILD | WS_DISABLED, xCoord, 240,
		constant::CONTROL_DEF_WIDTH, constant::BTN_DEF_HEIGHT, hWndMain, (HMENU)constant::BTN_CALIBRATE_Y, hInstance, NULL);
	SendMessage(hBtnCalibrateY, WM_SETFONT, (WPARAM)constant::DEF_FONT, TRUE);
	HWND hBtnCentralize = CreateWindowEx(0, L"BUTTON", L"Centralize", WS_VISIBLE | WS_CHILD, xCoord, 290,
		constant::CONTROL_DEF_WIDTH, constant::BTN_DEF_HEIGHT, hWndMain, (HMENU)constant::BTN_CENTRALIZE, hInstance, NULL);
	SendMessage(hBtnCentralize, WM_SETFONT, (WPARAM)constant::DEF_FONT, TRUE);
	HWND hBtnCalibration = CreateWindowEx(0, L"BUTTON", L"Calibration", WS_VISIBLE | WS_CHILD, xCoord, 350, 
		constant::CONTROL_DEF_WIDTH, constant::BTN_DEF_HEIGHT, hWndMain, (HMENU)constant::BTN_CALIBRATION, hInstance, NULL);
	SendMessage(hBtnCalibration, WM_SETFONT, (WPARAM)constant::DEF_FONT, TRUE);
	HWND hBtnStart = CreateWindowEx(0, L"BUTTON", L"Start", WS_VISIBLE | WS_CHILD, xCoord, 410, constant::CONTROL_DEF_WIDTH,
		constant::BTN_DEF_HEIGHT, hWndMain, (HMENU)constant::BTN_START, hInstance, NULL);
	SendMessage(hBtnStart, WM_SETFONT, (WPARAM)constant::DEF_FONT, TRUE);

	// Label
	//HWND hLblIP = CreateWindowEx(0, L"STATIC", L"IP", WS_CHILD | WS_VISIBLE, xCoord, 10, constant::CONTROL_DEF_WIDTH,
	//	constant::CONTROL_DEF_HEIGHT, hWndMain, NULL, hInstance, NULL);
	//SendMessage(hLblIP, WM_SETFONT, (WPARAM)constant::DEF_FONT, TRUE);
	HWND hLblAngleX = CreateWindowEx(0, L"STATIC", L"X angle", WS_CHILD | WS_VISIBLE, xCoord, 10, constant::CONTROL_DEF_WIDTH,
		constant::CONTROL_DEF_HEIGHT, hWndMain, (HMENU)constant::LBL_ANGLE_X, hInstance, NULL);
	SendMessage(hLblAngleX, WM_SETFONT, (WPARAM)constant::DEF_FONT, TRUE);
	HWND hLblAngleY = CreateWindowEx(0, L"STATIC", L"Y angle", WS_CHILD | WS_VISIBLE, xCoord, 150, constant::CONTROL_DEF_WIDTH,
		constant::CONTROL_DEF_HEIGHT, hWndMain, (HMENU)constant::LBL_ANGLE_Y, hInstance, NULL);
	SendMessage(hLblAngleY, WM_SETFONT, (WPARAM)constant::DEF_FONT, TRUE);

	// Combo box
	HWND hResolution = CreateWindowEx(0, L"COMBOBOX", NULL, WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST, 10, 10, 
		constant::CONTROL_DEF_WIDTH, constant::CONTROL_DEF_HEIGHT * resolutionArrSize, hWndMain, (HMENU)constant::CB_RESOLUTION, 
		NULL, NULL);
	SendMessage(hResolution, WM_SETFONT, (WPARAM)constant::DEF_FONT, TRUE);

	if (hResolution != NULL)
	{
		TCHAR buffer[32];
		for (INT i = 0; i < resolutionArrSize && constant::SCREEN_WIDTH[i] <= screenWidth && 
			constant::SCREEN_HEIGHT[i] <= screenHeight; i++)
		{
			wsprintf(buffer, L"%d X %d", constant::SCREEN_WIDTH[i], constant::SCREEN_HEIGHT[i]);
			SendMessage(hResolution, CB_ADDSTRING, 0, (LPARAM)buffer);
		}

		SendMessage(hResolution, CB_SETCURSEL, 0, 0);
	}

	RegisterClassEx(&wcexPaint);

	hWndPaint = CreateWindow(wcexPaint.lpszClassName, constant::PAINT_WND_NAME, WS_SYSMENU | WS_MAXIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT, constant::WND_DEF_WIDTH, constant::WND_DEF_HEIGHT, NULL, NULL, hInstance, NULL);

	ShowWindow(hWndMain, nCmdShow);
	UpdateWindow(hWndMain);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (INT)msg.wParam;
}

LRESULT CALLBACK WndProcMain(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HWND hComboBox;
	INT selectedIndex;

	switch (message)
	{
	case WM_SIZE:
		scaler->Scale(GetDlgItem(hWnd, constant::BTN_START));
		scaler->Scale(GetDlgItem(hWnd, constant::BTN_CALIBRATE_X));
		scaler->Scale(GetDlgItem(hWnd, constant::BTN_CALIBRATE_Y));
		scaler->Scale(GetDlgItem(hWnd, constant::BTN_CALIBRATION));
		scaler->Scale(GetDlgItem(hWnd, constant::BTN_CENTRALIZE));

		scaler->Scale(GetDlgItem(hWnd, constant::TXT_ANGLE_X));
		scaler->Scale(GetDlgItem(hWnd, constant::TXT_ANGLE_Y));

		scaler->Scale(GetDlgItem(hWnd, constant::LBL_ANGLE_X));
		scaler->Scale(GetDlgItem(hWnd, constant::LBL_ANGLE_Y));

		hComboBox = GetDlgItem(hWnd, constant::CB_RESOLUTION);
		scaler->ScaleComboBox(hComboBox, SendMessage(hComboBox, CB_GETCOUNT, 0, 0));

		scaler->UpdateClientRect();
		break;
	case WM_COMMAND:
		if (LOWORD(wParam) == constant::CB_RESOLUTION && HIWORD(wParam) == CBN_SELCHANGE)
		{
			selectedIndex = SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);

			SetWindowPos(hWnd, NULL, 0, 0, constant::SCREEN_WIDTH[selectedIndex], constant::SCREEN_HEIGHT[selectedIndex], 
				SWP_NOZORDER | SWP_NOACTIVATE);
			SetWindowPos(hWndPaint, NULL, 0, 0, constant::SCREEN_WIDTH[selectedIndex], constant::SCREEN_HEIGHT[selectedIndex],
				SWP_NOZORDER | SWP_NOACTIVATE);

			break;
		}
		if (LOWORD(wParam) == constant::BTN_START)
		{
			userPoints = 0;
			enemyPoints = 0;

			KillTimer(hWnd, constant::TIMER_CALIBRATION);

			isGame = TRUE;
			isReceiving = TRUE;

			if (hThread == NULL)
			{
				hThread = CreateThread(NULL, 0, NetworkThread, NULL, 0, NULL);
			}
			if (hThread == NULL)
			{
				return 1;
			}

			SetTimer(hWndPaint, constant::TIMER_LOG, constant::DEF_TIMER_TIME, NULL);
			SetTimer(hWndPaint, constant::TIMER_LOAD, constant::DEF_TIMER_TIME, NULL);
			SetTimer(hWndPaint, constant::TIMER_PAINT, constant::DEF_TIMER_TIME, NULL);

			target.SetCenter(Converter::ToCoord(reader.ReadLn()));
			target.SetDelay(Converter::GetValue(reader.ReadLn()));
			SetTimer(hWndPaint, constant::TIMER_TARGET, target.GetDelay(), NULL);

			ShowWindow(hWndMain, SW_HIDE);
			ShowWindow(hWndPaint, SW_SHOW);
		}
		else if (LOWORD(wParam) == constant::BTN_CALIBRATION)
		{
			if (isCalibrating)
			{
				KillTimer(hWnd, constant::TIMER_CALIBRATION);

				isReceiving = FALSE;
				WaitForSingleObject(hThread, constant::TIMER_WAITING);
				CloseHandle(hThread);

				EnableWindow(GetDlgItem(hWnd, constant::BTN_CALIBRATE_X), FALSE);
				EnableWindow(GetDlgItem(hWnd, constant::BTN_CALIBRATE_Y), FALSE);

				isCalibratingX = FALSE;
				isCalibratingY = FALSE;
				isCalibrating = FALSE;
			}
			else
			{
				SetTimer(hWnd, constant::TIMER_CALIBRATION, constant::DEF_TIMER_TIME, NULL);

				isReceiving = TRUE;

				hThread = CreateThread(NULL, 0, NetworkThread, NULL, 0, NULL);
				if (hThread == NULL)
				{
					return 1;
				}

				EnableWindow(GetDlgItem(hWnd, constant::BTN_CALIBRATE_X), TRUE);
				EnableWindow(GetDlgItem(hWnd, constant::BTN_CALIBRATE_Y), TRUE);

				isCalibratingX = TRUE;
				isCalibratingY = TRUE;
				isCalibrating = TRUE;
			}
		}
		else if (LOWORD(wParam) == constant::BTN_CALIBRATE_X)
		{
			maxXAngle = std::abs(Converter::GetFloat_FromWindowText(GetDlgItem(hWnd, constant::TXT_ANGLE_X))) + constant::DX_ANGLE;

			EnableWindow(GetDlgItem(hWnd, constant::BTN_CALIBRATE_X), FALSE);

			isCalibratingX = FALSE;
		}
		else if (LOWORD(wParam) == constant::BTN_CALIBRATE_Y)
		{
			maxYAngle = std::abs(Converter::GetFloat_FromWindowText(GetDlgItem(hWnd, constant::TXT_ANGLE_Y))) + constant::DY_ANGLE;

			EnableWindow(GetDlgItem(hWnd, constant::BTN_CALIBRATE_Y), FALSE);

			isCalibratingY = FALSE;
		}
		else if (LOWORD(wParam) == constant::BTN_CENTRALIZE)
		{
			centerAngleX = -Converter::GetFloat_FromWindowText(GetDlgItem(hWnd, constant::TXT_ANGLE_X));
			centerAngleY = -Converter::GetFloat_FromWindowText(GetDlgItem(hWnd, constant::TXT_ANGLE_Y));
		}
		break;
	case WM_TIMER:
		if (wParam == constant::TIMER_CALIBRATION)
		{
			wchar_t buffer[50];

			if (isCalibratingX)
			{
				_snwprintf_s(buffer, 50, L"%.2f", currentAngles.x);
				SetWindowTextW(GetDlgItem(hWnd, constant::TXT_ANGLE_X), buffer);
			}

			if (isCalibratingY)
			{
				_snwprintf_s(buffer, 50, L"%.2f", currentAngles.y);
				SetWindowTextW(GetDlgItem(hWnd, constant::TXT_ANGLE_Y), buffer);
			}
		}
		break;
	case WM_DESTROY:
		delete scaler;

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

		isGame = FALSE;
		isReceiving = FALSE;

		KillTimer(hWnd, constant::TIMER_LOG);
		KillTimer(hWnd, constant::TIMER_LOAD);
		KillTimer(hWnd, constant::TIMER_TARGET);
		KillTimer(hWnd, constant::TIMER_PAINT);

		WaitForSingleObject(hThread, constant::TIMER_WAITING);
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
		if (wParam == constant::TIMER_LOG)
		{
			POINT center = cursor.Shot();

			user_AngleLogger.LogLn(converter.ToAngle(center));
			user_CoordLogger.LogLn(converter.ToLogCoord(center));
			user_RealLogger.LogLn(center);
			user_RadianLogger.LogLn(converter.ToRadian_FromAngle(converter.ToAngle(center)));

			cursor.Move(isUpPressed, isRightPressed, isDownPressed, isLeftPressed, clientRect);

			if (enemy.Contains(cursor.Shot()))
			{
				userPoints += constant::DEF_ENEMY_POINTS_INC;
			}
		}

		if (wParam == constant::TIMER_LOAD)
		{
			POINTFLOAT nextPoint;
			POINT newCenter;

			nextPoint = currentAngles;
			newCenter = converter.ToCoord(nextPoint);

			enemy.SetCenter(newCenter);

			if (target.Contains(enemy.GetCenter()))
			{
				enemyPoints += constant::DEF_ENEMY_POINTS_INC;
			}

			enemy_CoordLogger.LogLn(converter.ToLogCoord(newCenter));
			enemy_AngleLogger.LogLn(nextPoint);
			enemy_RealLogger.LogLn(newCenter);
			enemy_RadianLogger.LogLn(converter.ToRadian_FromAngle(nextPoint));

			wchar_t buffer[50];
			_snwprintf_s(buffer, 50, L"User points: %d | Enemy points: %d", userPoints, enemyPoints);
			SetWindowTextW(hWnd, buffer);
		}
		if (wParam == constant::TIMER_PAINT)
		{
			InvalidateRect(hWnd, NULL, TRUE);
		}
		if (wParam == constant::TIMER_TARGET)
		{
			target.SetCenter(Converter::ToCoord(reader.ReadLn()));
			target.SetDelay(Converter::GetValue(reader.ReadLn()));

			KillTimer(hWnd, constant::TIMER_TARGET);
			SetTimer(hWnd, constant::TIMER_TARGET, target.GetDelay(), NULL);
		}
		break;
	case WM_KEYDOWN:
		if (wParam == VK_LEFT)
		{
			isLeftPressed = TRUE;
		}
		if (wParam == VK_RIGHT)
		{
			isRightPressed = TRUE;
		}
		if (wParam == VK_UP)
		{
			isUpPressed = TRUE;
		}
		if (wParam == VK_DOWN)
		{
			isDownPressed = TRUE;
		}
		break;
	case WM_KEYUP:
		if (wParam == VK_LEFT)
		{
			isLeftPressed = FALSE;
		}
		if (wParam == VK_RIGHT)
		{
			isRightPressed = FALSE;
		}
		if (wParam == VK_UP)
		{
			isUpPressed = FALSE;
		}
		if (wParam == VK_DOWN)
		{
			isDownPressed = FALSE;
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		renderTarget->BeginDraw();

		renderTarget->Clear(constant::DEF_BACKGROUND_COLOR);

		xAxis.Draw(renderTarget, constant::DEF_AXIS_COLOR);
		yAxis.Draw(renderTarget, constant::DEF_AXIS_COLOR);
		target.Draw(renderTarget, constant::DEF_TARGET_COLOR);
		enemy.Draw(renderTarget, constant::DEF_ENEMY_COLOR);
		cursor.Draw(renderTarget, constant::DEF_CURSOR_COLOR);

		if (!isGame)
		{
			//Graph enemy_graph(constant::FILEPATH_ENEMY_COORDINATES, converter);
			//enemy_graph.DrawWindRose(renderTarget, constant::DEF_ENEMY_WINDROSE_COLOR, converter, constant::DEF_WINDROSE_SIDES,
			//	constant::CIRCLE_MAX_ANGLE);

			Graph user_graph(constant::FILEPATH_USER_COORDINATES, converter);
			user_graph.DrawWindRose(renderTarget, constant::DEF_USER_WINDROSE_COLOR, converter, constant::DEF_WINDROSE_SIDES,
				constant::CIRCLE_MAX_ANGLE);

			PathDrawer enemy_drawer(constant::FILEPATH_ENEMY_COORDINATES, converter);
			enemy_drawer.Draw(renderTarget, constant::DEF_ENEMY_COLOR);

			PathDrawer user_drawer(constant::FILEPATH_USER_COORDINATES, converter);
			user_drawer.Draw(renderTarget, constant::DEF_CURSOR_COLOR);
		}

		renderTarget->EndDraw();

		EndPaint(hWnd, &ps);
		break;
	case WM_CLOSE:
		cursor.SetCenter({ clientRect.right / 2, clientRect.bottom / 2 });

		isGame = FALSE;
		isReceiving = FALSE;

		KillTimer(hWnd, constant::TIMER_LOG);
		KillTimer(hWnd, constant::TIMER_LOAD);
		KillTimer(hWnd, constant::TIMER_TARGET);
		KillTimer(hWnd, constant::TIMER_PAINT);

		if (hThread != NULL)
		{
			WaitForSingleObject(hThread, constant::TIMER_WAITING);
			CloseHandle(hThread);
			hThread = NULL;
		}

		reader.Restart();

		user_AngleLogger.Restart();
		user_CoordLogger.Restart();
		user_RadianLogger.Restart();
		user_RealLogger.Restart();

		enemy_AngleLogger.Restart();
		enemy_CoordLogger.Restart();
		enemy_RadianLogger.Restart();
		enemy_RealLogger.Restart();

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

#pragma once

namespace ProjConst
{
	const LPCWSTR DEF_IP = L"192.168.150.2";

	const LPCWSTR DEF_MAX_X_ANGLE_STR = L"20.0";
	const LPCWSTR DEF_MAX_Y_ANGLE_STR = L"20.0";

	const int DEF_WINDROSE_SIDES = 4;
	const int CIRCLE_MAX_ANGLE = 360;

	const float DEF_MAX_X_ANGLE = 20.0f;
	const float DEF_MAX_Y_ANGLE = 20.0f;

	const int DEF_ENEMY_POINTS_INC = 5;
	const int DEF_USER_POINTS_INC = 10;

	// NAMES
	const wchar_t* PAINT_WND_NAME = L"Tracker";
	const wchar_t* MAIN_WND_NAME = L"Main";

	const int DEF_PANEL_WIDTH = 300;

	// DRAWING
	const int SPEED = 6;
	const float DIAGONAL_SPEED_CORRECTION = 1.41;

	// SIZES
	const int WND_DEF_HEIGHT = 600;
	const int WND_DEF_WIDTH = 800;

	const int CONTROL_DEF_WIDTH = 190;
	const int CONTROL_DEF_HEIGHT = 20;
	const int BTN_DEF_HEIGHT = CONTROL_DEF_HEIGHT * 2;

	const float DX_ANGLE = 1.0f;
	const float DY_ANGLE = 1.0f;

	const D2D1::ColorF DEF_ENEMY_COLOR = D2D1::ColorF::Blue;
	const D2D1::ColorF DEF_CURSOR_COLOR = D2D1::ColorF::Red;
	const D2D1::ColorF DEF_TARGET_COLOR = D2D1::ColorF::Green;

	const D2D1::ColorF DEF_AXIS_COLOR = D2D1::ColorF::Black;

	const D2D1::ColorF DEF_USER_WINDROSE_COLOR = D2D1::ColorF::DimGray;
	const D2D1::ColorF DEF_ENEMY_WINDROSE_COLOR = D2D1::ColorF::DarkSlateGray;

	const COLORREF WND_DEF_COLOR = RGB(255, 255, 255);
	const D2D1::ColorF DEF_BACKGROUND_COLOR = D2D1::ColorF::White;
	const int LOAD_TIMEOUT = 10;

	const int BORDER_BOTTOM = WND_DEF_HEIGHT - 40;
	const int BORDER_TOP = 0;
	const int BORDER_RIGHT = WND_DEF_WIDTH + 20;
	const int BORDER_LEFT = -35;

	const int DEF_TIMER_TIME = 20;
	const int DEF_PORT = 9998;
	const int TIMER_WAITING = 500;

	const int CURSOR_RADIUS = 5;
	const int ENEMY_RADIUS = 10;
	const int TARGET_RADIUS = 20;
}

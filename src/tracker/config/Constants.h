#pragma once

namespace ProjConst 
{
	// NAMES
	const wchar_t* PROJ_NAME = L"Tracker";
	const wchar_t* WND_CAPTION = L"Tracker";

	// DRAWING
	const int SPEED = 6;
	const float DIAGONAL_SPEED_CORRECTION = 1.41;

	// SIZES
	const int WND_DEF_HEIGHT = 540;
	const int WND_DEF_WIDTH = 920;
	const D2D1::ColorF DEF_ENEMY_COLOR = D2D1::ColorF::Green;
	const D2D1::ColorF DEF_CURSOR_COLOR = D2D1::ColorF::Red;
	const D2D1::ColorF DEF_TARGET_COLOR = D2D1::ColorF::Blue;
	const D2D1::ColorF DEF_AXIS_COLOR = D2D1::ColorF::Black;
	const D2D1::ColorF DEF_PATH_COLOR = D2D1::ColorF::Green;
	const D2D1::ColorF DEF_WINDROSE_COLOR = D2D1::ColorF::LightGray;

	const COLORREF WND_DEF_COLOR = RGB(255, 255, 255);
	const int LOAD_TIMEOUT = 10;

	const int BORDER_BOTTOM = WND_DEF_HEIGHT - 40;
	const int BORDER_TOP = 0;
	const int BORDER_RIGHT = WND_DEF_WIDTH + 20;
	const int BORDER_LEFT = -35;

	const int LOG_TIMEOUT = 20;

	const int CURSOR_RADIUS = 5;
}

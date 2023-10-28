#pragma once

namespace ProjConst 
{
	// NAMES
	const wchar_t* PROJ_NAME = L"Tracker";
	const wchar_t* WND_CAPTION = L"Tracker";

	// DRAWING
	const int SPEED = 5;
	const float DIAGONAL_SPEED_CORRECTION = 1.41;

	// SIZES
	const int WND_DEF_HEIGHT = 720;
	const int WND_DEF_WIDTH = 720;
	const D2D1::ColorF DEF_CURSOR_COLOR = D2D1::ColorF::Red;
	const D2D1::ColorF DEF_TARGET_COLOR = D2D1::ColorF::Blue;
	const D2D1::ColorF DEF_AXIS_COLOR = D2D1::ColorF::Black;

	const COLORREF WND_DEF_COLOR = RGB(255, 255, 255);
	const int LOAD_TIMEOUT = 40;

	const int BORDER_BOTTOM = WND_DEF_HEIGHT - 40;
	const int BORDER_TOP = 0;
	const int BORDER_RIGHT = WND_DEF_WIDTH + 20;
	const int BORDER_LEFT = -35;

	const int FPS_60 = 17;
	const int CURSOR_RADIUS = 5;
}

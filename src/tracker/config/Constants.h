#pragma once

#include <windows.h>
#include <string>

namespace constant
{
	const std::string DIRPATH_USER = "data\\user\\";
	const std::string DIRPATH_ENEMY = "data\\enemy\\";
	const std::string DIRPATH_TARGET = "data\\target\\";

	const std::string FILENAME_TARGET_COORDINATES = "target.txt";
	const std::string FILENAME_ANGLES = "angles.txt";
	const std::string FILENAME_COORDINATES = "coords.txt";
	const std::string FILENAME_REAL_COORDINATES = "realCoords.txt";
	const std::string FILENAME_RADIANS = "radians.txt";

	const std::string FILEPATH_TARGET_COORDINATES = DIRPATH_TARGET + FILENAME_TARGET_COORDINATES;

	const std::string FILEPATH_ENEMY_ANGLES = DIRPATH_ENEMY + FILENAME_ANGLES;
	const std::string FILEPATH_ENEMY_COORDINATES = DIRPATH_ENEMY + FILENAME_COORDINATES;
	const std::string FILEPATH_ENEMY_REAL_COORDINATES = DIRPATH_ENEMY + FILENAME_REAL_COORDINATES;
	const std::string FILEPATH_ENEMY_RADIANS = DIRPATH_ENEMY + FILENAME_RADIANS;

	const std::string FILEPATH_USER_ANGLES = DIRPATH_USER + FILENAME_ANGLES;
	const std::string FILEPATH_USER_COORDINATES = DIRPATH_USER + FILENAME_COORDINATES;
	const std::string FILEPATH_USER_REAL_COORDINATES = DIRPATH_USER + FILENAME_REAL_COORDINATES;
	const std::string FILEPATH_USER_RADIANS = DIRPATH_USER + FILENAME_RADIANS;

	const CHAR DEF_SEPARATOR = ' ';

	const INT TIMER_LOG = 1;
	const INT TIMER_LOAD = 2;
	const INT TIMER_TARGET = 3;
	const INT TIMER_PAINT = 4;
	const INT TIMER_CALIBRATION = 5;

	const INT BTN_START = 1;
	const INT TXT_IP = 2;
	const INT BTN_CALIBRATION = 3;
	const INT TXT_ANGLE_X = 4;
	const INT TXT_ANGLE_Y = 5;
	const INT BTN_CALIBRATE_X = 6;
	const INT BTN_CALIBRATE_Y = 7;
	const INT BTN_CENTRALIZE = 8;
	const INT LBL_ANGLE_X = 9;
	const INT LBL_ANGLE_Y = 10;
	const INT CB_RESOLUTION = 11;

	const INT SCREEN_WIDTH[]{ 800, 1280, 1600, 1920, 2560, 3200, 3840, 6016, 7680 };
	const INT SCREEN_HEIGHT[]{ 600, 720, 900, 1080, 1440, 1800, 2160, 3384, 4320 };

	const CHAR* DEF_IP = "192.168.150.2";

	const LPCWSTR DEF_MAX_X_ANGLE_STR = L"20.0";
	const LPCWSTR DEF_MAX_Y_ANGLE_STR = L"20.0";

	const INT DEF_WINDROSE_SIDES = 4;
	const INT CIRCLE_MAX_ANGLE = 360;

	const INT DEF_MAX_X_ANGLE = 20.0f;
	const INT DEF_MAX_Y_ANGLE = 20.0f;

	const INT DEF_ENEMY_POINTS_INC = 5;
	const INT DEF_USER_POINTS_INC = 10;

	// NAMES
	const LPCWSTR PAINT_WND_NAME = L"Tracker";
	const LPCWSTR MAIN_WND_NAME = L"Main";

	// DRAWING
	const INT SPEED = 5;

	// SIZES
	const INT WND_DEF_HEIGHT = 600;
	const INT WND_DEF_WIDTH = 800;

	const INT CONTROL_DEF_WIDTH = 190;
	const INT CONTROL_DEF_HEIGHT = 25;
	const INT BTN_DEF_HEIGHT = CONTROL_DEF_HEIGHT * 2;

	const FLOAT DX_ANGLE = 1.0f;
	const FLOAT DY_ANGLE = 1.0f;

	const D2D1::ColorF DEF_ENEMY_COLOR = D2D1::ColorF::Blue;
	const D2D1::ColorF DEF_CURSOR_COLOR = D2D1::ColorF::Red;
	const D2D1::ColorF DEF_TARGET_COLOR = D2D1::ColorF::Green;

	const D2D1::ColorF DEF_AXIS_COLOR = D2D1::ColorF::Black;

	const D2D1::ColorF DEF_USER_WINDROSE_COLOR = D2D1::ColorF::DimGray;
	const D2D1::ColorF DEF_ENEMY_WINDROSE_COLOR = D2D1::ColorF::DarkSlateGray;

	const D2D1::ColorF DEF_BACKGROUND_COLOR = D2D1::ColorF::White;
	const COLORREF WND_DEF_COLOR = RGB(255, 255, 255);

	const INT DEF_TIMER_TIME = 15;
	const INT DEF_PORT = 9998;
	const INT TIMER_WAITING = 500;

	const INT CURSOR_RADIUS = 5;
	const INT ENEMY_RADIUS = 10;
	const INT TARGET_RADIUS = 20;

	const HFONT DEF_FONT = CreateFont(
		20,								// Font size
		0,								// Sybol width (0 - by default)
		0,								// Angle
		0,								// Angle
		FW_DEMIBOLD,					// Bold
		FALSE,							// Italic
		FALSE,							// Underline
		FALSE,							// Strike
		DEFAULT_CHARSET,				// Charset
		OUT_DEFAULT_PRECIS,				// Out precis
		CLIP_DEFAULT_PRECIS,			// Clip precis
		DEFAULT_QUALITY,				// Quality
		DEFAULT_PITCH | FF_DONTCARE,	// Step and family
		L"Arial"						// Name
	);
}

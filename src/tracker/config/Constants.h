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

	constexpr auto DEF_SEPARATOR = ' ';

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

	const INT SCREEN_WIDTH[]{ 800, 1280, 1600, 1920, 2560, 3200, 3840, 6016, 7680 };
	const INT SCREEN_HEIGHT[]{ 600, 720, 900, 1080, 1440, 1800, 2160, 3384, 4320 };

	constexpr auto DEF_IP = L"192.168.150.2";

	constexpr auto DEF_MAX_X_ANGLE_STR = L"20.0";
	constexpr auto DEF_MAX_Y_ANGLE_STR = L"20.0";

	constexpr auto DEF_WINDROSE_SIDES = 4;
	constexpr auto CIRCLE_MAX_ANGLE = 360;

	constexpr auto DEF_MAX_X_ANGLE = 20.0f;
	constexpr auto DEF_MAX_Y_ANGLE = 20.0f;

	constexpr auto DEF_ENEMY_POINTS_INC = 5;
	constexpr auto DEF_USER_POINTS_INC = 10;

	// NAMES
	constexpr auto PAINT_WND_NAME = L"Tracker";
	constexpr auto MAIN_WND_NAME = L"Main";

	constexpr auto DEF_PANEL_WIDTH = 300;

	// DRAWING
	constexpr auto SPEED = 6;
	constexpr auto DIAGONAL_SPEED_CORRECTION = 1.41;

	// SIZES
	constexpr auto WND_DEF_HEIGHT = 600;
	constexpr auto WND_DEF_WIDTH = 800;

	constexpr auto CONTROL_DEF_WIDTH = 190;
	constexpr auto CONTROL_DEF_HEIGHT = 20;
	constexpr auto BTN_DEF_HEIGHT = CONTROL_DEF_HEIGHT * 2;

	constexpr auto DX_ANGLE = 1.0f;
	constexpr auto DY_ANGLE = 1.0f;

	const D2D1::ColorF DEF_ENEMY_COLOR = D2D1::ColorF::Blue;
	const D2D1::ColorF DEF_CURSOR_COLOR = D2D1::ColorF::Red;
	const D2D1::ColorF DEF_TARGET_COLOR = D2D1::ColorF::Green;

	const D2D1::ColorF DEF_AXIS_COLOR = D2D1::ColorF::Black;

	const D2D1::ColorF DEF_USER_WINDROSE_COLOR = D2D1::ColorF::DimGray;
	const D2D1::ColorF DEF_ENEMY_WINDROSE_COLOR = D2D1::ColorF::DarkSlateGray;

	const D2D1::ColorF DEF_BACKGROUND_COLOR = D2D1::ColorF::White;
	constexpr auto WND_DEF_COLOR = RGB(255, 255, 255);
	constexpr auto LOAD_TIMEOUT = 10;

	constexpr auto DEF_TIMER_TIME = 15;
	constexpr auto DEF_PORT = 9998;
	constexpr auto TIMER_WAITING = 500;

	constexpr auto CURSOR_RADIUS = 5;
	constexpr auto ENEMY_RADIUS = 10;
	constexpr auto TARGET_RADIUS = 20;
}

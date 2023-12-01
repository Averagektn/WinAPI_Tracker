#pragma once

#include <windows.h>

/// <summary>
///		Just for control scaling
/// </summary>
class Control
{
public:
	/// <summary>
	///		Control has its parent window
	/// </summary>
	/// <param name="hWnd">
	///		Parent window handle
	/// </param>
	Control(HWND hWnd);

	/// <summary>
	///		Scales specified control
	/// </summary>
	/// <param name="hControl">
	///		Control to scale
	/// </param>
	VOID Scale(HWND hControl);
	/// <summary>
	///		Scales combo box. Combo box height is calculated as: h = element height * number of elements
	/// </summary>
	/// <param name="hControl">
	///		Combo box handle
	/// </param>
	/// <param name="nItems">
	///		Number of combo box elements
	/// </param>
	VOID ScaleComboBox(HWND hControl, INT nItems);

	/// <summary>
	///		Sets new client rect sizes
	/// </summary>
	VOID UpdateClientRect();

	/// <summary>
	///		Sets new client rect size
	/// </summary>
	/// <param name="clientRect">
	///		New size
	/// </param>
	VOID SetClientRect(RECT clientRect);

	/// <summary>
	///		Sets new window handle
	/// </summary>
	/// <param name="hWnd">
	///		New window handle
	/// </param>
	VOID SetWindowHandle(HWND hWnd);

	/// <summary>
	///		Receiving window handle
	/// </summary>
	/// <returns>
	///		Window handle
	/// </returns>
	HWND GetWindowHandle() const;

	/// <summary>
	///		Receiving current client rect
	/// </summary>
	/// <returns>
	///		Current client rect
	/// </returns>
	RECT GetCurrentClientRect() const;
private:
	/// <summary>
	///		Scales fonts
	/// </summary>
	/// <param name="hControl">
	///		Control handle
	/// </param>
	/// <param name="xScale">
	///		X scaling multiplier
	/// </param>
	/// <param name="yScale">
	///		Y scaling multiplier
	/// </param>
	VOID ScaleFont(HWND hControl, FLOAT xScale, FLOAT yScale);

	HWND hWnd;
	RECT clientRect;
};

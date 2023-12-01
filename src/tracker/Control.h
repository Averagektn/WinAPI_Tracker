#pragma once

#include <windows.h>

/// <summary>
/// 
/// </summary>
class Control
{
public:
	/// <summary>
	/// 
	/// </summary>
	/// <param name="hWnd">
	/// 
	/// </param>
	Control(HWND hWnd);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="hControl">
	/// 
	/// </param>
	/// <returns>
	/// 
	/// </returns>
	VOID Scale(HWND hControl);
	/// <summary>
	/// 
	/// </summary>
	/// <param name="hControl">
	/// 
	/// </param>
	/// <param name="nItems">
	/// 
	/// </param>
	/// <returns>
	/// 
	/// </returns>
	VOID ScaleComboBox(HWND hControl, INT nItems);

	/// <summary>
	/// 
	/// </summary>
	/// <returns>
	/// 
	/// </returns>
	VOID UpdateClientRect();

	/// <summary>
	/// 
	/// </summary>
	/// <param name="clientRect">
	/// 
	/// </param>
	/// <returns>
	/// 
	/// </returns>
	VOID SetClientRect(RECT clientRect);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="hWnd">
	/// 
	/// </param>
	/// <returns>
	/// 
	/// </returns>
	VOID SetWindowHandler(HWND hWnd);

	/// <summary>
	/// 
	/// </summary>
	/// <returns>
	/// 
	/// </returns>
	HWND GetWindowHandler() const;

	/// <summary>
	/// 
	/// </summary>
	/// <returns>
	/// 
	/// </returns>
	RECT GetCurrentClientRect() const;
private:
	/// <summary>
	/// 
	/// </summary>
	/// <param name="hControl">
	/// 
	/// </param>
	/// <param name="xScale">
	/// 
	/// </param>
	/// <param name="yScale">
	/// 
	/// </param>
	/// <returns>
	/// 
	/// </returns>
	VOID ScaleFont(HWND hControl, FLOAT xScale, FLOAT yScale);

	HWND hWnd;
	RECT clientRect;
};

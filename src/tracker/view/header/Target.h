#pragma once

#include <windows.h>
#include <string>

#include "Circle.h"

/// <summary>
///		Realization of target as a circle
/// </summary>
class Target : public Circle
{
public:
	/// <summary>
	///		Inititializes target with specified coordinates. Delay of the target is infinite by default.
	///		Bounds are: 0, 0, 0, 0
	/// </summary>
	/// <param name="x">
	///		x coordinate
	/// </param>
	/// <param name="y">
	///		y coordinate
	/// </param>
	/// <param name="radius">
	///		radius of target circle
	/// </param>
	Target(INT x, INT y, INT radius);

	/// <summary>
	///		Inititializes target with specified coordinates. Delay of the target is infinite by default.
	/// </summary>
	/// <param name="center">
	///		Cental point of the target
	/// </param>
	/// <param name="radius">
	///		radius of target circle
	/// </param>
	Target(POINT center, INT radius);

	/// <summary>
	///		Updates central point of the target circle
	/// </summary>
	/// <param name="center">
	///		New center
	/// </param>
	VOID SetCenter(POINT center);

	/// <summary>
	///		Updates delay until new target is loaded
	/// </summary>
	/// <param name="delay">
	///		Delay
	/// </param>
	VOID SetDelay(INT delay);

	/// <summary>
	///		Delay getter
	/// </summary>
	/// <returns>
	///		Returns delay
	/// </returns>
	INT GetDelay() const;
private:
	INT delay;
};

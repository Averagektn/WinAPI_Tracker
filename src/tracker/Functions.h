#pragma once

namespace DrawFuncs 
{
	void DoubleBufferedPaint(HWND hWnd, HDC hdc) {
		HDC memDC;
		HBITMAP memBMP;
		HGDIOBJ hOld;
		memDC = CreateCompatibleDC(hdc);
		memBMP = CreateCompatibleBitmap(hdc, ProjConst::WND_DEF_WIDTH, ProjConst::WND_DEF_HEIGHT);

		hOld = SelectObject(memDC, memBMP);

		BitBlt(hdc, 0, 0, ProjConst::WND_DEF_WIDTH, ProjConst::WND_DEF_HEIGHT, memDC, 0, 0, SRCCOPY);
		SelectObject(memDC, hOld);

		DeleteObject(memBMP);
		DeleteDC(memDC);
		ReleaseDC(hWnd, hdc);
	}
}

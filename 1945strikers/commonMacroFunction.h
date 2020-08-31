#pragma once
//=============================================================
//	## commonMacroFunction ##
//=============================================================

//POINT
inline POINT PointMake(int x, int y)
{
	POINT pt = { x, y };
	return pt;
}

//선 그리기
inline void LineMake(HDC hdc, int startX, int startY, int endX, int endY)
{
	MoveToEx(hdc, startX, startY, NULL);
	LineTo(hdc, endX, endY);
}

//RECT 만들기
//RECT rc = { 128, 59, 228, 159 };
//RECT rc = RectMake(128, 59, 100, 100)
inline RECT RectMake(int x, int y, int width, int height)
{
	RECT rc = { x, y, x + width, y + height };
	return rc;
}
//RECT 중심좌표로 만들기
inline RECT RectMakeCenter(int x, int y, int width, int height)
{
	RECT rc = { x - width / 2, y - height / 2, x + width / 2, y + height / 2 };
	return rc;
}

//Rectangle 함수 이용해서 사각형 그리기
inline void RectangleMake(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x, y, x + width, y + height);
}

//Ellipse 함수 이용해서 타원 그리기
inline void EllipseMake(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x, y, x + width, y + height);
}
//Ellipse 함수 이용해서 타원 중심좌표에 그리기
inline void EllipseMakeCenter(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x - width / 2, y - height / 2, x + width / 2, y + height / 2);
}

//편하쥬?
inline void Rectangle(HDC hdc, RECT rc)
{
	Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
}

inline float GetDistance(float x1, float y1, float x2, float y2)
{
	float w = x2 - x1;
	float h = y2 - y1;
	float r = sqrt((w * w) + (h * h));
	return r;
}

inline float GetAngle(float x1, float y1, float x2, float y2)
{
	return -atan2(y2 - y1, x2 - x1);
}
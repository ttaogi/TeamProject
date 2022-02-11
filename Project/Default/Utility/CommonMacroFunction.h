#pragma once

#include <iostream>
#include <windef.h>

class Component;
class MonoBehaviour;
class RenderedImage;

inline RECT MakeRectCWH(POINT _pos, int _width, int _height)
{
	return RECT{ _pos.x - _width / 2, _pos.y - _height / 2, _pos.x + _width / 2, _pos.y + _height / 2 };
}

inline void PaintRect(HDC _hdc, RECT _rc)
{
	Rectangle(_hdc, _rc.left, _rc.top, _rc.right, _rc.bottom);
}



inline void PrintRect(RECT _rc)
{
	printf("%04d\t%04d\t%04d\t%04d\n", _rc.left, _rc.top, _rc.right, _rc.bottom);
}

inline void PrintPos(POINT _pos)
{
	printf("%04d\t%04d\n", _pos.x, _pos.y);
}


MonoBehaviour* IsDerivedFromMonoBehaviour(Component* _c);

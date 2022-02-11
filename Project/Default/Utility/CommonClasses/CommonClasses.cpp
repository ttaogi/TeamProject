#include "Stdafx/stdafx.h"

#include "CommonClasses.h"

#pragma region	F_POINT
F_POINT& F_POINT::operator = (const POINT& _p) {
	x = (float)_p.x;
	y = (float)_p.y;
	return *this;
}

F_POINT F_POINT::operator + (const F_POINT& _p) {
	return F_POINT{ x + _p.x , y + _p.y };
}

F_POINT F_POINT::operator - (const F_POINT& _p) {
	return F_POINT{ x - _p.x, y - _p.y };
}

F_POINT F_POINT::operator * (const float& _f) {
	return F_POINT{ x * _f, y * _f };
}

F_POINT F_POINT::operator / (const float& _f) {
	return F_POINT{ x / _f, y / _f };
}

POINT F_POINT::ToPoint() const {
	return POINT{ (LONG)x, (LONG)y };
}

float F_POINT::Length() const {
	return sqrt(x * x + y * y);
}
#pragma endregion	F_POINT


#pragma region	VELOCITY
VELOCITY& VELOCITY::operator = (const F_POINT& _p) {
	x = _p.x;
	y = _p.y;
	return *this;
}

VELOCITY VELOCITY::operator + (const VELOCITY& _p) {
	return VELOCITY{ x + _p.x, y + _p.y };
}

VELOCITY VELOCITY::operator - (const VELOCITY& _p) {
	return VELOCITY{ x - _p.x, y - _p.y };
}

VELOCITY VELOCITY::operator * (const float& _f) {
	return VELOCITY{ x * _f, y * _f };
}

VELOCITY VELOCITY::operator / (const float& _f) {
	return VELOCITY{ x / _f, y / _f };
}

void VELOCITY::Accelerate(F_POINT _acc) {
	x += _acc.x;
	y += _acc.y;
}

void VELOCITY::AddG() {
	Accelerate(F_POINT{ 0, VELOCITY_G });
}

F_POINT VELOCITY::ToFPoint() const {
	return F_POINT{ x, y };
}

float VELOCITY::Length() const {
	return sqrt(x * x + y * y);
}
#pragma endregion	VELOCITY


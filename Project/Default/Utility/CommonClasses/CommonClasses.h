#pragma once

struct F_POINT
{
	float x;
	float y;

	F_POINT& operator = (const POINT& _p);
	F_POINT operator + (const F_POINT& _p);
	F_POINT operator - (const F_POINT& _p);
	F_POINT operator * (const float& _f);
	F_POINT operator / (const float& _f);

	POINT ToPoint() const;
	float Length() const;
};


#define VELOCITY_G	9.8f

struct VELOCITY
{
	float x;
	float y;

	void SetX(float _speed) { x = _speed; }
	float GetX() const { return x; }
	void SetY(float _speed) { y = _speed; }
	float GetY() const { return y; }

	VELOCITY& operator = (const F_POINT& _p);
	VELOCITY operator + (const VELOCITY& _p);
	VELOCITY operator - (const VELOCITY& _p);
	VELOCITY operator * (const float& _f);
	VELOCITY operator / (const float& _f);

	void Accelerate(F_POINT _acc);
	void AddG();

	F_POINT ToFPoint() const;
	float Length() const;
};





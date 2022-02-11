#pragma once

#include <Windows.h>

#include "DesignPattern/SingletonBase/SingletonBase.h"

class RandomFunction : public SingletonBase<RandomFunction>
{
public:
	RandomFunction()	{ srand((unsigned int)GetTickCount64()); }
	~RandomFunction()	{ }

	int GetInt(int _num)					{ return rand() % _num; }
	int GetIntFromTo(int _from, int _to)	{ return (rand() % (_to - _from + 1)) + _from; }

	float GetFloat()								{ return (float)rand() / (float)RAND_MAX; }
	float GetFloat(float _num)						{ return ((float)rand() / (float)RAND_MAX) * _num; }
	float GetFloatFromTo(float _from, float _to)	{ return ((float)rand() / (float)RAND_MAX) * (_to - _from) + _from; }
};
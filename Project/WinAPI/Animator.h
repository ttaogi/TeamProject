#pragma once

#include "Enums.h"

class Animation;

class Animator
{
private:
	bool play;

	Animation* animations[(unsigned int)CHARACTER_STATE::CHARACTER_STATE_NUM];
	CHARACTER_STATE curState;
public:
	Animator();
	~Animator() { release(); }

	void init() {}
	void release();
	void update();

	void addAnimation(CHARACTER_STATE _state, Animation* _animation);
	bool changeAnimation(CHARACTER_STATE _state);
	void animationRender(HDC _hdc, POINT _pos);
	bool isEnd() const;
	bool isPlay() const { return play; }

	void aniStart();
	void aniStop();
	void aniPause();
	void aniResume();
};
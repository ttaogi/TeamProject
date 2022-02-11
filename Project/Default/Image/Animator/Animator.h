#pragma once

#include "../Animation/Animation.h"

class Animator {
private:
	Animation* animations[(unsigned int)CHARACTER_STATE::CHARACTER_STATE_NUM];
	CHARACTER_STATE curState;
public:
	Animator();
	~Animator() { Release(); }

	void Init() {}
	void Release();

	void AddAnimation(CHARACTER_STATE _state, Animation* _animation);
	bool ChangeAnimation(CHARACTER_STATE _state);
	void AnimationRender(HDC _hdc, POINT _pos);
	bool IsEnd() const;
};
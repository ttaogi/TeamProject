#pragma once

#include "Image/Animation/Animation.h"

class Animator
{
private:
	bool isPlay;

	Animation* animations[(unsigned int)CHARACTER_STATE::CHARACTER_STATE_NUM];
	CHARACTER_STATE curState;
public:
	Animator();
	~Animator() { Release(); }

	void Init() {}
	void Release();
	void Update();

	void AddAnimation(CHARACTER_STATE _state, Animation* _animation);
	bool ChangeAnimation(CHARACTER_STATE _state);
	void AnimationRender(HDC _hdc, POINT _pos);
	bool IsEnd() const;
	bool IsPlay() const { return isPlay; }

	void AniStart();
	void AniStop();
	void AniPause();
	void AniResume();
};
#include "Stdafx/stdafx.h"

#include "Animator.h"

Animator::Animator()
{
	isPlay = true;
	for (int i = 0; i < (int)CHARACTER_STATE::CHARACTER_STATE_NUM; ++i)
		animations[i] = NULL;
	curState = CHARACTER_STATE::IDLE;
}

void Animator::Release()
{
	for (int i = 0; i < (int)CHARACTER_STATE::CHARACTER_STATE_NUM; ++i)
	{
		SAFE_RELEASE(animations[i]);
		SAFE_DELETE(animations[i]);
	}
}

void Animator::AddAnimation(CHARACTER_STATE _state, Animation* _animation)
{
	SAFE_RELEASE(animations[(int)_state]);
	SAFE_DELETE(animations[(int)_state]);
	animations[(int)_state] = _animation;
}

bool Animator::ChangeAnimation(CHARACTER_STATE _state)
{
	if (animations[(int)_state] != NULL)
	{
		curState = _state;
		animations[(int)_state]->Reset();
		return true;
	}
	else
	{
		curState = CHARACTER_STATE::IDLE;
		if (animations[(int)CHARACTER_STATE::IDLE] != NULL)
			animations[(int)CHARACTER_STATE::IDLE]->Reset();
		return false;
	}
}

void Animator::AnimationRender(HDC _hdc, POINT _pos)
{
	if (animations[(int)curState] != NULL)
		animations[(int)curState]->AnimationRender(_hdc, _pos, isPlay);
}

bool Animator::IsEnd() const
{
	if (animations[(int)curState] != NULL)
		return animations[(int)curState]->IsEnd();
	return true;
}

void Animator::AniStart()
{
	isPlay = true;
	animations[(int)curState]->Reset();
}

void Animator::AniStop()
{
	isPlay = false;
	animations[(int)curState]->Reset();
}

void Animator::AniPause() { isPlay = false; }

void Animator::AniResume() { isPlay = true; }

#include "Stdafx.h"

#include "Animator.h"

#include "Animation.h"

Animator::Animator()
{
	play = true;
	for (int i = 0; i < (int)CHARACTER_STATE::CHARACTER_STATE_NUM; ++i)
		animations[i] = NULL;
	curState = CHARACTER_STATE::IDLE_RIGHT;
}

void Animator::release()
{
	for (int i = 0; i < (int)CHARACTER_STATE::CHARACTER_STATE_NUM; ++i)
	{
		SAFE_RELEASE(animations[i]);
		SAFE_DELETE(animations[i]);
	}
}

void Animator::update()
{
	if (animations[(int)curState])
		animations[(int)curState]->animationUpdate(play);
}

void Animator::addAnimation(CHARACTER_STATE _state, Animation* _animation)
{
	SAFE_RELEASE(animations[(int)_state]);
	SAFE_DELETE(animations[(int)_state]);
	animations[(int)_state] = _animation;
}

bool Animator::changeAnimation(CHARACTER_STATE _state)
{
	if (animations[(int)_state])
	{
		curState = _state;
		animations[(int)_state]->reset();
		return true;
	}
	else
	{
		curState = CHARACTER_STATE::IDLE_RIGHT;
		if (animations[(int)CHARACTER_STATE::IDLE_RIGHT])
			animations[(int)CHARACTER_STATE::IDLE_RIGHT]->reset();
		return false;
	}
}

void Animator::animationRender(HDC _hdc, POINT _pos)
{
	if (animations[(int)curState])
		animations[(int)curState]->animationRender(_hdc, _pos);
}

bool Animator::isEnd() const
{
	if (animations[(int)curState])
		return animations[(int)curState]->isEnd();
	return true;
}

void Animator::aniStart()
{
	play = true;
	animations[(int)curState]->reset();
}

void Animator::aniStop()
{
	play = false;
	animations[(int)curState]->reset();
}

void Animator::aniPause() { play = false; }

void Animator::aniResume() { play = true; }

void Animator::setFrameIdx(int idx)
{
	if (animations[(int)curState])
		animations[(int)curState]->setFrameIdx(idx);
}

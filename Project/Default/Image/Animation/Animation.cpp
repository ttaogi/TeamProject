#include "Stdafx/stdafx.h"

#include "Animation.h"

Animation::Animation()
{
	frameIdx = 0;
	frameUpdateSec = 1.0f / DEFAULT_FPS;
	elapsedSec = 0.0f;
	image = NULL;
}

HRESULT Animation::Init(
	std::wstring _imageKey, POINT _coordinateRevision,
	CHARACTER_STATE _state, bool _loop,
	bool _reverse, float _fps)
{
	image = IMG->FindImage(_imageKey);
	if (image == NULL) return E_FAIL;

	frameIdx = 0;
	if (_fps > 0) SetFPS(_fps);
	loop = _loop;
	state = _state;
	coordinateRevision = _coordinateRevision;
	frameVec.clear();
	playVec.clear();

	for (int i = 0; i < image->GetMaxFrameIdx(); ++i) {
		int srcX = (i % image->GetMaxFrameX()) * image->GetFrameWidth();
		int srcY = (i / image->GetMaxFrameX()) * image->GetFrameHeight();

		frameVec.push_back(POINT{ srcX, srcY });
	}

	SetDefaultPlayFrame(_reverse, _loop);

	return S_OK;
}

void Animation::AnimationUpdate(bool _isPlay)
{
	if (_isPlay)
	{
		elapsedSec += TIME->GetElapsedTime();

		while (elapsedSec >= frameUpdateSec) {
			elapsedSec -= frameUpdateSec;
			++frameIdx;
		}
	}

	if (loop)
		frameIdx %= (int)playVec.size();

	if (frameIdx >= (int)playVec.size())
		frameIdx = (int)playVec.size();
}

void Animation::AnimationRender(HDC _hdc, POINT _pos)
{
	int usedIdx = 0;

	if (frameIdx == playVec.size())
		usedIdx = frameIdx - 1;
	else
		usedIdx = frameIdx;

	int destX = _pos.x + coordinateRevision.x;
	int destY = _pos.y + coordinateRevision.y;
	int srcX = (usedIdx % image->GetMaxFrameX()) * image->GetFrameWidth();
	int srcY = (usedIdx / image->GetMaxFrameX()) * image->GetFrameHeight();

	if (image->GetIsTrans() == true)
	{
		GdiTransparentBlt(
			_hdc, destX, destY,
			image->GetFrameWidth(),
			image->GetFrameHeight(),
			image->GetMemDC(),
			srcX,
			srcY,
			image->GetFrameWidth(),
			image->GetFrameHeight(),
			image->GetTransColor());
	}
	else {
		BitBlt(
			_hdc, destX, destY,
			image->GetFrameWidth(),
			image->GetFrameHeight(),
			image->GetMemDC(),
			srcX,
			srcY,
			SRCCOPY);
	}
}

bool Animation::IsEnd() const
{
	if (loop) return false;
	return (frameIdx == playVec.size());
}

void Animation::SetDefaultPlayFrame(bool _reverse, bool _loop)
{
	loop = _loop;
	playVec.clear();
	frameIdx = 0;

	if (_reverse)
	{
		for (int i = 0; i < image->GetMaxFrameIdx(); ++i)
			playVec.push_back(i);
		for (int i = image->GetMaxFrameIdx() - 2; i > 0; --i)
			playVec.push_back(i);
		if (!_loop)
			playVec.push_back(0);
	}
	else
		for (int i = 0; i < image->GetMaxFrameIdx(); i++)
			playVec.push_back(i);
}

void Animation::SetPlayFrame(int* _playArr, int _arrLen)
{
	loop = false;
	playVec.clear();
	if (_playArr)	frameIdx = _playArr[0];
	else
	{
		frameIdx = 0;

		for (int i = 0; i < _arrLen; ++i)
			playVec.push_back(_playArr[i]);
	}
}

void Animation::SetPlayFrame(int _start, int _end, bool _reverse, bool _loop)
{
	loop = _loop;
	playVec.clear();
	frameIdx = _start;

	for (int i = _start; i < _end; ++i) {
		int srcX = (i % image->GetMaxFrameX()) * image->GetFrameWidth();
		int srcY = (i / image->GetMaxFrameX()) * image->GetFrameHeight();

		frameVec.push_back(POINT{ srcX, srcY });
	}

	if (_reverse) {
		for (int i = _end - 2; i > _start; --i) {
			int srcX = (i % image->GetMaxFrameX()) * image->GetFrameWidth();
			int srcY = (i / image->GetMaxFrameX()) * image->GetFrameHeight();

			frameVec.push_back(POINT{ srcX, srcY });
		}

		if (!_loop) {
			int srcX = (_start % image->GetMaxFrameX()) * image->GetFrameWidth();
			int srcY = (_start / image->GetMaxFrameX()) * image->GetFrameHeight();

			frameVec.push_back(POINT{ srcX, srcY });
		}
	}
}

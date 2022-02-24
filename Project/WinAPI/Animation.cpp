#include "Stdafx.h"

#include "Animation.h"

Animation::Animation()
{
	frameIdx = 0;
	frameUpdateSec = 1.0f / DEFAULT_FPS;
	elapsedSec = 0.0f;
	image = NULL;
}

HRESULT Animation::init(
	std::string _imageKey, POINT _coordinateRevision,
	CHARACTER_STATE _state, bool _loop,
	bool _reverse, float _fps)
{
	image = IMAGEMANAGER->findImage(_imageKey);
	if (image == NULL) return E_FAIL;

	frameIdx = 0;
	if (_fps > 0) setFPS(_fps);
	loop = _loop;
	state = _state;
	coordinateRevision = _coordinateRevision;
	frameVec.clear();
	playVec.clear();

	for (int i = 0; i < image->getMaxFrameIdx(); ++i) {
		int srcX = (i % image->getMaxFrameX()) * image->getFrameWidth();
		int srcY = (i / image->getMaxFrameX()) * image->getFrameHeight();

		frameVec.push_back(POINT{ srcX, srcY });
	}

	setDefaultPlayFrame(_reverse, _loop);

	return S_OK;
}

void Animation::animationUpdate(bool _isPlay)
{
	if (_isPlay)
	{
		elapsedSec += TIMEMANAGER->getElapsedTime();

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

void Animation::animationRender(HDC _hdc, POINT _pos)
{
	int usedIdx = 0;

	if (frameIdx == playVec.size())
		usedIdx = frameIdx - 1;
	else
		usedIdx = frameIdx;

	int destX = _pos.x + coordinateRevision.x;
	int destY = _pos.y + coordinateRevision.y;
	int srcX = (usedIdx % image->getMaxFrameX()) * image->getFrameWidth();
	int srcY = (usedIdx / image->getMaxFrameX()) * image->getFrameHeight();

	if (image->getIsTrans() == true)
	{
		GdiTransparentBlt(
			_hdc, destX, destY,
			image->getFrameWidth(),
			image->getFrameHeight(),
			image->getMemDC(),
			srcX,
			srcY,
			image->getFrameWidth(),
			image->getFrameHeight(),
			image->getTransColor());
	}
	else {
		BitBlt(
			_hdc, destX, destY,
			image->getFrameWidth(),
			image->getFrameHeight(),
			image->getMemDC(),
			srcX,
			srcY,
			SRCCOPY);
	}
}

bool Animation::isEnd() const
{
	if (loop) return false;
	return (frameIdx == playVec.size());
}

void Animation::setDefaultPlayFrame(bool _reverse, bool _loop)
{
	loop = _loop;
	playVec.clear();
	frameIdx = 0;

	if (_reverse)
	{
		for (int i = 0; i < image->getMaxFrameIdx(); ++i)
			playVec.push_back(i);
		for (int i = image->getMaxFrameIdx() - 2; i > 0; --i)
			playVec.push_back(i);
		if (!_loop)
			playVec.push_back(0);
	}
	else
		for (int i = 0; i < image->getMaxFrameIdx(); i++)
			playVec.push_back(i);
}

void Animation::setPlayFrame(int* _playArr, int _arrLen)
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

void Animation::setPlayFrame(int _start, int _end, bool _reverse, bool _loop)
{
	loop = _loop;
	playVec.clear();
	frameIdx = _start;

	for (int i = _start; i < _end; ++i) {
		int srcX = (i % image->getMaxFrameX()) * image->getFrameWidth();
		int srcY = (i / image->getMaxFrameX()) * image->getFrameHeight();

		frameVec.push_back(POINT{ srcX, srcY });
	}

	if (_reverse) {
		for (int i = _end - 2; i > _start; --i) {
			int srcX = (i % image->getMaxFrameX()) * image->getFrameWidth();
			int srcY = (i / image->getMaxFrameX()) * image->getFrameHeight();

			frameVec.push_back(POINT{ srcX, srcY });
		}

		if (!_loop) {
			int srcX = (_start % image->getMaxFrameX()) * image->getFrameWidth();
			int srcY = (_start / image->getMaxFrameX()) * image->getFrameHeight();

			frameVec.push_back(POINT{ srcX, srcY });
		}
	}
}

#include "Stdafx.h"
#include "Slime.h"

Slime::Slime() {}

HRESULT Slime::init(void)
{
	//! Do Nothing
	return S_OK;
}

HRESULT Slime::init(const char * imageName, POINT position)
{
	_worldTimeCount = TIMEMANAGER->getWorldTime();
	_rndTimeCount = RND->getFromFloatTo(0.04f, 0.1f);

	_bulletFireCount = TIMEMANAGER->getWorldTime();
	_rndFireCount = RND->getFromFloatTo(0.5f, 4.5f);


	_image = IMAGEMANAGER->findImage(imageName);
	_rc = RectMakeCenter(position.x, position.y, _image->getFrameWidth(), _image->getFrameHeight());
	return S_OK;
}

void Slime::release(void)
{
}

void Slime::update(void)
{
	move();
}

void Slime::render(void)
{
	draw();
	animation();
}
//
////´Ë
//void Slime::move(void)
//{
//}
//
//void Slime::draw(void)
//{
//	_image->frameRender(getMemDC(), _rc.left, _rc.top,
//		_currentFrameX, _currentFrameY);
//}
//
//void Slime::animation(void)
//{
//	//¹¬¾ð ¼öÇà
//	if (_rndTimeCount + _worldTimeCount <= TIMEMANAGER->getWorldTime())
//	{
//		_worldTimeCount = TIMEMANAGER->getWorldTime();
//		_currentFrameX++;
//		if (_image->getMaxFrameX() < _currentFrameX)
//		{
//			_currentFrameX = 0;
//		}
//	}
//}

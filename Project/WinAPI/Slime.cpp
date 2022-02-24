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
	
	slime = IMAGEMANAGER->addFrameImage(KEY_SLIME, DIR_SLIME, 208, 104, 4, 2, 8, true, MAGENTA);

	_rc = RectMakeCenter(position.x, position.y, slime->getFrameWidth(), slime->getFrameHeight());

	cout << "getFrameWidth: " << slime->getFrameWidth() <<endl;
	cout << "getFrameHeight: " << slime->getFrameHeight() <<endl;


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


void Slime::move(void)
{
}

void Slime::draw(void)
{
	Rectangle(getMemDC(), _rc.left, _rc.top, _rc.right, _rc.bottom);


	slime->frameRender(getMemDC(), _rc.left, _rc.top,
		_currentFrameX, _currentFrameY);


}

void Slime::animation(void)
{
	if (_rndTimeCount + _worldTimeCount <= TIMEMANAGER->getWorldTime())
	{
		_worldTimeCount = TIMEMANAGER->getWorldTime();
		_currentFrameX++;
		if (slime->getMaxFrameX() <= _currentFrameX)
		{
			_currentFrameX = 0;
		}
	}
}

#include "Stdafx.h"
#include "Flame.h"

Flame::Flame()
{
	//! DO Nothing
}

Flame::~Flame()
{
	//! DO Nothing
}

HRESULT Flame::init(const char* fileName, float* x, float* y)
{
	_image = IMAGEMANAGER->addFrameImage("부스터", "Resources/Images/Object/Flame.bmp",
		0.0f, 0.0f, 432, 297, 9, 1, true, RGB(255, 0, 255));

	_x = x;
	_y = y;

	_rc = RectMakeCenter((int)(*_x), (int)(*_y), _image->getFrameWidth(), _image->getFrameHeight());

	return S_OK;
}


void Flame::release(void)
{
}

void Flame::update(void)
{
	/*
	여지 -> 문제의 여지 -> 최대한 설계단계 에서 배제
	Flame 클래스는 Rocket의 종속 클래스인데 계속 프레임을 추가하다보면 언젠간 로켓보다 메모리를 더많이 잡아먹는
	주객전도가 일어날수있기 때문에 아래와같이 쓰는건 별로 좋지가 않다

	_count++;
	if (_count % 3 == 0)
	{

	}
	*/
	if (FLAME_COUNT + _flameTick <= GetTickCount())
	{
		_flameTick = (float)GetTickCount();
		_image->setFrameX(_image->getFrameX() + 1);

		if (_image->getFrameX() >= _image->getMaxFrameX())
		{
			_image->setFrameX(0);
		}
	}

	_rc = RectMakeCenter((int)(*_x), (int)(*_y) + 180,
		_image->getFrameWidth(),
		_image->getFrameHeight());
}

void Flame::render(void)
{
	_image->frameRender(getMemDC(), _rc.left, _rc.top,
		_image->getFrameX(), _image->getFrameY());
}






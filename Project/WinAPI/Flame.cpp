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
	_image = IMAGEMANAGER->addFrameImage("�ν���", "Resources/Images/Object/Flame.bmp",
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
	���� -> ������ ���� -> �ִ��� ����ܰ� ���� ����
	Flame Ŭ������ Rocket�� ���� Ŭ�����ε� ��� �������� �߰��ϴٺ��� ������ ���Ϻ��� �޸𸮸� ������ ��ƸԴ�
	�ְ������� �Ͼ���ֱ� ������ �Ʒ��Ͱ��� ���°� ���� ������ �ʴ�

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






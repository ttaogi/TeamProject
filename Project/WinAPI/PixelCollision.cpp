#include "Stdafx.h"
#include "PixelCollision.h"

HRESULT PixelCollision::init(void)
{
	_pixelTank = IMAGEMANAGER->addImage("�ȼ� ��ũ", "Resources/Images/Object/PixelTank.bmp",
		70, 60, true, RGB(255, 0, 255));

	_x = CENTER_X + 250;
	_y = CENTER_Y + 100;
	_rc = RectMakeCenter(_x, _y, _pixelTank->getWidth(), _pixelTank->getHeight());

	//Y�� Ž��
	_probeY = _y + _pixelTank->getHeight() / 2;

	return S_OK;
}

void PixelCollision::release(void)
{
	SAFE_DELETE(_pixelTank);
}

void PixelCollision::update(void)
{
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT)) _x += 1.0f;
	if (KEYMANAGER->isStayKeyDown(VK_LEFT)) _x -= 1.0f;

	//Y�� Ž��
	_probeY = _y + _pixelTank->getHeight() / 2;

	//�˻縦���ؼ� �ݺ���
	for (int i = _probeY - 30; i < _probeY + 30; i++)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("��������")->getMemDC(), _x, i);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (!(r == 255 && g == 0 && b == 255))
		{
			_y = i - _pixelTank->getHeight() / 2;
			break;
		}
	}

	_rc = RectMakeCenter(_x, _y, _pixelTank->getWidth(), _pixelTank->getHeight());
}

void PixelCollision::render(void)
{
	_pixelTank->render(getMemDC(), _rc.left, _rc.top);

	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		Rectangle(getMemDC(), _x, _probeY, _x + 10, _probeY + 10);
	}
}

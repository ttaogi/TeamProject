#include "Stdafx.h"
#include "PixelScene.h"

HRESULT PixelScene::init(void)
{
	IMAGEMANAGER->addImage("��������", "Resources/Images/Object/Mountain.bmp", 
		WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));

	_pixel = new PixelCollision;
	_pixel->init();
	return S_OK;
}

void PixelScene::release(void)
{
	SAFE_DELETE(_pixel);
}

void PixelScene::update(void)
{
	_pixel->update();
}

void PixelScene::render(void)
{
	IMAGEMANAGER->findImage("��������")->render(getMemDC());
	_pixel->render();
}

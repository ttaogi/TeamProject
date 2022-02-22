#pragma once

#include "Image.h"

//백버퍼 이미지를 정적으로
//static Image* _backBuffer;
static Image* _backBuffer = IMAGEMANAGER->addImage("backBuffer", WINSIZEX, WINSIZEY);

class GameNode
{
private:
	HDC _hdc;
	bool _managerInit;

public:
	virtual HRESULT init(void);
	virtual HRESULT init(bool managerInit);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	//백버퍼 이미지 얻기
	Image* getBackBuffer(void) { return _backBuffer; }

	HDC getMemDC(){ return _backBuffer->getMemDC(); }
	HDC getHDC() { return _hdc; }

	LRESULT MainProc(HWND hWnd, UINT imessage, WPARAM wParam, LPARAM lParam);

	GameNode() {}
	virtual ~GameNode() {}
};


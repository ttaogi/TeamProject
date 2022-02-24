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
protected:
	POINT pos;
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
	POINT getPos() const { return pos; }

	LRESULT MainProc(HWND hWnd, UINT imessage, WPARAM wParam, LPARAM lParam);

	bool operator<(const GameNode gn) const {
		if (pos.y != gn.pos.y)
			return pos.y > gn.pos.y;
		else
			return pos.x > gn.pos.x;
	}

	GameNode() {}
	virtual ~GameNode() {}
};

// reference.
// https://stackoverflow.com/questions/23997104/priority-queue-with-pointers-and-comparator-c
struct CmpGameNodePtrs
{
	bool operator()(const GameNode* lhs, const GameNode* rhs) const
	{
		return *lhs < *rhs;
	}
};

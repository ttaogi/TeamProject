#pragma  once

#include "Image/Image.h"

static Image* backBuffer = NULL;

class GameNode
{
private:
	HDC nodeHdc;
	bool managerInit;
public:
	GameNode();
	virtual ~GameNode();

	virtual HRESULT Init();
	virtual HRESULT Init(bool _managerInit);
	virtual void Release();

	virtual void Update(HWND _hWnd);
	virtual void Render(HDC _hdc);

	Image* GetBackBuffer() { return backBuffer; }

	HDC getMemDC() { return backBuffer->GetMemDC(); }
	HDC getHDC() { return nodeHdc; }

	LRESULT MainProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam);
};
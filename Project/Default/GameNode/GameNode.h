#pragma once

class Image;

static Image* backBuffer = NULL;

class GameNode
{
protected:
	HDC nodeHdc;
public:
	GameNode();
	virtual ~GameNode();

	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render();

	Image* GetBackBuffer();
	void SetBackBuffer(Image* _image);

	HDC GetMemDC();
	HDC GetHDC();

	LRESULT MainProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam);
};
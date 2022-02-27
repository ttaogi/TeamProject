#include "Stdafx.h"

#include "GameNode.h"

HRESULT GameNode::init(void) { return S_OK; }

HRESULT GameNode::init(bool managerInit)
{
	_hdc = GetDC(_hWnd);
	_managerInit = managerInit;

	return S_OK;
}

void GameNode::release()
{
	ReleaseDC(_hWnd, _hdc);
}

void GameNode::update(void) { }

void GameNode::render(void) { }

LRESULT GameNode::MainProc(HWND hWnd, UINT imessage, WPARAM wParam, LPARAM lParam)
{
	//HDC hdc;
	//PAINTSTRUCT ps;
	
	switch (imessage)
	{
	case WM_TIMER:
		this->update();
		break;
	case WM_PAINT:
		this->render();
		break;
	case WM_MOUSEMOVE:
		_ptMouse.x = LOWORD(lParam);
		_ptMouse.y = HIWORD(lParam);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			PostMessage(hWnd, WM_DESTROY, 0, 0);
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return (DefWindowProc(hWnd, imessage, wParam, lParam));
}

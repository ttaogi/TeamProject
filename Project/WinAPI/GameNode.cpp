#include "Stdafx.h"

#include "GameNode.h"

HRESULT GameNode::init(void) { return S_OK; }

HRESULT GameNode::init(bool managerInit)
{
	_hdc = GetDC(_hWnd);
	_managerInit = managerInit;

	if (managerInit)
	{
		setlocale(LC_ALL, "Korean");

		RND->init();
		// FONTMANAGER has no init.
		IMAGEMANAGER->init();
		KEYMANAGER->init();
		SCENEMANAGER->init();
		SOUNDMANAGER->init();
		TEXTDATAMANAGER->init();
		TIMEMANAGER->init();
		XMLMANAGER->init();

		ITEMINFOMANAGER->init();
		MAPINFOMANAGER->init();
		PLAYERINFOMANAGER->init();
	}

	return S_OK;
}

void GameNode::release()
{
	if (_managerInit)
	{
		PLAYERINFOMANAGER->release();
		PLAYERINFOMANAGER->releaseSingleton();
		MAPINFOMANAGER->release();
		MAPINFOMANAGER->releaseSingleton();
		ITEMINFOMANAGER->release();
		ITEMINFOMANAGER->releaseSingleton();

		XMLMANAGER->release();
		XMLMANAGER->releaseSingleton();
		TIMEMANAGER->release();
		TIMEMANAGER->releaseSingleton();
		TEXTDATAMANAGER->release();
		TEXTDATAMANAGER->releaseSingleton();
		SOUNDMANAGER->release();
		SOUNDMANAGER->releaseSingleton();
		SCENEMANAGER->release();
		SCENEMANAGER->releaseSingleton();
		MAPINFOMANAGER->release();
		MAPINFOMANAGER->releaseSingleton();
		KEYMANAGER->releaseSingleton();
		IMAGEMANAGER->release();
		IMAGEMANAGER->releaseSingleton();
		FONTMANAGER->releaseSingleton();
		RND->releaseSingleton();
	}

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

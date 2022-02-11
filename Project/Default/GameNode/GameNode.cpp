#include "Stdafx/stdafx.h"

#include <locale.h>

#include "GameNode.h"

GameNode::GameNode() { }

GameNode::~GameNode() { Release(); }

HRESULT GameNode::Init() {
	backBuffer = IMG->AddImage(KEY_BACKGROUND_BACKBUFFER, BACKGROUND_BACKBUFFER, WINSIZE_X, WINSIZE_Y);
	SetTimer(HANDLE_WINDOW, 1, 42, NULL);
	return S_OK;
}

HRESULT GameNode::Init(bool _managerInit) {
	nodeHdc = GetDC(HANDLE_WINDOW);
	managerInit = _managerInit;

	if (_managerInit) {
		IMG->init();
		_wsetlocale(LC_ALL, L"Korean");
	}

	return Init();
}

void GameNode::Release() {
	KillTimer(HANDLE_WINDOW, 1);
	KEY->ReleaseSingleton();
	RND->ReleaseSingleton();
	if (managerInit) {
		IMG->Release();
		IMG->ReleaseSingleton();
	}
	ReleaseDC(HANDLE_WINDOW, nodeHdc);
}

void GameNode::Update(HWND _hWnd) {
	InvalidateRect(_hWnd, NULL, true);
}

void GameNode::Render(HDC _hdc) { }

LRESULT GameNode::MainProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam) {
	return DefWindowProc(_hWnd, _message, _wParam, _lParam);
}

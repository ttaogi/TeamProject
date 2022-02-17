#include "Stdafx/stdafx.h"

#include "GameNode.h"

#include <locale.h>

#include "Image/Image.h"

GameNode::GameNode() { }

GameNode::~GameNode() { Release(); }

HRESULT GameNode::Init() { return S_OK; }

void GameNode::Release() { }

void GameNode::Update() { }

void GameNode::Render() { }

Image* GameNode::GetBackBuffer() { return backBuffer; }

void GameNode::SetBackBuffer(Image* _image) { backBuffer = _image; }

HDC GameNode::GetMemDC() { return backBuffer->GetMemDC(); }

HDC GameNode::GetHDC() { return nodeHdc; }

LRESULT GameNode::MainProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam)
{
	return DefWindowProc(_hWnd, _message, _wParam, _lParam);
}

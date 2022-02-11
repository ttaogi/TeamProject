#pragma warning(disable:28251)

#include "Stdafx/stdafx.h"

#include "MainGame.h"

MainGame::MainGame() {
	scnMgr = nullptr;
	nextScnType = SCENE_TYPE::NONE;
	quit = false;
}

MainGame::~MainGame() {
	Release();
}

HRESULT MainGame::Init() {
	if (scnMgr == nullptr) {
		scnMgr = new TitleSceneManager(this);
		scnMgr->Init(this);
	}

	return GameNode::Init();
}

HRESULT MainGame::Init(bool _managerInit) {
	if (scnMgr == nullptr) {
		scnMgr = new TitleSceneManager(this);
		scnMgr->Init(this);
	}

	return GameNode::Init(_managerInit);
}

void MainGame::Release() {
	if (scnMgr != nullptr) {
		scnMgr->Release();
		delete scnMgr;
		scnMgr = nullptr;
	}

	GameNode::Release();
}

void MainGame::Update(HWND _hWnd) {
	if (quit == true) {
		Release();
		PostQuitMessage(0);
		return;
	}

	MOUSE_CLICKED = false;
	if (KEY->IsOnceKeyDown(VK_LBUTTON)) {
		GetCursorPos(&POINT_MOUSE);
		ScreenToClient(_hWnd, &POINT_MOUSE);
		MOUSE_CLICKED = true;
	}

	switch (nextScnType) {
	case SCENE_TYPE::TITLE:
		nextScnType = SCENE_TYPE::NONE;
		break;
	case SCENE_TYPE::ONGAME:
		nextScnType = SCENE_TYPE::NONE;
		if (scnMgr != nullptr) {
			scnMgr->Release();
			delete scnMgr;
			scnMgr = new OnGameSceneManager(this);
			scnMgr->Init(this);
		}
		break;
	case SCENE_TYPE::END:
		nextScnType = SCENE_TYPE::NONE;
		if (scnMgr != nullptr) {
			scnMgr->Release();
			delete scnMgr;
			scnMgr = new EndSceneManager(this);
			scnMgr->Init(this);
		}
		break;
	default:
		nextScnType = SCENE_TYPE::NONE;
		break;
	}

	if (scnMgr != nullptr) scnMgr->Update(_hWnd);

	GameNode::Update(_hWnd);
}

void MainGame::Render(HDC _hdc) {
	if (scnMgr != nullptr) scnMgr->Render(_hdc);
	GameNode::Render(_hdc);
}

LRESULT MainGame::MainProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam) {
	HDC hdc;
	PAINTSTRUCT ps;

	switch (_message) {
	case WM_CREATE:
		break;
	case WM_TIMER:
		switch (_wParam) {
		case 1:
			Update(_hWnd);
			break;
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(_hWnd, &ps);

		Render(hdc);

		EndPaint(_hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return GameNode::MainProc(_hWnd, _message, _wParam, _lParam);
}

void MainGame::SetNextScene_ONGAME() {
	nextScnType = SCENE_TYPE::ONGAME;
}

void MainGame::SetNextScene_END() {
	nextScnType = SCENE_TYPE::END;
}

void MainGame::QuitGame() {
	quit = true;
}

#pragma warning(disable:28251)
#include "Stdafx/stdafx.h"

#include "MainGame.h"

#include "Manager/SceneManager/EndSceneManager/EndSceneManager.h"
#include "Manager/SceneManager/OnGameSceneManager/OnGameSceneManager.h"
#include "Manager/SceneManager/TitleSceneManager/TitleSceneManager.h"

MainGame::MainGame()
{
	quit = false;
	scnMgr = NULL;
	nextScnType = SCENE_TYPE::NONE;
}

MainGame::~MainGame()
{
	Release();
}

HRESULT MainGame::Init()
{
	nodeHdc = GetDC(HANDLE_WINDOW);

	// singleton init.
	IMG->init();
	_wsetlocale(LC_ALL, L"Korean");
	TIME->Init();

	SetBackBuffer(IMG->FindImage(KEY_BACKGROUND_BACKBUFFER));

	if (scnMgr == NULL)
	{
		scnMgr = new TitleSceneManager();
		scnMgr->Init();
	}

	SetTimer(HANDLE_WINDOW, 1, 42, NULL);

	return S_OK;
}

void MainGame::Release()
{ // reverse order of init.
	KillTimer(HANDLE_WINDOW, 1);

	if (scnMgr != NULL)
	{
		scnMgr->Release();
		delete scnMgr;
		scnMgr = NULL;
	}

	// singleton release.
	TIME->Release();
	TIME->ReleaseSingleton();
	FONT->ReleaseSingleton();
	IMG->Release();
	IMG->ReleaseSingleton();
	KEY->ReleaseSingleton();
	RND->ReleaseSingleton();

	ReleaseDC(HANDLE_WINDOW, nodeHdc);
}

void MainGame::Update()
{
	if (quit == true)
	{
		Release();
		PostQuitMessage(0);
		return;
	}

	MOUSE_CLICKED = false;
	if (KEY->IsOnceKeyDown(VK_LBUTTON))
	{
		GetCursorPos(&POINT_MOUSE);
		ScreenToClient(HANDLE_WINDOW, &POINT_MOUSE);
		MOUSE_CLICKED = true;
	}

	switch (nextScnType)
	{
	case SCENE_TYPE::TITLE:
		nextScnType = SCENE_TYPE::NONE;
		break;
	case SCENE_TYPE::ONGAME:
		nextScnType = SCENE_TYPE::NONE;
		if (scnMgr != NULL)
		{
			scnMgr->Release();
			delete scnMgr;
			scnMgr = new OnGameSceneManager();
			scnMgr->Init();
		}
		break;
	case SCENE_TYPE::END:
		nextScnType = SCENE_TYPE::NONE;
		if (scnMgr != NULL)
		{
			scnMgr->Release();
			delete scnMgr;
			scnMgr = new EndSceneManager();
			scnMgr->Init();
		}
		break;
	default:
		nextScnType = SCENE_TYPE::NONE;
		break;
	}

	if (scnMgr != NULL) scnMgr->Update();

	InvalidateRect(HANDLE_WINDOW, NULL, true);
}

void MainGame::Render()
{
	if (scnMgr != NULL) scnMgr->Render();
	GetBackBuffer()->Render(GetHDC());
}

LRESULT MainGame::MainProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	switch (_message)
	{
	case WM_CREATE:
		break;
	case WM_TIMER:
		switch (_wParam)
		{
		case 1:
			Update();
			break;
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(_hWnd, &ps);

		Render();

		EndPaint(_hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return GameNode::MainProc(_hWnd, _message, _wParam, _lParam);
}

void MainGame::SetNextScene_ONGAME() { nextScnType = SCENE_TYPE::ONGAME; }

void MainGame::SetNextScene_END() {	nextScnType = SCENE_TYPE::END; }

void MainGame::QuitGame() {	quit = true; }

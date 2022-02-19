#pragma warning(disable:28251)
#include "Stdafx/stdafx.h"

#include "MainGame.h"

#include "Manager/SceneManager/SceneManager.h"
#include "Scene/EndScene/EndScene.h"
#include "Scene/OnGameScene/OnGameScene.h"
#include "Scene/TitleScene/TitleScene.h"

MainGame::MainGame()
{
	quit = false;
	nodeHdc = NULL;
}

MainGame::~MainGame() { Release(); }

HRESULT MainGame::Init()
{
	nodeHdc = GetDC(HANDLE_WINDOW);

	SetBackBuffer(IMG->FindImage(KEY_BACKGROUND_BACKBUFFER));

	TitleScene* titleScene = new TitleScene();
	SCENE->AddScene(KEY_TITLE_SCENE, titleScene);
	OnGameScene* onGameScene = new OnGameScene();
	SCENE->AddScene(KEY_ONGAME_SCENE, onGameScene);
	EndScene* endScene = new EndScene();
	SCENE->AddScene(KEY_END_SCENE, endScene);

	SCENE->ChangeScene(KEY_TITLE_SCENE);

	SetTimer(HANDLE_WINDOW, 1, 42, NULL);

	return S_OK;
}

void MainGame::Release()
{ // reverse order of init.
	KillTimer(HANDLE_WINDOW, 1);

	ReleaseDC(HANDLE_WINDOW, nodeHdc);
}

void MainGame::Update()
{
	TIME->Update(60.0f);

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

	SCENE->Update();
}

void MainGame::Render()
{
	SCENE->Render();
	GetBackBuffer()->Render(GetHDC());
}

LRESULT MainGame::MainProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam)
{
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
		Render();
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return GameNode::MainProc(_hWnd, _message, _wParam, _lParam);
}

void MainGame::QuitGame() {	quit = true; }

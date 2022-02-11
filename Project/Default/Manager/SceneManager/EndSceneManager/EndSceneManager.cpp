#include "Stdafx/stdafx.h"

#include "EndSceneManager.h"

EndSceneManager::EndSceneManager(MainGame* _mg)
	: SceneManager(SCENE_TYPE::TITLE, _mg)
{
	/*retryBtn.SetCallBack_v_CB_v(std::bind(&MainGame::SetNextScene_ONGAME, _mg));
	quitBtn.SetCallBack_v_CB_v(std::bind(&MainGame::QuitGame, _mg));*/
	bgImage = NULL;
}

void EndSceneManager::SetBackBuffer() {
	/*SAFE_RELEASE(backBuffer);
	SAFE_DELETE(backBuffer);
	backBuffer = new Image;
	backBuffer->Init(WINSIZE_X, WINSIZE_Y);*/
}

void EndSceneManager::Init(MainGame* _mg) {
	SetBackBuffer();

	/*bgImage = new Image();
	bgImage->Init(BACKGROUND_ENDSCENE, WINSIZE_X, WINSIZE_Y);
	bgImage->InitForAlphaBlend();*/
}

void EndSceneManager::Update(HWND _hWnd) {
}

void EndSceneManager::LateUpdate() { }

void EndSceneManager::Release() { }

void EndSceneManager::Render(HDC _hdc) {
	//HDC memDC = GetBackBuffer()->GetMemDC();

	//PatBlt(memDC, 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);

	//bgImage->Render(memDC, 0, 0);

	//retryBtn.Render(memDC);
	//quitBtn.Render(memDC);

	//GetBackBuffer()->Render(_hdc, 0, 0);
}

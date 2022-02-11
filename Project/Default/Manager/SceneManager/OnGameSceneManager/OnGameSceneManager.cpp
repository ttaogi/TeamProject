#include "Stdafx/stdafx.h"

#include "OnGameSceneManager.h"

OnGameSceneManager::OnGameSceneManager(MainGame* _mg)
	: SceneManager(SCENE_TYPE::ONGAME, _mg)
{
	//endBtn.SetCallBack_v_CB_v(std::bind(&MainGame::SetNextScene_END, _mg));
	bgImage = NULL;
	msg = L": ";

	alpha = 0;
	bgSpeed = 20;
	bgOffsetX = 0;
	bgOffsetY = 0;
}

OnGameSceneManager::~OnGameSceneManager() { }

void OnGameSceneManager::SetBackBuffer() {
	//*
	SAFE_RELEASE(backBuffer);
	SAFE_DELETE(backBuffer);
	backBuffer = new Image;
	backBuffer->Init(WINSIZE_X, WINSIZE_Y);
	//*/
}

void OnGameSceneManager::Init(MainGame* _mg) {
	SetBackBuffer();

	//*
	bgImage = new Image();
	bgImage->Init(BACKGROUND_ONGAMESCENE, WINSIZE_X, WINSIZE_Y);
	bgImage->InitForAlphaBlend();
	//*/

}

void OnGameSceneManager::Update(HWND _hWnd) {
	if (KEY->IsOnceKeyDown('Q')) {
		//endBtn.SetDestroy(false);
	}

	//if(player.GetDestroy() == false) player.Update(_hWnd, this);

	bgOffsetX = (bgOffsetX + bgSpeed) % WINSIZE_X;
	alpha = (alpha + 5) % 255;
}

void OnGameSceneManager::LateUpdate() { }

void OnGameSceneManager::Release() {
	SAFE_RELEASE(backBuffer);
	SAFE_DELETE(backBuffer);
	IMG->DeleteImage(KEY_BACKGROUND_ONGAMESCENE);
}

void OnGameSceneManager::Render(HDC _hdc) {
	//*
	HDC memDC = GetBackBuffer()->GetMemDC();

	PatBlt(memDC, 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);

	RECT tmp{ 0, 0, WINSIZE_X, WINSIZE_Y };
	bgImage->LoopAlphaRender(memDC, &tmp, bgOffsetX, bgOffsetY, alpha);
	//*/

	//if (player.GetDestroy() == false) player.Render(memDC);

	//TextOut(memDC, 50, 70, NOTICE.c_str(), (int)NOTICE.length());

	//endBtn.Render(memDC);

	GetBackBuffer()->Render(_hdc, 0, 0);
}

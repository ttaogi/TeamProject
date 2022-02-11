#include "Stdafx/stdafx.h"

#include "DesignPattern/ComponentBase/Component/Button/Button.h"
#include "DesignPattern/ComponentBase/Component/RectTransform/RectTransform.h"
#include "DesignPattern/ComponentBase/Component/Rendered/RenderedImage/RenderedImage.h"
#include "DesignPattern/ComponentBase/GameObject/GameObject.h"
#include "TitleSceneManager.h"

TitleSceneManager::TitleSceneManager(MainGame* _mg)
	: SceneManager(SCENE_TYPE::TITLE, _mg)
{
	bgImage = NULL;
	{ // gameStartBtn.
		Button* btn = new Button();
		RectTransform* rcT = new RectTransform();
		RenderedImage* rImg = new RenderedImage();
		GameObject* gameStartBtn = new GameObject();
		btn->SetCallBack_v_CB_v(std::bind(&MainGame::SetNextScene_ONGAME, _mg));
		btn->Init();
		rcT->SetRect(RECT{ 0, 0, 200, 150 });
		rImg->SetImage(IMG->FindImage(KEY_UI_START_BUTTON_STRIPE));
		gameStartBtn->AddComponent(btn);
		gameStartBtn->AddComponent(rcT);
		gameStartBtn->AddComponent(rImg);
		gameObjects.push_back(gameStartBtn);
	}
}

void TitleSceneManager::SetBackBuffer() {
	SAFE_RELEASE(backBuffer);
	SAFE_DELETE(backBuffer);
	backBuffer = new Image();
	backBuffer->Init(WINSIZE_X, WINSIZE_Y);
}

void TitleSceneManager::Init(MainGame* _mg) {
	SetBackBuffer();

	bgImage = new Image();
	bgImage->Init(BACKGROUND_TITLESCENE, WINSIZE_X, WINSIZE_Y);
	bgImage->InitForAlphaBlend();
}

void TitleSceneManager::Update(HWND _hWnd) {
	for (GameObject* go : gameObjects) {
		for (Component* c : go->cList) {
			MonoBehaviour* m = IsDerivedFromMonoBehaviour(c);
			if (m != NULL) m->Update(_hWnd);
		}
	}
}

void TitleSceneManager::LateUpdate() { }

void TitleSceneManager::Release() { }

void TitleSceneManager::Render(HDC _hdc) {
	HDC memDC = GetBackBuffer()->GetMemDC();

	PatBlt(memDC, 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);

	bgImage->Render(memDC);

	for (GameObject* go : gameObjects) {
		RenderedImage* rImg = go->GetComponent<RenderedImage>();
		if (rImg) rImg->Render(memDC);
	}

	GetBackBuffer()->Render(_hdc, 0, 0);
}

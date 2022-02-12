#include "Stdafx/stdafx.h"

#include "DesignPattern/AbstractFactoryBase/AbstractFactoryBase.h"
#include "TitleSceneManager.h"

TitleSceneManager::TitleSceneManager(MainGame* _mg)
	: SceneManager(SCENE_TYPE::TITLE, _mg) { }

void TitleSceneManager::SetBackBuffer()
{
	SAFE_RELEASE(backBuffer);
	SAFE_DELETE(backBuffer);
	backBuffer = new Image();
	backBuffer->Init(WINSIZE_X, WINSIZE_Y);
}

void TitleSceneManager::Init(MainGame* _mg)
{
	SetBackBuffer();

	backgroundImage = IMG->FindImage(KEY_BACKGROUND_TITLESCENE);

	RECT gameStartBtnRc{ 0, 0, BUTTON_WIDTH, BUTTON_HEIGHT };
	GameObject* gameStartBtn = AbstractFactoryButton::GetSingleton()
		->GetObject(BUTTON_FACTORY_TYPE::DEFAULT,
			std::bind(&MainGame::SetNextScene_ONGAME, _mg),
			&gameStartBtnRc,
			IMG->FindImage(KEY_UI_START_BUTTON_STRIPE));
	gameStartBtn->GetComponent<Transform>()->SetPosition(F_POINT{WINSIZE_X / 2, WINSIZE_Y / 2});
	gameObjects.push_back(gameStartBtn);
}

void TitleSceneManager::Update(HWND _hWnd)
{
	for (GameObject* go : gameObjects)
		if(go->GetActive())
			for (Component* c : go->cList)
			{
				MonoBehaviour* m = IsDerivedFromMonoBehaviour(c);
				if (m != NULL) m->Update(_hWnd);
			}
}

void TitleSceneManager::LateUpdate() { }

void TitleSceneManager::Release()
{
	SAFE_RELEASE(backBuffer);
	SAFE_DELETE(backBuffer);
}

void TitleSceneManager::Render(HDC _hdc)
{
	HDC memDC = GetBackBuffer()->GetMemDC();

	PatBlt(memDC, 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);

	backgroundImage->Render(memDC);

	for (GameObject* go : gameObjects)
		if (go->GetActive()) {
			RenderedImage* rImg = go->GetComponent<RenderedImage>();
			if (rImg) rImg->Render(memDC);
		}

	GetBackBuffer()->Render(_hdc, 0, 0);
}

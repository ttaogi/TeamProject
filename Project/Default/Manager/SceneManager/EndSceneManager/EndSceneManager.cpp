#include "Stdafx/stdafx.h"

#include "DesignPattern/AbstractFactoryBase/AbstractFactoryBase.h"
#include "EndSceneManager.h"

EndSceneManager::EndSceneManager(MainGame* _mg)
	: SceneManager(SCENE_TYPE::TITLE, _mg) { }

EndSceneManager::~EndSceneManager() { }

void EndSceneManager::SetBackBuffer()
{
	SAFE_RELEASE(backBuffer);
	SAFE_DELETE(backBuffer);
	backBuffer = new Image;
	backBuffer->Init(WINSIZE_X, WINSIZE_Y);
}

void EndSceneManager::Init(MainGame* _mg)
{
	SetBackBuffer();

	backgroundImage = IMG->FindImage(KEY_BACKGROUND_ENDSCENE);

	RECT quitBtnRc{ 0, 0, BUTTON_WIDTH, BUTTON_HEIGHT };
	GameObject* quitBtn = AbstractFactoryButton::GetSingleton()
		->GetObject(BUTTON_FACTORY_TYPE::DEFAULT,
			std::bind(&MainGame::QuitGame, _mg),
			&quitBtnRc,
			IMG->FindImage(KEY_UI_QUIT_BUTTON_STRIPE));
	quitBtn->SetTag(QUIT_BUTTON_TAG);
	quitBtn->GetComponent<Transform>()
		->SetPosition(F_POINT{ WINSIZE_X / 2 - BUTTON_WIDTH - 50, WINSIZE_Y / 2 });
	gameObjects.push_back(quitBtn);

	RECT retryBtnRc{ 0, 0, BUTTON_WIDTH, BUTTON_HEIGHT };
	GameObject* retryBtn = AbstractFactoryButton::GetSingleton()
		->GetObject(BUTTON_FACTORY_TYPE::DEFAULT,
			std::bind(&MainGame::SetNextScene_ONGAME, _mg),
			&retryBtnRc,
			IMG->FindImage(KEY_UI_RETRY_BUTTON_STRIPE));
	retryBtn->SetTag(RETRY_BUTTON_TAG);
	retryBtn->GetComponent<Transform>()
		->SetPosition(F_POINT{ WINSIZE_X / 2 + BUTTON_WIDTH + 50, WINSIZE_Y / 2 });
	gameObjects.push_back(retryBtn);
}

void EndSceneManager::Update(HWND _hWnd) {
	for (GameObject* go : gameObjects)
		if (go->GetActive())
			for (Component* c : go->cList)
			{
				MonoBehaviour* m = IsDerivedFromMonoBehaviour(c);
				if (m != NULL) m->Update(_hWnd);
			}
}

void EndSceneManager::LateUpdate() { }

void EndSceneManager::Release() {
	SAFE_RELEASE(backBuffer);
	SAFE_DELETE(backBuffer);
}

void EndSceneManager::Render(HDC _hdc)
{
	HDC memDC = GetBackBuffer()->GetMemDC();

	PatBlt(memDC, 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);

	backgroundImage->Render(memDC, 0, 0);

	for (GameObject* go : gameObjects)
		if (go->GetActive()) {
			RenderedImage* rImg = go->GetComponent<RenderedImage>();
			if (rImg) rImg->Render(memDC);
		}

	GetBackBuffer()->Render(_hdc, 0, 0);
}

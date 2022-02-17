#include "Stdafx/stdafx.h"

#include "EndSceneManager.h"

#include "DesignPattern/AbstractFactoryBase/AbstractFactoryBase.h"
#include "DesignPattern/ComponentBase/Component/Button/Button.h"
#include "DesignPattern/ComponentBase/Component/Rendered/RenderedImage/RenderedImage.h"
#include "DesignPattern/ComponentBase/Component/Transform/Transform.h"
#include "DesignPattern/ComponentBase/GameObject/GameObject.h"

#define BUTTON_WIDTH	200
#define BUTTON_HEIGHT	150

EndSceneManager::EndSceneManager()
	: SceneManager(SCENE_TYPE::TITLE) { }

EndSceneManager::~EndSceneManager() { }

void EndSceneManager::Init()
{
	backgroundImage = IMG->FindImage(KEY_BACKGROUND_ENDSCENE);

	RECT quitBtnRc{ 0, 0, BUTTON_WIDTH, BUTTON_HEIGHT };
	GameObject* quitBtn = AbstractFactoryButton::GetSingleton()
		->GetObject(BUTTON_FACTORY_TYPE::DEFAULT,
			std::bind(&MainGame::QuitGame, MAIN_GAME),
			&quitBtnRc,
			IMG->FindImage(KEY_UI_QUIT_BUTTON_STRIPE));
	quitBtn->SetTag(QUIT_BUTTON_TAG);
	quitBtn->GetComponent<Transform>()
		->SetPosition(F_POINT{ WINSIZE_X / 2 - BUTTON_WIDTH - 50, WINSIZE_Y / 2 });
	gameObjects.push_back(quitBtn);

	RECT retryBtnRc{ 0, 0, BUTTON_WIDTH, BUTTON_HEIGHT };
	GameObject* retryBtn = AbstractFactoryButton::GetSingleton()
		->GetObject(BUTTON_FACTORY_TYPE::DEFAULT,
			std::bind(&MainGame::SetNextScene_ONGAME, MAIN_GAME),
			&retryBtnRc,
			IMG->FindImage(KEY_UI_RETRY_BUTTON_STRIPE));
	retryBtn->SetTag(RETRY_BUTTON_TAG);
	retryBtn->GetComponent<Transform>()
		->SetPosition(F_POINT{ WINSIZE_X / 2 + BUTTON_WIDTH + 50, WINSIZE_Y / 2 });
	gameObjects.push_back(retryBtn);
}

void EndSceneManager::Update() {
	for (GameObject* go : gameObjects)
		if (go->GetActive())
			for (Component* c : go->cList)
			{
				MonoBehaviour* m = IsDerivedFromMonoBehaviour(c);
				if (m != NULL) m->Update();
			}
}

void EndSceneManager::Release() { }

void EndSceneManager::Render()
{
	HDC memDC = MAIN_GAME->GetBackBuffer()->GetMemDC();

	PatBlt(memDC, 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);

	backgroundImage->Render(memDC, 0, 0);

	for (GameObject* go : gameObjects)
		if (go->GetActive()) {
			RenderedImage* rImg = go->GetComponent<RenderedImage>();
			if (rImg) rImg->Render(memDC);
		}
}

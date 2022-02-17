#include "Stdafx/stdafx.h"

#include "TitleSceneManager.h"

#include "DesignPattern/AbstractFactoryBase/AbstractFactoryBase.h"
#include "DesignPattern/ComponentBase/Component/Button/Button.h"
#include "DesignPattern/ComponentBase/Component/Rendered/RenderedImage/RenderedImage.h"
#include "DesignPattern/ComponentBase/Component/Transform/Transform.h"
#include "DesignPattern/ComponentBase/GameObject/GameObject.h"

#define BUTTON_WIDTH	200
#define BUTTON_HEIGHT	150

TitleSceneManager::TitleSceneManager()
	: SceneManager(SCENE_TYPE::TITLE) { }

void TitleSceneManager::Init()
{
	backgroundImage = IMG->FindImage(KEY_BACKGROUND_TITLESCENE);

	RECT gameStartBtnRc{ 0, 0, BUTTON_WIDTH, BUTTON_HEIGHT };
	GameObject* gameStartBtn = AbstractFactoryButton::GetSingleton()
		->GetObject(BUTTON_FACTORY_TYPE::DEFAULT,
			std::bind(&MainGame::SetNextScene_ONGAME, MAIN_GAME),
			&gameStartBtnRc,
			IMG->FindImage(KEY_UI_START_BUTTON_STRIPE));
	gameStartBtn->GetComponent<Transform>()->SetPosition(F_POINT{WINSIZE_X / 2, WINSIZE_Y / 2});
	gameObjects.push_back(gameStartBtn);
}

void TitleSceneManager::Update()
{
	for (GameObject* go : gameObjects)
		if(go->GetActive())
			for (Component* c : go->cList)
			{
				MonoBehaviour* m = IsDerivedFromMonoBehaviour(c);
				if (m != NULL) m->Update();
			}
}

void TitleSceneManager::Release() { }

void TitleSceneManager::Render()
{
	HDC memDC = MAIN_GAME->GetMemDC();

	PatBlt(memDC, 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);

	backgroundImage->Render(memDC);

	for (GameObject* go : gameObjects)
		if (go->GetActive()) {
			RenderedImage* rImg = go->GetComponent<RenderedImage>();
			if (rImg) rImg->Render(memDC);
		}
}

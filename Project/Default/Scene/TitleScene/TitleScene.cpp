#include "Stdafx/stdafx.h"

#include "TitleScene.h"

#include <functional>

#include "DesignPattern/AbstractFactoryBase/AbstractFactoryBase.h"
#include "DesignPattern/ComponentBase/Component/Button/Button.h"
#include "DesignPattern/ComponentBase/Component/Rendered/RenderedImage/RenderedImage.h"
#include "DesignPattern/ComponentBase/Component/Transform/Transform.h"
#include "DesignPattern/ComponentBase/GameObject/GameObject.h"

#define BUTTON_WIDTH	200
#define BUTTON_HEIGHT	150

TitleScene::TitleScene() { }

TitleScene::~TitleScene() { }

HRESULT TitleScene::Init()
{
	backgroundImage = IMG->FindImage(KEY_BACKGROUND_TITLESCENE);

	RECT gameStartBtnRc{ 0, 0, BUTTON_WIDTH, BUTTON_HEIGHT };
	GameObject* gameStartBtn = AbstractFactoryButton::GetSingleton()
		->GetObject(BUTTON_FACTORY_TYPE::DEFAULT,
			std::bind(&SceneManager::SetNextSceneKeyOnGameScene, SCENE),
			&gameStartBtnRc,
			IMG->FindImage(KEY_UI_START_BUTTON_STRIPE));
	gameStartBtn->GetComponent<Transform>()->SetPosition(F_POINT{WINSIZE_X / 2, WINSIZE_Y / 2});
	gameObjects.push_back(gameStartBtn);

	SOUND->Play(KEY_SOUND_EXAMPLE, 1.0f);

	return S_OK;
}

void TitleScene::Update()
{
	SOUND->Update();
	for (GameObject* go : gameObjects)
		if(go->GetActive())
			for (Component* c : go->cList)
			{
				MonoBehaviour* m = IsDerivedFromMonoBehaviour(c);
				if (m != NULL) m->Update();
			}
}

void TitleScene::Release() {
	SOUND->AllStop();
}

void TitleScene::Render()
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

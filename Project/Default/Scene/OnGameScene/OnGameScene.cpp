#include "Stdafx/stdafx.h"

#include "OnGameScene.h"

#include <functional>

#include "DesignPattern/AbstractFactoryBase/AbstractFactoryBase.h"
#include "DesignPattern/ComponentBase/Component/Button/Button.h"
#include "DesignPattern/ComponentBase/Component/Rendered/RenderedImage/RenderedImage.h"
#include "DesignPattern/ComponentBase/Component/Transform/Transform.h"
#include "DesignPattern/ComponentBase/GameObject/GameObject.h"

#define BUTTON_WIDTH	200
#define BUTTON_HEIGHT	150

OnGameScene::OnGameScene() { }

OnGameScene::~OnGameScene() { }

HRESULT OnGameScene::Init()
{
	backgroundImage = IMG->FindImage(KEY_BACKGROUND_ONGAMESCENE);

	RECT quitBtnRc{ 0, 0, BUTTON_WIDTH, BUTTON_HEIGHT };
	GameObject* quitBtn = AbstractFactoryButton::GetSingleton()
		->GetObject(BUTTON_FACTORY_TYPE::DEFAULT,
			std::bind(&SceneManager::SetNextSceneKeyEndScene, SCENE),
			&quitBtnRc,
			IMG->FindImage(KEY_UI_QUIT_BUTTON_STRIPE));
	quitBtn->SetTag(QUIT_BUTTON_TAG);
	quitBtn->GetComponent<Transform>()
		->SetPosition(F_POINT{ WINSIZE_X / 2, WINSIZE_Y / 2 });
	gameObjects.push_back(quitBtn);

	msg = L"";
	mapInfo = MAP_INFO->GetMapInfo(MAP_ID::EXAMPLE_MAP);
	if (mapInfo == NULL) return E_FAIL;

	alpha = 0;
	bgSpeed = 20;
	bgOffsetX = 0;
	bgOffsetY = 0;

	return S_OK;
}

void OnGameScene::Update()
{
	if (KEY->IsOnceKeyDown('Q'))
		for (GameObject* go : gameObjects)
			if (wcscmp(go->GetTag().c_str(), QUIT_BUTTON_TAG.c_str()) == 0)
				go->SetActive(!go->GetActive());

	for (GameObject* go : gameObjects)
		if (go->GetActive())
			for (Component* c : go->cList)
			{
				MonoBehaviour* m = IsDerivedFromMonoBehaviour(c);
				if (m != NULL) m->Update();
			}

	bgOffsetX = (bgOffsetX + bgSpeed) % WINSIZE_X;
	alpha = (alpha + 5) % 255;
}

void OnGameScene::Release() { }

void OnGameScene::Render()
{
	HDC memDC = MAIN_GAME->GetBackBuffer()->GetMemDC();

	PatBlt(memDC, 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);

	RECT tmp{ 0, 0, WINSIZE_X, WINSIZE_Y };
	backgroundImage->LoopAlphaRender(memDC, &tmp, bgOffsetX, bgOffsetY, alpha);

	for (GameObject* go : gameObjects)
		if (go->GetActive()) {
			RenderedImage* rImg = go->GetComponent<RenderedImage>();
			if (rImg) rImg->Render(memDC);
		}

	//TextOut(memDC, 50, 70, NOTICE.c_str(), (int)NOTICE.length());
}

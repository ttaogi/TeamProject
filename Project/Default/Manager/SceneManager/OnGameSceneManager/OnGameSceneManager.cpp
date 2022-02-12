#include "Stdafx/stdafx.h"

#include "DesignPattern/AbstractFactoryBase/AbstractFactoryBase.h"
#include "OnGameSceneManager.h"

OnGameSceneManager::OnGameSceneManager(MainGame* _mg)
	: SceneManager(SCENE_TYPE::ONGAME, _mg)
{
	msg = L"";

	alpha = 0;
	bgSpeed = 20;
	bgOffsetX = 0;
	bgOffsetY = 0;
}

OnGameSceneManager::~OnGameSceneManager() { }

void OnGameSceneManager::SetBackBuffer()
{
	SAFE_RELEASE(backBuffer);
	SAFE_DELETE(backBuffer);
	backBuffer = new Image;
	backBuffer->Init(WINSIZE_X, WINSIZE_Y);
}

void OnGameSceneManager::Init(MainGame* _mg)
{
	SetBackBuffer();

	backgroundImage = IMG->FindImage(KEY_BACKGROUND_ONGAMESCENE);

	RECT quitBtnRc{ 0, 0, BUTTON_WIDTH, BUTTON_HEIGHT };
	GameObject* quitBtn = AbstractFactoryButton::GetSingleton()
		->GetObject(BUTTON_FACTORY_TYPE::DEFAULT,
			std::bind(&MainGame::SetNextScene_END, _mg),
			&quitBtnRc,
			IMG->FindImage(KEY_UI_QUIT_BUTTON_STRIPE));
	quitBtn->SetTag(QUIT_BUTTON_TAG);
	quitBtn->GetComponent<Transform>()
		->SetPosition(F_POINT{ WINSIZE_X / 2, WINSIZE_Y / 2 });
	gameObjects.push_back(quitBtn);
}

void OnGameSceneManager::Update(HWND _hWnd)
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
				if (m != NULL) m->Update(_hWnd);
			}

	bgOffsetX = (bgOffsetX + bgSpeed) % WINSIZE_X;
	alpha = (alpha + 5) % 255;
}

void OnGameSceneManager::LateUpdate() { }

void OnGameSceneManager::Release()
{
	SAFE_RELEASE(backBuffer);
	SAFE_DELETE(backBuffer);
}

void OnGameSceneManager::Render(HDC _hdc)
{
	HDC memDC = GetBackBuffer()->GetMemDC();

	PatBlt(memDC, 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);

	RECT tmp{ 0, 0, WINSIZE_X, WINSIZE_Y };
	backgroundImage->LoopAlphaRender(memDC, &tmp, bgOffsetX, bgOffsetY, alpha);

	for (GameObject* go : gameObjects)
		if (go->GetActive()) {
			RenderedImage* rImg = go->GetComponent<RenderedImage>();
			if (rImg) rImg->Render(memDC);
		}

	//TextOut(memDC, 50, 70, NOTICE.c_str(), (int)NOTICE.length());

	GetBackBuffer()->Render(_hdc, 0, 0);
}

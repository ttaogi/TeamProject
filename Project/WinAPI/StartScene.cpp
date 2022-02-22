#include "Stdafx.h"
#include "StartScene.h"

#include "MainGame.h"

HRESULT StartScene::init(void)
{
	IMAGEMANAGER->addImage("시작화면", "Resources/Images/BackGround/startBack.bmp", WINSIZEX, WINSIZEY);

	wsprintf(_text, "Start Scene");

	return S_OK;
}

void StartScene::release(void)
{
}

void StartScene::update(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
		SCENEMANAGER->changeScene("슈팅");
	if (KEYMANAGER->isOnceKeyDown('Q'))
	{
		_mg->quitGame();
		return;
	}
}

void StartScene::render(void)
{
	IMAGEMANAGER->render("시작화면", getMemDC());

	TextOut(getMemDC(), CENTER_X, CENTER_Y, _text, strlen(_text));
}
#include "Stdafx.h"

#include "StartScene.h"

#include "MainGame.h"

HRESULT StartScene::init(void)
{
	background = IMAGEMANAGER->findImage(KEY_BACKGROUND_START_SCENE);
	pressAnyKey = IMAGEMANAGER->findImage(KEY_UI_PRESS_ANY_KEY);

	SOUNDMANAGER->allStop();
	SOUNDMANAGER->play(KEY_BGM_MAIN_MENU, DEFAULT_VOLUME);

	return S_OK;
}

void StartScene::release(void) { }

void StartScene::update(void)
{
	if (KEYMANAGER->isOnceAnyKeyDown())
	{ // a-z, 0-9, space, enter.
		_mg->setNextScene(KEY_SCENE_LOBBY);
		return;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_ESCAPE))
	{
		_mg->quitGame();
		return;
	}
}

void StartScene::render(void)
{
	background->render(getMemDC(), 0, 0);
	pressAnyKey->alphaRender(getMemDC(), (WINSIZEX - pressAnyKey->getWidth()) / 2,
		WINSIZEY - 44, (BYTE)(63 + 192 * abs(sin(TIMEMANAGER->getWorldTime()))));
}
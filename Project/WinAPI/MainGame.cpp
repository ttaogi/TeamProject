#include "Stdafx.h"

#include "MainGame.h"

#include "LobbyScene.h"
#include "StartScene.h"

HRESULT MainGame::init(void)
{
	GameNode::init(TRUE);

	nextSceneKey = KEY_SCENE_NONE;
	quit = false;

	SCENEMANAGER->addScene(KEY_SCENE_START, new StartScene);
	SCENEMANAGER->addScene(KEY_SCENE_LOBBY, new LobbyScene);
	SCENEMANAGER->changeScene(KEY_SCENE_START);

	return S_OK;
}

void MainGame::release(void) { GameNode::release(); }

void MainGame::update(void)
{
	if (quit)
	{
		PostQuitMessage(0);
		return;
	}

	if (nextSceneKey != KEY_SCENE_NONE)
	{
		SCENEMANAGER->changeScene(nextSceneKey);
		nextSceneKey = KEY_SCENE_NONE;
	}

	TIMEMANAGER->update(60.0f);
	GameNode::update();
	SCENEMANAGER->update();
}

void MainGame::render(void)
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);

	SCENEMANAGER->render();
	TIMEMANAGER->render(getMemDC());
	
	this->getBackBuffer()->render(getHDC());
}

void MainGame::quitGame() { quit = true; }

void MainGame::setNextScene(std::string _nextSceneKey) { nextSceneKey = _nextSceneKey; }

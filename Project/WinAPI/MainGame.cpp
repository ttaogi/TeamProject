#include "Stdafx.h"
#include "MainGame.h"
#include "StartScene.h"
#include "ShootingScene.h"
#include "PixelScene.h"

HRESULT MainGame::init(void)
{
	GameNode::init(TRUE);

	quit = false;

	SCENEMANAGER->addScene("����", new ShootingScene);
	SCENEMANAGER->addScene("����", new StartScene);
	SCENEMANAGER->addScene("�ȼ��浹", new PixelScene);
	SCENEMANAGER->changeScene("����");

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

#include "Stdafx.h"
#include "MainGame.h"
#include "StartScene.h"
#include "ShootingScene.h"
#include "PixelScene.h"

HRESULT MainGame::init(void)
{
	GameNode::init(TRUE);

	SCENEMANAGER->addScene("슈팅", new ShootingScene);
	SCENEMANAGER->addScene("시작", new StartScene);
	SCENEMANAGER->addScene("픽셀충돌", new PixelScene);

	//======================================================
	
	SCENEMANAGER->changeScene("슈팅");
	return S_OK;
}

void MainGame::release(void)
{
	GameNode::release();
}

void MainGame::update(void)
{
	GameNode::update();

	SCENEMANAGER->update();
}

void MainGame::render(void)
{
	//검은색 빈 비트맵
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
	//================================


	SCENEMANAGER->render();
	TIMEMANAGER->render(getMemDC());
	
	//================================
	//백버퍼의 내용을 HDC에 그린다
	this->getBackBuffer()->render(getHDC());
}


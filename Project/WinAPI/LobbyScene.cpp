#include "Stdafx.h"
#include "LobbyScene.h"

#include "MainGame.h"
#include "Player.h"

HRESULT LobbyScene::init(void)
{
	mapInfo = MAPINFOMANAGER->getMapInfo(MAP_ID::EXAMPLE_MAP);
	if (mapInfo == NULL) return E_FAIL;

	player = new Player();
	player->init();
	player->Move(mapInfo->getStartPos());

	_plEquip = new PlEquip;
	_plEquip->init();

	_plGold = new PlGold;
	_plGold->init();

	_plHp = new PlHp;
	_plHp->init();
	
	_Note = new RhythmNote;
	_Note->init();

	return S_OK;
}

void LobbyScene::release(void)
{
	SAFE_RELEASE(player);
	SAFE_DELETE(player);
}

void LobbyScene::update(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_ESCAPE))
	{
		_mg->quitGame();
		return;
	}
	player->update();
}

void LobbyScene::render(void)
{
	mapInfo->render(getMemDC());
	player->render();

	_plEquip->render();
	_plGold->render();
	_plHp->render();
	_Note->render();
}

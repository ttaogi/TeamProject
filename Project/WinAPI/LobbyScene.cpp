#include "Stdafx.h"

#include "LobbyScene.h"

#include <queue>

#include "MainGame.h"
#include "Player.h"
#include "Slime.h"
#include "slimeBlue.h"
#include "Skeleton.h"
#include "Bat.h"
#include "Wall.h"

HRESULT LobbyScene::init(void)
{
	mapInfo = MAPINFOMANAGER->getMapInfo(MAP_ID::EXAMPLE_MAP, this);
	if (mapInfo == NULL) return E_FAIL;

	objectVec = mapInfo->getObjectVec();

	if (mapInfo->getBgmKey() != "")
		SOUNDMANAGER->play(mapInfo->getBgmKey(), 1.0f);

	player = new Player();
	player->init(this);
	player->Move(mapInfo->getStartPos());

	skeleton = new Skeleton();
	skeleton->init(this, POINT{ 7, 8 });

	bat = new Bat();
	bat->init(this, POINT{ 3, 8 });

	objectVec.push_back(skeleton);
	objectVec.push_back(bat);
	
	// UI.
	_plEquip = new PlEquip;
	_plEquip->init();

	_plGold = new PlGold;
	_plGold->init();

	_plHp = new PlHp;
	_plHp->init();
	
	_Note = new RhythmNote;
	_Note->init("", 300, 1000);
	
	return S_OK;
}

void LobbyScene::release(void)
{
	SOUNDMANAGER->allStop();
	SAFE_RELEASE(player);
	SAFE_DELETE(player);
	for (auto iter = objectVec.begin(); iter != objectVec.end(); ++iter)
	{
		SAFE_RELEASE((*iter));
		SAFE_DELETE((*iter));
	}
	objectVec.clear();
}

void LobbyScene::update(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_ESCAPE))
	{
		_mg->quitGame();
		return;
	}

	SOUNDMANAGER->update();

	player->update();

	for (auto iter = objectVec.begin(); iter != objectVec.end(); ++iter)
		(*iter)->update();
	for (auto iter = objectVec.begin(); iter != objectVec.end();)
	{
		if ((*iter)->getDestroyed())
			iter = objectVec.erase(iter);
		else ++iter;
	}

	_Note->update();
}

void LobbyScene::render(void)
{
	mapInfo->render(getMemDC());

	priority_queue<GameNode*, vector<GameNode*>, CmpGameNodePtrs> pQue;

	pQue.push(player);
	for (auto iter = objectVec.begin(); iter != objectVec.end(); ++iter)
		pQue.push((*iter));

	while (!pQue.empty())
	{
		pQue.top()->render();
		pQue.pop();
	}

	_plEquip->render();
	_plGold->render();
	_plHp->render();
	_Note->render();
}

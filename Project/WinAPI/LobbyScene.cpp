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
#include "SteppingStone.h"

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

	SteppingStoneRight *ssr = new SteppingStoneRight();
	ssr->init(this, POINT{ 8, 8 });

	SteppingStoneLeft *ssl = new SteppingStoneLeft();
	ssl->init(this, POINT{ 10, 8 });

	SteppingStoneTop *sst = new SteppingStoneTop();
	sst->init(this, POINT{ 9, 9 });

	SteppingStoneBottom *ssb = new SteppingStoneBottom();
	ssb->init(this, POINT{ 9, 7 });

	objectVec.push_back(skeleton);
	objectVec.push_back(bat);
	objectVec.push_back(ssr);
	objectVec.push_back(ssl);
	objectVec.push_back(sst);
	objectVec.push_back(ssb);
	
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
	_plHp->update();
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

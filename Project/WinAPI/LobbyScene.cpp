#include "Stdafx.h"

#include "LobbyScene.h"

#include <queue>

#include "Bat.h"
#include "MainGame.h"
#include "Money.h"
#include "Player.h"
#include "Skeleton.h"
#include "Slime.h"
#include "slimeBlue.h"
#include "Necrodancer.h"
#include "SteppingStone.h"
#include "Wall.h"
#include "Head.h"

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
	bat->init(this, POINT{ 3, 7 });

	necrodancer = new Necrodancer();
	necrodancer->init(this, POINT{ 12, 3 });

	SteppingStoneRight *ssr = new SteppingStoneRight();
	ssr->init(this, POINT{ 8, 8 });

	SteppingStoneLeft *ssl = new SteppingStoneLeft();
	ssl->init(this, POINT{ 10, 8 });

	SteppingStoneTop *sst = new SteppingStoneTop();
	sst->init(this, POINT{ 9, 9 });

	SteppingStoneBottom *ssb = new SteppingStoneBottom();
	ssb->init(this, POINT{ 9, 7 });

	Head *head = new Head();
	head->init(this, POINT{ 1, 7 });

	Money* money = new Money();
	money->init(this, POINT{ 11, 8 });
	money->setQuantity(5);

	objectVec.push_back(skeleton);
	objectVec.push_back(bat);
	objectVec.push_back(necrodancer);
	objectVec.push_back(ssr);
	objectVec.push_back(ssl);
	objectVec.push_back(sst);
	objectVec.push_back(ssb);
	objectVec.push_back(money);

	objectVec.push_back(head);
	
	// UI.
	_plEquip = new PlEquip;
	_plEquip->init();

	_plGold = new PlGold;
	_plGold->init();

	_plHp = new PlHp;
	_plHp->init();
	
	_Note = new RhythmNote;
	_Note->init("", 300, 1000);

	CAMERAMANAGER->init(player);
	
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
	_plGold->update();

	CAMERAMANAGER->update();
	SOUNDMANAGER->update();
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
	_plHp->render();
	_Note->render();
	_plGold->render();
}

#include "Stdafx.h"

#include "BossScene.h"

#include <queue>

#include "Attack.h"
#include "Bat.h"
#include "Body.h"
#include "Bomb.h"
#include "Explosion.h"
#include "GameUI.h"
#include "Head.h"
#include "Heal.h"
#include "MainGame.h"
#include "Money.h"
#include "Necrodancer.h"
#include "Player.h"
#include "Skeleton.h"
#include "Slime.h"
#include "slimeBlue.h"
#include "Stair.h"
#include "SteppingStone.h"
#include "Torch.h"
#include "Wall.h"

HRESULT BossScene::init(void)
{
	mapInfo = MAPINFOMANAGER->getMapInfo(MAP_ID::BOSS_MAP, this);
	if (mapInfo == NULL) return E_FAIL;

	objectVec = mapInfo->getObjectVec();

	for (auto obj = objectVec.begin(); obj != objectVec.end(); ++obj)
		if ((*obj)->getType() == OBJECT_TYPE::STAIR)
			((Stair*)(*obj))->setNextSceneKey(KEY_SCENE_START);

	SOUNDMANAGER->allStop();
	if (mapInfo->getBgmKey() != "")
		SOUNDMANAGER->play(mapInfo->getBgmKey(), DEFAULT_VOLUME);

	player = new Player();
	player->init(this);
	player->Move(mapInfo->getStartPos());

	// UI.
	_plEquip = new PlEquip;
	_plEquip->init();

	_plGold = new PlGold;
	_plGold->init();

	_plHp = new PlHp;
	_plHp->init();

	_Note = new RhythmNote;
	_Note->init(this);

	CAMERAMANAGER->init(player);

	return S_OK;
}

void BossScene::release(void)
{
	SAFE_RELEASE(player);
	SAFE_DELETE(player);
	for (auto iter = objectVec.begin(); iter != objectVec.end(); ++iter)
	{
		SAFE_RELEASE((*iter));
		SAFE_DELETE((*iter));
	}
	objectVec.clear();
}

void BossScene::update(void)
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

void BossScene::render(void)
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

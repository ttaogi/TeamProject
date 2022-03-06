#include "Stdafx.h"

#include "DungeonScene.h"

#include <queue>

#include "Attack.h"
#include "Bat.h"
#include "Body.h"
#include "Bomb.h"
#include "Explosion.h"
#include "Head.h"
#include "Heal.h"
#include "MainGame.h"
#include "Money.h"
#include "Necrodancer.h"
#include "Player.h"
#include "Shopkeeper.h"
#include "Skeleton.h"
#include "Slime.h"
#include "slimeBlue.h"
#include "Stair.h"
#include "SteppingStone.h"
#include "Torch.h"
#include "Wall.h"

HRESULT DungeonScene::init(void)
{
	minimap = new Image();
	minimap->init(MINIMAP_WIDTH, MINIMAP_HEIGHT);
	PatBlt(minimap->getMemDC(), 0, 0, MINIMAP_WIDTH, MINIMAP_HEIGHT, BLACKNESS);
	minimap->setTransColor(true, RGB(0, 0, 0));

	mapInfo = MAPINFOMANAGER->getMapInfo(MAP_ID::DUGEON_MAP, this);
	if (mapInfo == NULL) return E_FAIL;

	objectVec = mapInfo->getObjectVec();
	bgmLength = mapInfo->getBgmPlayTime();
	sceneInitTime = TIMEMANAGER->getWorldTime();

	for (auto obj = objectVec.begin(); obj != objectVec.end(); ++obj)
		if ((*obj)->getType() == OBJECT_TYPE::STAIR)
			((Stair*)(*obj))->setNextSceneKey(KEY_SCENE_BOSS);

	player = new Player();
	player->init(this);
	player->Move(mapInfo->getStartPos());

	for (auto obj = objectVec.begin(); obj != objectVec.end(); ++obj)
		if ((*obj)->getType() == OBJECT_TYPE::NPC_SHOP)
			shopkeeper = (Shopkeeper*)(*obj);

	SOUNDMANAGER->allStop();
	if (mapInfo->getBgmKey() != "")
		SOUNDMANAGER->play(mapInfo->getBgmKey(), DEFAULT_VOLUME);
	SOUNDMANAGER->setSound3DInfo(
		(float)(GridPointToPixelPointCenter(shopkeeper->getPos()).x),
		(float)(GridPointToPixelPointCenter(shopkeeper->getPos()).y), 0);
	SOUNDMANAGER->play3DSound(DEFAULT_VOLUME * 5, 0, 0, 0);
	SOUNDMANAGER->updateListener(GridPointToPixelPointCenter(player->getPos()));

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

void DungeonScene::release(void)
{
	SAFE_RELEASE(player);
	SAFE_DELETE(player);
	for (auto iter = objectVec.begin(); iter != objectVec.end(); ++iter)
	{
		SAFE_RELEASE((*iter));
		SAFE_DELETE((*iter));
	}
	objectVec.clear();
	for (auto iter = effectVec.begin(); iter != effectVec.end(); ++iter)
	{
		SAFE_RELEASE((*iter));
		SAFE_DELETE((*iter));
	}
	effectVec.clear();
	SAFE_RELEASE(minimap);
	SAFE_DELETE(minimap);
}

void DungeonScene::update(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_ESCAPE))
	{
		_mg->quitGame();
		return;
	}

	if (PLAYERINFOMANAGER->getHp() <= 0)
	{
		_mg->setNextScene(KEY_SCENE_LOBBY);
		return;
	}
	if (TIMEMANAGER->getWorldTime() - sceneInitTime > bgmLength)
	{
		_mg->setNextScene(KEY_SCENE_BOSS);
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

	for (auto iter = effectVec.begin(); iter != effectVec.end(); ++iter)
		(*iter)->update();
	for (auto iter = effectVec.begin(); iter != effectVec.end();)
	{
		if ((*iter)->getDestroyed())
			iter = effectVec.erase(iter);
		else ++iter;
	}

	_Note->update();
	_plHp->update();
	_plGold->update();

	CAMERAMANAGER->update();
	SOUNDMANAGER->setSound3DInfo(
		(float)(GridPointToPixelPointCenter(shopkeeper->getPos()).x),
		(float)(GridPointToPixelPointCenter(shopkeeper->getPos()).y), 0);
	SOUNDMANAGER->updateListener(GridPointToPixelPointCenter(player->getPos()));
	SOUNDMANAGER->update();
}

void DungeonScene::render(void)
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

	for (auto iter = effectVec.begin(); iter != effectVec.end(); ++iter)
		(*iter)->render();

	// minimap.
	if (minimap)
	{
		mapInfo->renderMinimap(minimap->getMemDC());
		for (auto iter = objectVec.begin(); iter != objectVec.end(); ++iter)
			(*iter)->renderMinimap(minimap->getMemDC());
		player->renderMinimap(minimap->getMemDC());

		minimap->render(getMemDC(), WINSIZEX - MINIMAP_WIDTH, WINSIZEY - MINIMAP_HEIGHT);
	}

	_plEquip->render();
	_plHp->render();
	_Note->render();
	_plGold->render();
}

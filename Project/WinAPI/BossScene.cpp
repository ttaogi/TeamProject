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
	minimap = new Image();
	minimap->init(MINIMAP_WIDTH, MINIMAP_HEIGHT);
	PatBlt(minimap->getMemDC(), 0, 0, MINIMAP_WIDTH, MINIMAP_HEIGHT, BLACKNESS);
	minimap->setTransColor(true, RGB(0, 0, 0));

	mapInfo = MAPINFOMANAGER->getMapInfo(MAP_ID::BOSS_MAP, this);
	if (mapInfo == NULL) return E_FAIL;

	objectVec = mapInfo->getObjectVec();

	for (auto obj = objectVec.begin(); obj != objectVec.end(); ++obj)
		if ((*obj)->getType() == OBJECT_TYPE::STAIR)
			((Stair*)(*obj))->setNextSceneKey(KEY_SCENE_LOBBY);

	objectVec.reserve(objectVec.size() * 1.5);

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

	// bossRoomOpen
	IMAGEMANAGER->addImage(KEY_BG_TOPBLADE, DIR_BG_TOPBLADE, 602, 68, true, MAGENTA);
	IMAGEMANAGER->addImage(KEY_BG_GRADIENT, DIR_BG_GRADIENT, 1920, 296, true, MAGENTA);
	IMAGEMANAGER->addImage(KEY_BG_BOTTOMBLADE, DIR_BG_BOTTOMBLADE, 728, 96, true, MAGENTA);
	IMAGEMANAGER->addImage(KEY_BG_GRADIENT2, DIR_BG_GRADIENT2, 960, 413, true, MAGENTA);
	IMAGEMANAGER->addImage(KEY_BG_BOTTOMBLADE2, DIR_BG_BOTTOMBLADE2, 728, 96, true, MAGENTA);

	upBarRect = RectMake(-590, 43, 602, 68);
	necOpenRect = RectMake(970, 0, 960, 413);
	downBarRect = RectMake(970, 427, 728, 96);

	turnCount = 0;
	turnCount1 = 0;
	turnCount2 = 0;
	turnCount3 = 0;
	turnCount1TF = false;
	turnCount2TF = false;
	turnCount3TF = false;
	upBarTF = true;
	bossBarTF = true;
	bottomBarTF = true;
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
	for (auto iter = effectVec.begin(); iter != effectVec.end(); ++iter)
	{
		SAFE_RELEASE((*iter));
		SAFE_DELETE((*iter));
	}
	effectVec.clear();
	SAFE_RELEASE(minimap);
	SAFE_DELETE(minimap);
}

void BossScene::update(void)
{
	turnCount += TIMEMANAGER->getElapsedTime();
	turnCount1 += TIMEMANAGER->getElapsedTime();
	turnCount2 += TIMEMANAGER->getElapsedTime();
	turnCount3 += TIMEMANAGER->getElapsedTime();
	
	if (upBarTF)
	{
		if (turnCount >= 0.1f)
		{
			upBarRect.right += 20;
			upBarRect.left += 20;

			if (upBarRect.left >= 0)
			{
				upBarRect.right = 602;
				upBarRect.left = 0;
			}
		}
	}
	
	if (turnCount >= 1.5f)
	{
		upBarTF = false;
	}

	if (!upBarTF)
	{
		if (turnCount >= 0.1f)
		{
			upBarRect.right -= 20;
			upBarRect.left -= 20;
		}
	}

	if (bossBarTF)
	{
		if (turnCount >= 0.2f)
		{
			necOpenRect.right -= 30;
			necOpenRect.left -= 30;

		if (necOpenRect.left <= 0)
			{
				necOpenRect.right = 960;
				necOpenRect.left = 0;
			}
		}
	}

	if (turnCount >= 1.5f)
	{
		bossBarTF = false;
	}

	if (!bossBarTF)
	{
		if (turnCount >= 0.2f)
		{
			necOpenRect.right += 30;
			necOpenRect.left += 30;
		}
	}


	if (bottomBarTF)
	{
		if (turnCount >= 0.2f)
		{
			downBarRect.right -= 30;
			downBarRect.left -= 30;

			if (downBarRect.right <= 960)
			{
				downBarRect.right = 958;
				downBarRect.left = 230;
			}
		}
	}

	if (turnCount >= 1.5f)
	{
		bottomBarTF = false;
	}

	if (!bottomBarTF)
	{
		if (turnCount >= 0.2f)
		{
			downBarRect.right += 30;
			downBarRect.left += 30;
		}
	}


	if (KEYMANAGER->isOnceKeyDown(VK_ESCAPE))
	{
		_mg->quitGame();
		return;
	}

	player->update();

	for (auto iter = objectVec.begin(); iter != objectVec.end(); ++iter)
	{
		(*iter)->update();
	}
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

	IMAGEMANAGER->render(KEY_BG_TOPBLADE, getMemDC(), upBarRect.left, upBarRect.top);
	IMAGEMANAGER->render(KEY_BG_GRADIENT2, getMemDC(), necOpenRect.left, necOpenRect.top);
	IMAGEMANAGER->render(KEY_BG_BOTTOMBLADE2, getMemDC(), downBarRect.left, downBarRect.top);

	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		Rectangle(getMemDC(), upBarRect.left, upBarRect.top, upBarRect.right, upBarRect.bottom);
		Rectangle(getMemDC(), necOpenRect.left, necOpenRect.top, necOpenRect.right, necOpenRect.bottom);
		Rectangle(getMemDC(), downBarRect.left, downBarRect.top, downBarRect.right, downBarRect.bottom);
	}
}

#include "Stdafx.h"

#include "LobbyScene.h"

#include <queue>

#include "MainGame.h"
#include "Player.h"
#include "Slime.h"
#include "slimeBlue.h"
#include "Wall.h"

HRESULT LobbyScene::init(void)
{
	mapInfo = MAPINFOMANAGER->getMapInfo(MAP_ID::EXAMPLE_MAP);
	if (mapInfo == NULL) return E_FAIL;
	objectVec = mapInfo->getObjectVec();

	player = new Player();
	player->init(this);
	player->Move(mapInfo->getStartPos());

	slime = new Slime();
	slime->init("KEY_SLIME", POINT{ 15, 8 });

	slimeBlue = new SlimeBlue();
	slimeBlue->init("KEY_SLIME", POINT{ 15, 10 });

	return S_OK;
}

void LobbyScene::release(void)
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

void LobbyScene::update(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_ESCAPE))
	{
		_mg->quitGame();
		return;
	}

	player->update();
	slime->update();
	slimeBlue->update();

	for (auto iter = objectVec.begin(); iter != objectVec.end(); ++iter)
		(*iter)->update();
	for (auto iter = objectVec.begin(); iter != objectVec.end();)
	{
		if ((*iter)->getDestroyed())
		{
			SAFE_RELEASE((*iter));
			SAFE_DELETE((*iter));
			iter = objectVec.erase(iter);
		}
		else ++iter;
	}
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

	slime->render();
	slimeBlue->render();
}

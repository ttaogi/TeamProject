#include "Stdafx.h"

#include "LobbyScene.h"

#include <queue>

#include "GameNode.h"
#include "MainGame.h"
#include "Player.h"
#include "Wall.h"
#include "Slime.h"

HRESULT LobbyScene::init(void)
{
	mapInfo = MAPINFOMANAGER->getMapInfo(MAP_ID::EXAMPLE_MAP);
	if (mapInfo == NULL) return E_FAIL;
	objectVec = mapInfo->getObjectVec();

	player = new Player();
	player->init();
	player->Move(mapInfo->getStartPos());

	slime = new Slime();
	slime->init();


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
	for (auto iter = objectVec.begin(); iter != objectVec.end(); ++iter)
		(*iter)->update();
}

void LobbyScene::render(void)
{
	mapInfo->render(getMemDC());

	/*player->render();
	for (auto iter = objectVec.begin(); iter != objectVec.end(); ++iter)
		(*iter)->render();*/

	priority_queue<GameNode*, vector<GameNode*>, CmpGameNodePtrs> pQue;

	pQue.push(player);
	for (auto iter = objectVec.begin(); iter != objectVec.end(); ++iter)
		pQue.push((*iter));

	while (!pQue.empty())
	{
		pQue.top()->render();
		pQue.pop();
	}
}

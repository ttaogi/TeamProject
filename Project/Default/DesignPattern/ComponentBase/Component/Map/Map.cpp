#include "Stdafx/stdafx.h"

#include "DesignPattern/ComponentBase/Component/Map/Map.h"

#include "DesignPattern/ComponentBase/GameObject/GameObject.h"
#include "DesignPattern/ComponentBase/Component/Rendered/RenderedAnimator/RenderedAnimator.h"
#include "Player/Player.h"

Map::Map()
	: Component((const Component_ID)typeid(Map).name()) { }

Map::~Map() { }

void Map::Operation() { }

void Map::Init(MAP_ID _mapId)
{
	mapInfo = MAP_INFO->GetMapInfo(_mapId);

	initTime = TIME->GetWorldTime();
	timeCount = 0.0f;
	turnInterval = mapInfo->GetTurnInterval();
	
	// create player, monsters, objects.
	GameObject* player = new GameObject();
	player->SetParent(gameObject);
	player->SetTag(L"PLAYER");

	Player* playerControl = new Player();
	playerControl->SetPos(mapInfo->GetStartPos());
	player->AddComponent(playerControl);

	RenderedAnimator* rAnim = new RenderedAnimator();
	player->AddComponent(rAnim);

	gameObject->AddGameObject(player);
}

void Map::Update()
{
}

void Map::LateUpdate() { }

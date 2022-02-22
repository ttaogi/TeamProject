#pragma once

#include "DesignPattern/ComponentBase/Component/Behaviour/MonoBehaviour/MonoBehaviour.h"

class Map : public MonoBehaviour {
private:
	float initTime;
	float timeCount;
	float turnInterval;
	MapInfo* mapInfo;
	GameObject* player;
	std::vector<GameObject*> enemyVec;
	std::vector<GameObject*> objectVec;
	std::vector<GameObject*> effectVec;

	void Init() override { }
public:
	Map();
	~Map();

	void Operation() override;
	void Init(MAP_ID _mapId);
	void Update() override;
	void LateUpdate() override;
};
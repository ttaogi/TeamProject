#pragma once

#include "GameNode.h"

class Object;
class Player;
class Slime;

class LobbyScene : public GameNode
{
private:
	MapInfo* mapInfo;
	Player* player;
	Slime* slime;
	std::vector<Object*> objectVec;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	LobbyScene() {}
	~LobbyScene() {}
};
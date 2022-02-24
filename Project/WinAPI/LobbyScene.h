#pragma once
#include "GameNode.h"

class Player;
class Object;

class LobbyScene : public GameNode
{
private:
	MapInfo* mapInfo;
	Player* player;
	std::vector<Object*> objectVec;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	LobbyScene() {}
	~LobbyScene() {}
};
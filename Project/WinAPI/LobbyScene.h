#pragma once
#include "GameNode.h"

class Player;
class Slime;

class LobbyScene : public GameNode
{
private:
	MapInfo* mapInfo;
	Player* player;
	Slime* slime;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	LobbyScene() {}
	~LobbyScene() {}
};
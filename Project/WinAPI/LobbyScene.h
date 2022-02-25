#pragma once
#include "GameNode.h"

#include "GameUI.h"

class Player;

class LobbyScene : public GameNode
{
private:
	MapInfo* mapInfo;
	Player* player;

	PlEquip* _plEquip;
	PlGold* _plGold;
	PlHp* _plHp;
	RhythmNote* _Note;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	LobbyScene() {}
	~LobbyScene() {}
};
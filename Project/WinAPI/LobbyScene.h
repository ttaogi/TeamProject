#pragma once

#include "Scene.h"

#include "GameUI.h"

class Player;
class Shopkeeper;

class LobbyScene : public Scene
{
private:
	PlEquip* _plEquip;
	PlGold* _plGold;
	PlHp* _plHp;
	RhythmNote* _Note;
	Shopkeeper* shopkeeper;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	LobbyScene() {}
	virtual ~LobbyScene() {}
};
#pragma once

#include "Scene.h"

#include "GameUI.h"

class Player;
class Slime;
class SlimeBlue;

class LobbyScene : public Scene
{
private:
	Slime* slime;
	SlimeBlue* slimeBlue;

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
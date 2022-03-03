#pragma once

#include "Scene.h"

#include "GameUI.h"

class Player;
class Slime;
class SlimeBlue;
class Skeleton;
class Bat;
class Necrodancer;

class LobbyScene : public Scene
{
private:
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
	virtual ~LobbyScene() {}
};
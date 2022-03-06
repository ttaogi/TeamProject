#pragma once

#include "Scene.h"

class PlEquip;
class PlGold;
class PlHp;
class RhythmNote;

class BossScene : public Scene
{
private:
	PlEquip* _plEquip;
	PlGold* _plGold;
	PlHp* _plHp;
	RhythmNote* _Note;
	RECT upBarRect;
	RECT necOpenRect;
	RECT downBarRect;

	float turnCount;
	float turnCount1;
	float turnCount2;
	float turnCount3;
	bool turnCount1TF;
	bool turnCount2TF;
	bool turnCount3TF;
	bool upBarTF;
	bool bossBarTF;
	bool bottomBarTF;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	BossScene() {}
	virtual ~BossScene() {}
};
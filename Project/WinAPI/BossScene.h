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
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	BossScene() {}
	virtual ~BossScene() {}
};
#pragma once

#include "GameNode.h"

class Animator;
class Scene;

class Player : public GameNode
{
private:
	float initTime;
	float turnCount;
	float turnInterval;

	DIRECTION command;
	DIRECTION bounce;
	
	Animator* headAnimator;
	Animator* bodyAnimator;
	Animator* bodyArmorAnimator;
	Animator* atk_animator_Dagger;
	Animator* atk_animator_Broadsword;

	RECT rc;
	Scene* scene;
	Image* minimapStripe;
	
	int effectCountIndex;
	
	HRESULT init(void) { return S_OK; }

public:
	HRESULT init(Scene* scenePtr);
	void release(void);
	void update(void);
	void render(void);
	void renderMinimap(HDC _hdc);

	void Move(POINT _pos);

	void setBounce(DIRECTION dir);

	RECT getRect(void) { return rc; }

	Player() { }
	virtual ~Player() { }
};
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
	RECT rc;
	Animator* headAnimator;
	Animator* bodyAnimator;
	Animator* attakAnimator;
	Scene* scene;
	
	int effectCountIndex;
	bool DaggerEffectRightTF;
	HRESULT init(void) { return S_OK; }
public:
	HRESULT init(Scene* scenePtr);
	void release(void);
	void update(void);
	void render(void);

	void Move(POINT _pos);

	void setBounce(DIRECTION dir);

	POINT getPosition(void) { return PointMake((int)pos.x, (int)pos.y); }
	RECT getRect(void) { return rc; }

	Player() { }
	virtual ~Player() { }
};
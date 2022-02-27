#pragma once

#include "GameNode.h"

class Animator;
class Scene;

class Player : public GameNode
{
private:
	int hp;
	float initTime;
	float turnCount;
	float turnInterval;
	DIRECTION command;
	RECT rc;
	Animator* headAnimator;
	Animator* bodyAnimator;
	Animator* attakAnimator;
	Scene* scene;

	HRESULT init(void) { return S_OK; }
public:
	HRESULT init(Scene* scenePtr);
	void release(void);
	void update(void);
	void render(void);

	void Move(POINT _pos);

	Player() { }
	~Player() { }
};
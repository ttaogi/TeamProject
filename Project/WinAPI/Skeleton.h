#pragma once
#include "Enemy.h"
#include "Animator.h"

class Skeleton : public Enemy
{
private:
	float turnCount;

	Animator* SkeletonAnimator;
	Animator* SkeletonAttakAnimator;
	Animator* SkeletonMoveAnimator;

	RECT rc;
public:
	HRESULT init(void);
	HRESULT init(const char * imageName, POINT position);
	void release(void);
	void update(void);
	void render(void);

	void move(void);

	Skeleton();
	~Skeleton() {};
};


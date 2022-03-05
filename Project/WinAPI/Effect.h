#pragma once

#include "Object.h"

class IceBlast : public Object
{
public:
	HRESULT init(Scene* scenePtr, POINT position);
	void release(void);
	void update(void);
	void render(void);

	bool interact(Player* player);

	IceBlast();
	virtual ~IceBlast();
};

class Explosion55 : public Object
{
public:
	HRESULT init(Scene* scenePtr, POINT position);
	void release(void);
	void update(void);
	void render(void);

	bool interact(Player* player);

	Explosion55();
	virtual ~Explosion55();
};

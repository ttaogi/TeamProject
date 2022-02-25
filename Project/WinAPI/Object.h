#pragma once

#include "GameNode.h"

class Animator;
class Player;

class Object : public GameNode
{
protected:
	bool destroyed;
	OBJECT_TYPE type;
	Animator* animator;
public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	OBJECT_TYPE getType() const { return type; }
	bool getDestroyed() const { return destroyed; }

	// return bool means moving is possible.
	virtual bool interact(Player* player) = 0;

	Object() { }
	virtual ~Object() { }
};
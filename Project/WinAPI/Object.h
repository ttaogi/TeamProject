#pragma once

#include "GameNode.h"

class Animator;

class Object : public GameNode
{
protected:
	OBJECT_TYPE type;
	Animator* animator;
public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	OBJECT_TYPE getType() const { return type; }

	Object() { }
	virtual ~Object() { }
};
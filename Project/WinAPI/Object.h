#pragma once

#include "GameNode.h"

class Animator;
class Player;
class Scene;

class Object : public GameNode
{
protected:
	bool destroyed;
	OBJECT_TYPE type;
	Animator* animator;
	Scene* scene;

	HRESULT init(void) { return S_OK; }
	HRESULT init(bool managerInit) { return S_OK; }
public:
	virtual HRESULT init(Scene* scenePtr, POINT position) = 0;
	virtual void release(void) = 0;
	virtual void update(void) = 0;
	virtual void render(void) = 0;

	OBJECT_TYPE getType() const { return type; }
	bool getDestroyed() const { return destroyed; }
	void setDestroyed(bool _destroyed) { destroyed = _destroyed; }

	// returned bool means moving is possible or not.
	virtual bool interact(Player* player) = 0;

	Object() { }
	virtual ~Object() { }
};
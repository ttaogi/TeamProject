#pragma once

#include "DesignPattern/ComponentBase/Component/component.h"
#include "StateMachine/PlayerStateMachine/PlayerStateMachine.h"

class Player : public Component
{
private:
	int hp;
	POINT pos;
public:
	Player();
	~Player();

	void Operation() override {};

	void Init();
	void Update();
	void LateUpdate();

	void SetPos(POINT _pos) { pos = _pos; }
};
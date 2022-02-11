#pragma once

#include "DesignPattern/ComponentBase/Component/Behaviour/MonoBehaviour/MonoBehaviour.h"
#include "StateMachine/PlayerStateMachine/PlayerStateMachine.h"

class Player : public MonoBehaviour {
private:
	int hp;
public:
	Player();
	~Player();

	void Init();
	void Update(HWND _hWnd);
	void LateUpdate();
};
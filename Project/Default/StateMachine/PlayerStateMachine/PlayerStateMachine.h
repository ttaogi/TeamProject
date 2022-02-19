#pragma once

#include "StateMachine/StateMachine.h"

class PlayerStateMachine : public StateMachine
{
public:
	PlayerStateMachine();
	~PlayerStateMachine();

	void SetState(MonoBehaviour* _mb, CHARACTER_STATE _state);
	void SetCallBack_v_CB_pMb(std::function<void(MonoBehaviour*)> _callBack);

	void Update(MonoBehaviour* _mb, Scene* _scene);
};
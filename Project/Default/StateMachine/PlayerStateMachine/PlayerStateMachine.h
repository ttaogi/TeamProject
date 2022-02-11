#pragma once

#include "../StateMachine.h"

class PlayerStateMachine : public StateMachine {
private:
public:
	PlayerStateMachine();
	~PlayerStateMachine();

	void Update(MonoBehaviour* _mb, SceneManager* _scnMgr);

	void SetState(MonoBehaviour* _mb, CHARACTER_STATE _state);
	void SetCallBack_v_CB_pMb(std::function<void(MonoBehaviour*)> _callBack);
};
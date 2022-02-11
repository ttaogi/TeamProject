#pragma once

#include <functional>

#include "../Image/Animator/Animator.h"

class MonoBehaviour;
class SceneManager;

class StateMachine {
protected:
	std::function<void(MonoBehaviour*)> callBack;
	CHARACTER_STATE curState;
public:
	StateMachine() { curState = CHARACTER_STATE::IDLE; callBack = NULL; }

	virtual void Update(MonoBehaviour* _mb, SceneManager* _scnMgr) = 0;

	CHARACTER_STATE GetState() const { return curState; }
	virtual void SetState(MonoBehaviour* _mb, CHARACTER_STATE _state) = 0;
	virtual void SetCallBack_v_CB_pMb(std::function<void(MonoBehaviour*)> _callBack) = 0;
};
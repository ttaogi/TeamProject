#pragma once

#include <functional>

#include "Image/Animator/Animator.h"

class MonoBehaviour;
class Scene;

class StateMachine
{
protected:
	std::function<void(MonoBehaviour*)> callBack;
	CHARACTER_STATE curState;
public:
	StateMachine() { curState = CHARACTER_STATE::IDLE; callBack = NULL; }

	CHARACTER_STATE GetState() const { return curState; }
	virtual void SetState(MonoBehaviour* _mb, CHARACTER_STATE _state) = 0;
	virtual void SetCallBack_v_CB_pMb(std::function<void(MonoBehaviour*)> _callBack) = 0;

	virtual void Update(MonoBehaviour* _mb, Scene* _scnMgr) = 0;
};
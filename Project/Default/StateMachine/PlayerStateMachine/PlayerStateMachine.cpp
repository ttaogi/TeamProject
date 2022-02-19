#include "Stdafx/stdafx.h"

#include "DesignPattern/ComponentBase/Component/Button/Button.h"
#include "Scene/OnGameScene/OnGameScene.h"
#include "Player/Player.h"
#include "PlayerStateMachine.h"

PlayerStateMachine::PlayerStateMachine() : StateMachine() { }

PlayerStateMachine::~PlayerStateMachine() { }

void PlayerStateMachine::SetState(MonoBehaviour* _mb, CHARACTER_STATE _state)
{
	//_mb->GetAnimator()->ChangeAnimation(_state);
	curState = _state;
}

void PlayerStateMachine::SetCallBack_v_CB_pMb(std::function<void(MonoBehaviour*)> _callBack)
{
	callBack = std::move(_callBack);
}

void PlayerStateMachine::Update(MonoBehaviour* _mb, Scene* _scene)
{
	Player* player = (Player*)_mb;
	OnGameScene* scene = (OnGameScene*)_scene;

	//player->Move();

	//if (player->GetAnimator() != NULL) {
	//	switch (curState) {
	//	case CHARACTER_STATE::IDLE:
	//		if(KEY->IsOnceKeyDown(0x41)) { // 'A'
	//			player->GetAnimator()->ChangeAnimation(CHARACTER_STATE::ATTACK);
	//			curState = CHARACTER_STATE::ATTACK;
	//			if(callBack != NULL) {
	//				Attack* atk = new Attack();
	//				atk->SetPos(POINT{ player->GetPos().x + 100, player->GetPos().y + 4 });
	//				atk->SetRect(MakeRectCWH(atk->GetPos(), 100, 20));
	//				atk->SetIsLeft(false);
	//				atk->SetByPlayer(true);
	//				atk->SetCallBack_v_CB_pMb(callBack);
	//				atk->Init();
	//				callBack(atk);
	//			}
	//			break;
	//		}
	//		if (KEY->IsOnceKeyDown(0x44)) { // 'D'
	//			player->GetAnimator()->ChangeAnimation(CHARACTER_STATE::DEFFENCE);
	//			curState = CHARACTER_STATE::DEFFENCE;
	//			break;
	//		}
	//		break;
	//	case CHARACTER_STATE::ATTACK:
	//		if (player->GetAnimator()->IsEnd()) {
	//			player->GetAnimator()->ChangeAnimation(CHARACTER_STATE::IDLE);
	//			curState = CHARACTER_STATE::IDLE;
	//			break;
	//		}
	//		break;
	//	case CHARACTER_STATE::ATTACKED:
	//		if (player->GetAnimator()->IsEnd()) {
	//			player->GetAnimator()->ChangeAnimation(CHARACTER_STATE::IDLE);
	//			curState = CHARACTER_STATE::IDLE;
	//			break;
	//		}
	//		break;
	//	case CHARACTER_STATE::DEFFENCE:
	//		if (!KEY->IsStayKeyDown(0x44)) {
	//			player->GetAnimator()->ChangeAnimation(CHARACTER_STATE::IDLE);
	//			curState = CHARACTER_STATE::IDLE;
	//			break;
	//		}
	//		break;
	//	}
	//}
}

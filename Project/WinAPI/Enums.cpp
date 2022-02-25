#include "Stdafx.h"

#include "Enums.h"

string CharacterStateToWString(CHARACTER_STATE _state)
{
	switch (_state)
	{
	case CHARACTER_STATE::IDLE_RIGHT:
		return "IDLE_RIGHT";
	case CHARACTER_STATE::IDLE_LEFT:
		return "IDLE_LEFT";
	case CHARACTER_STATE::JUMP_RIGHT:
		return "JUMP_RIGHT";
	case CHARACTER_STATE::JUMP_LEFT:
		return "JUMP_LEFT";
	case CHARACTER_STATE::JUMP_TOP:
		return "JUMP_TOP";
	case CHARACTER_STATE::JUMP_BOTTOM:
		return "JUMP_BOTTOM";
	case CHARACTER_STATE::ATTACK:
		return "ATTACK";
	case CHARACTER_STATE::ATTACKED:
		return "ATTACKED";
	default:
		return "CHARACTER_STATE_NUM";
	}
}

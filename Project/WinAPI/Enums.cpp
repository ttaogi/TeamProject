#include "Stdafx.h"

#include "Enums.h"

string CharacterStateToWString(CHARACTER_STATE _state)
{
	switch (_state)
	{
	case CHARACTER_STATE::IDLE:
		return "IDLE";
	case CHARACTER_STATE::ATTACK:
		return "ATTACK";
	case CHARACTER_STATE::ATTACKED:
		return "ATTACKED";
	case CHARACTER_STATE::MOVE:
		return "DEFFENCE";
	default:
		return "CHARACTER_STATE_NUM";
	}
}

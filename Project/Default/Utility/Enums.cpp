#include "Stdafx/stdafx.h"

#include "Enums.h"

wstring StateToWString(CHARACTER_STATE _state) {
	switch (_state) {
	case CHARACTER_STATE::IDLE:
		return L"IDLE";
	case CHARACTER_STATE::ATTACK:
		return L"ATTACK";
	case CHARACTER_STATE::ATTACKED:
		return L"ATTACKED";
	case CHARACTER_STATE::DEFFENCE:
		return L"DEFFENCE";
	default:
		return L"CHARACTER_STATE_NUM";
	}
}

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

std::string MapIdToKeyString(MAP_ID id)
{
	switch (id)
	{
	case MAP_ID::EXAMPLE_MAP:
		return XML_DOC_EXAMPLE_MAP;
	default:
		return "";
	}
}

std::string SoundIdToKeyString(SOUND_ID id)
{
	switch (id)
	{
	case SOUND_ID::BGM_INTRO:
		return KEY_BGM_INTRO;
	case SOUND_ID::BGM_LOBBY:
		return KEY_BGM_LOBBY;
	case SOUND_ID::BGM_MAIN_MENU:
		return KEY_BGM_MAIN_MENU;
	default:
		return "";
	}
}

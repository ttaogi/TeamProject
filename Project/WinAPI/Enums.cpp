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
	case CHARACTER_STATE::ATTACK_LEFT:
		return "ATTACK_LEFT";
	case CHARACTER_STATE::ATTACK_RIGHT:
		return "ATTACK_RIGHT";
	case CHARACTER_STATE::ATTACK_TOP:
		return "ATTACK_TOP";
	case CHARACTER_STATE::ATTACK_BOTTOM:
		return "ATTACK_BOTTOM";
	case CHARACTER_STATE::RIGHT_UP_JUMP:
		return "RIGHT_UP_JUMP";
	case CHARACTER_STATE::RIGHT_DOWN_JUMP:
		return "RIGHT_DOWN_JUMP";
	case CHARACTER_STATE::LEFT_UP_JUMP:
		return "LEFT_UP_JUMP";
	case CHARACTER_STATE::LEFT_DOWN_JUMP:
		return "LEFT_DOWN_JUMP";
	case CHARACTER_STATE::RIGHT_BLUEATT:
		return "RIGHT_BLUEATT";
	case CHARACTER_STATE::LEFT_BLUEATT:
		return "LEFT_BLUEATT";
	case CHARACTER_STATE::EXPLOSION_IDLE:
		return "EXPLOSION_IDLE";
	case CHARACTER_STATE::EXPLOSION:
		return "EXPLOSION";
	case CHARACTER_STATE::SOHWAN_IDLE:
		return "SOHWAN_IDLE";
	case CHARACTER_STATE::IDLE2:
		return "IDLE2";
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
	case MAP_ID::DUGEON_MAP:
		return XML_DOC_DUGEON_MAP;
	case MAP_ID::BOSS_MAP:
		return XML_DOC_BOSS_MAP;
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
	case SOUND_ID::BGM_ZONE_1_1:
		return KEY_BGM_ZONE_1_1;
	case SOUND_ID::BGM_NECRODANCER:
		return KEY_BGM_BOSS_NECRODANCER;
	default:
		return "";
	}
}

std::string ItemDetailToIconKeyString(ITEM_DETAIL type)
{
	switch (type)
	{
	case ITEM_DETAIL::SHOVEL:
		return KEY_ITEM_SHOVEL;
	case ITEM_DETAIL::ATTACK_DAGGER:
		return KEY_ITEM_DAGGER;
	case ITEM_DETAIL::ATTACK_BROADSWORD:
		return KEY_ITEM_BROADSWORD;
	case ITEM_DETAIL::BODY:
		return KEY_ITEM_BODY;
	case ITEM_DETAIL::HEAD:
		return KEY_ITEM_HEAD;
	case ITEM_DETAIL::TORCH:
		return KEY_ITEM_TORCH;
	case ITEM_DETAIL::HEAL_APPLE:
		return KEY_ITEM_APPLE;
	case ITEM_DETAIL::BOMB:
		return KEY_ITEM_BOMB;
	case ITEM_DETAIL::ATTACK_GOLDENLUTE:
		return KEY_ITEM_GOLDENLUTE;
	default:
		return "";
	}
}

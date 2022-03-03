#pragma once

enum class CHARACTER_STATE
{
	IDLE_RIGHT = 0, IDLE_LEFT,
	JUMP_RIGHT, JUMP_LEFT,
	JUMP_TOP, JUMP_BOTTOM,
	ATTACK, ATTACKED,
	RIGHT_UP_JUMP, RIGHT_DOWN_JUMP,
	LEFT_UP_JUMP, LEFT_DOWN_JUMP,
	RIGHT_BLUEATT, LEFT_BLUEATT,
	EXPLOSION_IDLE, EXPLOSION,
	SOHWAN_IDLE, IDLE2,
	CHARACTER_STATE_NUM
};

std::string CharacterStateToWString(CHARACTER_STATE _state);

enum class DIRECTION
{
	LEFT = 0, TOP, RIGHT, BOTTOM,
	LEFT_TOP, LEFT_BOTTOM, RIGHT_TOP, RIGHT_BOTTOM,
	DIRECTION_NUM
};

enum class TILE_TYPE
{
	EMPTY = 0,
	DIRT,
	TILE_TYPE_NUM
};

enum class OBJECT_TYPE
{
	NONE = 0,
	WALL_UNBREAKABLE,
	WALL_DIRT,
	WALL_SHOP,
	MONSTER_SLIME,
	MONSTER_SLIME_BLUE,
	MONSTER_SKELETON,
	MONSTER_BAT,
	MONSTER_NECRODANCER,
	STEPPING_STONE_LEFT,
	STEPPING_STONE_TOP,
	STEPPING_STONE_RIGHT,
	STEPPING_STONE_BOTTOM,
	ITEM_MONEY,
	ITEM_HEAL_APPLE,
	ITEM_BOMB,
	EUIP_HEAD,
	EUIP_BOBY,
	EUIP_ATTACK_DAGGER,
	EUIP_ATTACK_BROADSWORD,
	EUIP_TORCH,
	EUIP_ATTACK_GOLDENLUTE,
	STAIR,
	OBJECT_TYPE_NUM
};

enum class MAP_ID
{
	EXAMPLE_MAP = 0,
	DUGEON_MAP, BOSS_MAP,
	MAP_ID_NUM
};

std::string MapIdToKeyString(MAP_ID id);

enum class SOUND_ID
{
	BGM_INTRO = 0, BGM_LOBBY, BGM_MAIN_MENU,
	SOUND_ID_NUM
};

std::string SoundIdToKeyString(SOUND_ID id);

enum class ITEM_TYPE
{
	SHOVEL = 0, ATTACK, BODY, HEAD, TORCH,
	HEAL, BOMB,
	ITEM_TYPE_NUM
};

enum class ITEM_DETAIL
{
	SHOVEL = 0,
	ATTACK_DAGGER, ATTACK_BROADSWORD,
	BODY, HEAD,
	TORCH, HEAL_APPLE,
	BOMB, ATTACK_GOLDENLUTE,
	ITEM_DETAIL_NUM
};

std::string ItemDetailToIconKeyString(ITEM_DETAIL type);

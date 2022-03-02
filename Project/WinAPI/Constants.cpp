#include "Stdafx.h"

#include "Constants.h"

#pragma region Stripe
#pragma region Background
const std::string KEY_BACKGROUND_START_SCENE =
	"BACKGROUND_START_SCENE";
const char* DIR_BACKGROUND_START_SCENE =
	"Resources/Images/mainmenu/mainmenu.bmp";
#pragma endregion Background

#pragma region Tile
const std::string KEY_TILE_DIRT =
	"TILE_DIRT";
const char* DIR_TILE_DIRT =
	"Resources/Images/Object/TILE/DIRT/dirt.bmp";
#pragma endregion Tile

#pragma region Wall
const std::string KEY_WALL_UNBREAKABLE =
	"WALL_UNBREAKABLE";
const char* DIR_WALL_UNBREAKABLE =
	"Resources/Images/level/TEMP_wall_unbreakable.bmp";
const std::string KEY_WALL_DIRT =
	"WALL_DIRT";
const char* DIR_WALL_DIRT =
	"Resources/Images/level/wall_dirt_crypt.bmp";
const std::string KEY_WALL_SHOP =
	"WALL_SHOP";
const char* DIR_WALL_SHOP =
	"Resources/Images/level/wall_shop_crypt.bmp";
#pragma endregion Wall

#pragma region SteppingStone
const std::string KEY_STEPPING_STONE_LEFT =
	"STEPPING_STONE_LEFT";
const char* DIR_STEPPING_STONE_LEFT =
	"Resources/Images/traps/steppingStoneLeft.bmp";
const std::string KEY_STEPPING_STONE_TOP =
	"STEPPING_STONE_TOP";
const char* DIR_STEPPING_STONE_TOP =
	"Resources/Images/traps/steppingStoneTop.bmp";
const std::string KEY_STEPPING_STONE_RIGHT =
	"STEPPING_STONE_RIGHT";
const char* DIR_STEPPING_STONE_RIGHT =
	"Resources/Images/traps/steppingStoneRight.bmp";
const std::string KEY_STEPPING_STONE_BOTTOM =
	"STEPPING_STONE_BOTTOM";
const char* DIR_STEPPING_STONE_BOTTOM =
	"Resources/Images/traps/steppingStoneBottom.bmp";
#pragma endregion SteppingStone

#pragma region UI
const std::string KEY_UI_PRESS_ANY_KEY =
	"PRESS_ANY_KEY";
const char* DIR_UI_PRESS_ANY_KEY =
	"Resources/Images/mainmenu/continue.bmp";

const std::string KEY_UI_SLOT_1 =
	"UI_SLOT_1";
const char* DIR_UI_SLOT_1 =
	"Resources/Images/gui/hud_slot_1.bmp";
const std::string KEY_UI_SLOT_2 =
	"UI_SLOT_2";
const char* DIR_UI_SLOT_2 =
	"Resources/Images/gui/hud_slot_2.bmp";
const std::string KEY_UI_SLOT_3 =
	"UI_SLOT_3";
const char* DIR_UI_SLOT_3 =
	"Resources/Images/gui/hud_slot_3.bmp";
const std::string KEY_UI_SLOT_4 =
	"UI_SLOT_4";
const char* DIR_UI_SLOT_4 =
	"Resources/Images/gui/hud_slot_4.bmp";
const std::string KEY_UI_SLOT_5 =
	"UI_SLOT_5";
const char* DIR_UI_SLOT_5 =
	"Resources/Images/gui/hud_slot_7.bmp";
const std::string KEY_UI_ACTION_1 =
	"UI_ACTION_1";
const char* DIR_UI_ACTION_1 =
	"Resources/Images/gui/hud_slot_action1.bmp";
const std::string KEY_UI_ACTION_2 =
	"UI_ACTION_2";
const char* DIR_UI_ACTION_2 =
	"Resources/Images/gui/hud_slot_bomb.bmp";

const std::string KEY_UI_FULLHP =
	"UI_FULLHP";
const char* DIR_UI_FULLHP =
	"Resources/Images/gui/heart.bmp";
const std::string KEY_UI_HALFHP =
	"UI_HALFHP";
const char* DIR_UI_HALFHP =
	"Resources/Images/gui/heart_half.bmp";
const std::string KEY_UI_EMPTYHP =
	"UI_EMPTYHP";
const char* DIR_UI_EMPTYHP =
	"Resources/Images/gui/heart_empty.bmp";

const std::string KEY_UI_HEART =
	"UI_HEART";
const char* DIR_UI_HEART =
	"Resources/Images/gui/TEMP_beat_heart.bmp";
const std::string KEY_UI_NOTE_GREEN =
	"UI_NOTE_GREEN";
const char* DIR_UI_NOTE_GREEN =
	"Resources/Images/gui/TEMP_beat_marker.bmp";
const std::string KEY_UI_NOTE_RED =
	"UI_NOTE_RED";
const char* DIR_UI_NOTE_RED =
	"Resources/Images/gui/TEMP_beat_marker_red.bmp";

const std::string KEY_UI_GOLD =
	"UI_GOLD";
const char* DIR_UI_GOLD =
	"Resources/Images/gui/hud_coins.bmp";

const std::string KEY_UI_MONSTER_HEART_EMPTY = 
	"UI_MONSTER_HEART_EMPTY";
const char* DIR_UI_MONSTER_HEART_EMPTY =
	"Resources/Images/gui/TEMP_heart_empty_small.bmp";

const std::string KEY_UI_MONSTER_HEART_FULL =
	"UI_MONSTER_HEART_FULL";
const char* DIR_UI_MONSTER_HEART_FULL =
	"Resources/Image/gui/TEMP_heart_small.bmp";

#pragma endregion UI

#pragma region Player
const std::string KEY_PLAYER_HEAD_IDLE_RIGHT =
	"PLAYER_HEAD_IDLE_RIGHT";
const char* DIR_PLAYER_HEAD_IDLE_RIGHT =
	"Resources/Images/entities/player1_heads_idle_right.bmp";
const std::string KEY_PLAYER_BODY_IDLE_RIGHT =
	"PLAYER_BODY_IDLE_RIGHT";
const char* DIR_PLAYER_BODY_IDLE_RIGHT =
	"Resources/Images/entities/player1_armor_body_xmas_idle_right.bmp";

const std::string KEY_PLAYER_HEAD_IDLE_LEFT =
	"PLAYER_HEAD_IDLE_LEFT";
const char* DIR_PLAYER_HEAD_IDLE_LEFT =
	"Resources/Images/entities/player1_heads_idle_left.bmp";
const std::string KEY_PLAYER_BODY_IDLE_LEFT =
	"PLAYER_BODY_IDLE_LEFT";
const char* DIR_PLAYER_BODY_IDLE_LEFT =
	"Resources/Images/entities/player1_armor_body_xmas_idle_left.bmp";

const std::string KEY_PLAYER_HEAD_JUMP_RIGHT =
	"PLAYER_HEAD_JUMP_RIGHT";
const char* DIR_PLAYER_HEAD_JUMP_RIGHT =
	"Resources/Images/entities/player1_heads_jump_right.bmp";
const std::string KEY_PLAYER_BODY_JUMP_RIGHT =
	"PLAYER_BODY_JUMP_RIGHT";
const char* DIR_PLAYER_BODY_JUMP_RIGHT =
	"Resources/Images/entities/player1_armor_body_xmas_jump_right.bmp";

const std::string KEY_PLAYER_HEAD_JUMP_LEFT =
	"PLAYER_HEAD_JUMP_LEFT";
const char* DIR_PLAYER_HEAD_JUMP_LEFT =
	"Resources/Images/entities/player1_heads_jump_left.bmp";
const std::string KEY_PLAYER_BODY_JUMP_LEFT =
	"PLAYER_BODY_JUMP_LEFT";
const char* DIR_PLAYER_BODY_JUMP_LEFT =
	"Resources/Images/entities/player1_armor_body_xmas_jump_left.bmp";

const std::string KEY_PLAYER_HEAD_JUMP_TOP =
	"PLAYER_HEAD_JUMP_TOP";
const char* DIR_PLAYER_HEAD_JUMP_TOP =
	"Resources/Images/entities/player1_heads_jump_top.bmp";
const std::string KEY_PLAYER_BODY_JUMP_TOP =
	"PLAYER_BODY_JUMP_TOP";
const char* DIR_PLAYER_BODY_JUMP_TOP =
	"Resources/Images/entities/player1_armor_body_xmas_jump_top.bmp";

const std::string KEY_PLAYER_HEAD_JUMP_BOTTOM =
	"PLAYER_HEAD_JUMP_BOTTOM";
const char* DIR_PLAYER_HEAD_JUMP_BOTTOM =
	"Resources/Images/entities/player1_heads_jump_bottom.bmp";
const std::string KEY_PLAYER_BODY_JUMP_BOTTOM =
	"PLAYER_BODY_JUMP_BOTTOM";
const char* DIR_PLAYER_BODY_JUMP_BOTTOM =
	"Resources/Images/entities/player1_armor_body_xmas_jump_bottom.bmp";
#pragma endregion Player

#pragma region Slime
const std::string KEY_SLIME =
	"SLIME";
const char* DIR_SLIME =
	"Resources/Images/entities/slime_green.bmp";
const std::string KEY_SLIME_JUMP =
	"SLIME_JUMP";
const char* DIR_SLIME_JUMP =
	"Resources/Images/entities/slime_green_jump.bmp";
#pragma endregion Slime

#pragma region SlimeBlue
const std::string KEY_SLIME_BLUE =
	"SLIME_BLUE";
const char* DIR_SLIME_BLUE =
	"Resources/Images/entities/slime_ice.bmp";
const std::string KEY_SLIME_BLUE_JUMP =
	"SLIME_BLUE_JUMP";
const char* DIR_SLIME_BLUE_JUMP =
	"Resources/Images/entities/slime_ice_jump.bmp";
const std::string KEY_SLIME_BLUE_JUMP_TOP =
	"SLIME_BLUE_JUMP_TOP";
const char* DIR_SLIME_BLUE_JUMP_TOP =
	"Resources/Images/entities/slime_ice_jump_top.bmp";
const std::string KEY_SLIME_BLUE_JUMP_BOTTOM =
	"SLIME_BLUE_JUMP_BOTTOM";
const char* DIR_SLIME_BLUE_JUMP_BOTTOM =
	"Resources/Images/entities/slime_ice_jump_bottom.bmp";
#pragma endregion SlimeBlue

#pragma region Skeleton
const std::string KEY_SKELETON_LEFT =
	"SKELETON_LEFT";
const char* DIR_SKELETON_LEFT =
	"Resources/Images/entities/skeleton_left.bmp";
const std::string KEY_SKELETON_RIGHT =
	"SKELETON_RIGHT";
const char* DIR_SKELETON_RIGHT =
	"Resources/Images/entities/skeleton_right.bmp";
#pragma endregion Skeleton

#pragma region bat
const std::string KEY_BAT_LEFT =
	"BAT_LEFT";
const char* DIR_BAT_LEFT =
	"Resources/Images/entities/bat_miniboss_left.bmp";
const std::string KEY_BAT_RIGHT =
	"BAT_RIGHT";
const char* DIR_BAT_RIGHT =
	"Resources/Images/entities/bat_miniboss_right.bmp";
#pragma endregion bat

#pragma region necrodancer
const std::string KEY_NECRODANCER_RIGHT_IDLE =
	"NECRODANCER_RIGHT_IDLE";
const char* DIR_NECRODANCER_RIGHT_IDLE =
	"Resources/Images/entities/necrodancer_right_idle.bmp";
const std::string KEY_NECRODANCER_RIGHT_UP_JUMP =
	"NECRODANCER_RIGHT_UP_JUMP";
const char* DIR_NECRODANCER_RIGHT_UP_JUMP =
	"Resources/Images/entities/necrodancer_right_up_jump.bmp";
const std::string KEY_NECRODANCER_RIGHT_DOWN_JUMP =
	"NECRODANCER_RIGHT_DOWN_JUMP";
const char* DIR_NECRODANCER_RIGHT_DOWN_JUMP =
	"Resources/Images/entities/necrodancer_right_down_jump.bmp";

const std::string KEY_NECRODANCER_LEFT_IDLE =
	"NECRODANCER_LEFT_IDLE";
const char* DIR_NECRODANCER_LEFT_IDLE =
	"Resources/Images/entities/necrodancer_left_idle.bmp";
const std::string KEY_NECRODANCER_LEFT_UP_JUMP =
	"NECRODANCER_LEFT_UP_JUMP";
const char* DIR_NECRODANCER_LEFT_UP_JUMP =
	"Resources/Images/entities/necrodancer_left_up_jump.bmp";
const std::string KEY_NECRODANCER_LEFT_DOWN_JUMP =
	"NECRODANCER_LEFT_DOWN_JUMP";
const char* DIR_NECRODANCER_LEFT_DOWN_JUMP =
	"Resources/Images/entities/necrodancer_left_down_jump.bmp";

const std::string KEY_NECRODANCER_EXPLOSION_IDLE =
	"NECRODANCER_EXPLOSION_IDLE";
const char* DIR_NECRODANCER_EXPLOSION_IDLE =
	"Resources/Images/entities/necrodancer_explosion_idle.bmp";
const std::string KEY_NECRODANCER_EXPLOSION =
	"NECRODANCER_EXPLOSION";
const char* DIR_NECRODANCER_EXPLOSION =
	"Resources/Images/entities/necrodancer_explosion.bmp";

const std::string KEY_NECRODANCER_RIGHT_BLUEATT =
	"NECRODANCER_RIGHT_BLUEATT";
const char* DIR_NECRODANCER_RIGHT_BLUEATT =
	"Resources/Images/entities/necrodancer_rightBlueATT.bmp";
const std::string KEY_NECRODANCER_LEFT_BLUEATT =
	"NECRODANCER_LEFT_BLUEATT";
const char* DIR_NECRODANCER_LEFT_BLUEATT =
	"Resources/Images/entities/necrodancer_leftBlueATT.bmp";

const std::string KEY_NECRODANCER_SOHWAN_IDLE =
	"NECRODANCER_SOHWAN_IDLE";
const char* DIR_NECRODANCER_SOHWAN_IDLE =
	"Resources/Images/entities/necrodancer_sohwan_idle.bmp";
const std::string KEY_NECRODANCER_IDLE2 =
	"NECRODANCER_IDLE2";
const char* DIR_NECRODANCER_IDLE2 =
	"Resources/Images/entities/necrodancer_idle2.bmp";
#pragma endregion necrodancer

#pragma region WeaponEffect
const std::string KEY_SWIPE_DAGGER_TOP =
	"SWIPE_DAGGER_TOP";
const char* DIR_SWIPE_DAGGER_TOP =
	"Resources/Images/swipes/swipe_dagger_top.bmp";
const std::string KEY_SWIPE_DAGGER_BOTTOM =
	"SWIPE_DAGGER_bottom";
const char* DIR_SWIPE_DAGGER_BOTTOM =
	"Resources/Images/swipes/swipe_dagger_bottom.bmp";
const std::string KEY_SWIPE_DAGGER_LEFT =
	"SWIPE_DAGGER_LEFT";
const char* DIR_SWIPE_DAGGER_LEFT =
	"Resources/Images/swipes/swipe_dagger_left.bmp";
const std::string KEY_SWIPE_DAGGER_RIGHT =
	"SWIPE_DAGGER_RIGHT";
const char* DIR_SWIPE_DAGGER_RIGHT =
	"Resources/Images/swipes/swipe_dagger_right.bmp";
#pragma endregion WeaponEffect

#pragma region EnemyAttackEffect
const std::string KEY_SWIPE_ENEMY_LEFT =
	"SWIPE_ENEMY_LEFT";
const char* DIR_SWIPE_ENEMY_LEFT =
	"Resources/Images/swipes/swipe_enemy_left.bmp";
const std::string KEY_SWIPE_ENEMY_RIGHT =
	"SWIPE_ENEMY_RIGHT";
const char* DIR_SWIPE_ENEMY_RIGHT =
	"Resources/Images/swipes/swipe_enemy_right.bmp";
const std::string KEY_SWIPE_ENEMY_TOP =
	"SWIPE_ENEMY_TOP";
const char* DIR_SWIPE_ENEMY_TOP =
	"Resources/Images/swipes/swipe_enemy_top.bmp";
const std::string KEY_SWIPE_ENEMY_BOTTOM =
	"SWIPE_ENEMY_BOTTOM";
const char* DIR_SWIPE_ENEMY_BOTTOM =
	"Resources/Images/swipes/swipe_enemy_bottom.bmp";
#pragma endregion EnemyAttackEffect

#pragma region Item
extern const std::string KEY_ITEM_GOLD =
	"DIR_ITEM_GOLD";
extern const char* DIR_ITEM_GOLD =
	"Resources/Images/items/resource_coin.bmp";
#pragma endregion Item
#pragma endregion Stripe

///////////////////////
///////////////////////

#pragma region Sound
const std::string KEY_BGM_INTRO =
	"BGM_INTRO";
const char* DIR_BGM_INTRO =
	"Resources/Sounds/BGM/intro.ogg";
const std::string KEY_BGM_LOBBY =
	"BGM_LOBBY";
const char* DIR_BGM_LOBBY =
	"Resources/Sounds/BGM/lobby.ogg";
const std::string KEY_BGM_MAIN_MENU =
	"BGM_MAIN_MENU";
const char* DIR_BGM_MAIN_MENU =
	"Resources/Sounds/BGM/main_menu.ogg";
#pragma endregion Sound

///////////////////////
///////////////////////

#pragma region Scene
const std::string KEY_SCENE_START =
	"START_SCENE";
const std::string KEY_SCENE_LOBBY =
	"LOBBY_SCENE";
#pragma endregion Scene

///////////////////////
///////////////////////

#pragma region XmlDocument
const std::string XML_DOC_EXAMPLE =
	"XML/example document.xml";
const std::string XML_DOC_ITEM_LIST =
	"XML/item list.xml";
const std::string XML_DOC_EXAMPLE_MAP =
	"XML/example map.xml";
#pragma endregion XmlDocument

///////////////////////
///////////////////////

#pragma region Size
const int TILE_SIZE = 48;
#pragma endregion Size


const COLORREF MAGENTA = RGB(255, 0, 255);
const float DEFAULT_FPS = 60.0f;

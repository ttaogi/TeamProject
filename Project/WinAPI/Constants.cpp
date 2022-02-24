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

#pragma region UI
const std::string KEY_UI_PRESS_ANY_KEY =
	"PRESS_ANY_KEY";
const char* DIR_UI_PRESS_ANY_KEY =
	"Resources/Images/mainmenu/continue.bmp";
#pragma endregion UI

#pragma region Player
const std::string KEY_PLAYER =
	"PLAYER";
const char* DIR_PLAYER =
	"Resources/Images/entities/player1_heads.bmp";
const std::string KEY_PLAYER2 =
	"PLAYER_TMP2";
const char* DIR_PLAYER2 =
	"Resources/Images/entities/player1_armor_body_xmas.bmp";
#pragma endregion Player

#pragma region Slime
const std::string KEY_SLIME =
	"SLIME";
const char* DIR_SLIME =
	"Resources/Images/entities/slime_green.bmp";
#pragma endregion Slime

#pragma endregion Stripe

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

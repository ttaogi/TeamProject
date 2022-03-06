﻿#include "Stdafx.h"
#include "MainGame.h"

HINSTANCE	_hInstance;
HWND		_hWnd;
POINT		_ptMouse = { 0, 0 };
LPTSTR		_lpszClass = TEXT("WindowsAPI");

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void setWindowSize(int x, int y, int width, int height);
void loadResources();
void releaseResources();

MainGame* _mg;

int APIENTRY WinMain(HINSTANCE hInstance,
					 HINSTANCE hPrevInstance,
					 LPSTR lpszCmdParam,
					 int nCmdShow)
{
	_mg = new MainGame();
	_hInstance = hInstance;

	loadResources();

	WNDCLASS wndClass;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hInstance = hInstance;
	wndClass.lpfnWndProc = (WNDPROC)WndProc;
	wndClass.lpszClassName = WINNAME;
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	
	RegisterClass(&wndClass);

	_hWnd = CreateWindow
	(
		WINNAME,
		WINNAME,
		WINSTYLE,
		WINSTARTX,
		WINSTARTY,
		WINSIZEX,
		WINSIZEY,
		NULL,
		(HMENU)NULL,
		hInstance,
		NULL
	);

	setWindowSize(WINSTARTX, WINSTARTY, WINSIZEX, WINSIZEY);
	ShowWindow(_hWnd, nCmdShow);

	if (FAILED(_mg->init()))
	{
		return 0;
	}

	MSG message;

	while (true)
	{
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
		{
			if (message.message == WM_QUIT) break;
			TranslateMessage(&message);
			DispatchMessage(&message);
		}

		else
		{
			TIMEMANAGER->update(60.0f);
			_mg->update();
			_mg->render();
		}
	}

	_mg->release();

	releaseResources();

	return (int)message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT imessage, WPARAM wParam, LPARAM lParam)
{
	return _mg->MainProc(hWnd, imessage, wParam, lParam);
}
         
void setWindowSize(int x, int y, int width, int height)
{
	RECT rc = { 0, 0, width, height };

	AdjustWindowRect(&rc, WINSTYLE, false);

	SetWindowPos(_hWnd, NULL, x, y,
		(rc.right - rc.left),
		(rc.bottom - rc.top),
		SWP_NOZORDER | SWP_NOMOVE);
}

void loadResources()
{
	setlocale(LC_ALL, "Korean");

	RND->init();
	CAMERAMANAGER->init();
	// FONTMANAGER has no init.
	IMAGEMANAGER->init();
	KEYMANAGER->init();
	SCENEMANAGER->init();
	SOUNDMANAGER->init();
	TEXTDATAMANAGER->init();
	TIMEMANAGER->init();
	XMLMANAGER->init();

	// player.
	IMAGEMANAGER->addFrameImage(KEY_PLAYER_HEAD_IDLE_RIGHT, DIR_PLAYER_HEAD_IDLE_RIGHT, 192, 96, 4, 2, 8, true, MAGENTA);
	IMAGEMANAGER->addFrameImage(KEY_PLAYER_BODY_IDLE_RIGHT, DIR_PLAYER_BODY_IDLE_RIGHT, 192, 28, 4, 1, 4, true, MAGENTA);
	IMAGEMANAGER->addFrameImage(KEY_PLAYER_ARMOR_IDLE_RIGHT, DIR_PLAYER_ARMOR_IDLE_RIGHT, 192, 28, 4, 1, 4, true, MAGENTA);

	IMAGEMANAGER->addFrameImage(KEY_PLAYER_HEAD_IDLE_LEFT, DIR_PLAYER_HEAD_IDLE_LEFT, 192, 96, 4, 2, 8, true, MAGENTA);
	IMAGEMANAGER->addFrameImage(KEY_PLAYER_BODY_IDLE_LEFT, DIR_PLAYER_BODY_IDLE_LEFT, 192, 28, 4, 1, 4, true, MAGENTA);
	IMAGEMANAGER->addFrameImage(KEY_PLAYER_ARMOR_IDLE_LEFT, DIR_PLAYER_ARMOR_IDLE_LEFT, 192, 28, 4, 1, 4, true, MAGENTA);

	IMAGEMANAGER->addFrameImage(KEY_PLAYER_HEAD_JUMP_RIGHT, DIR_PLAYER_HEAD_JUMP_RIGHT, 384, 144, 4, 2, 8, true, MAGENTA);
	IMAGEMANAGER->addFrameImage(KEY_PLAYER_BODY_JUMP_RIGHT, DIR_PLAYER_BODY_JUMP_RIGHT, 384, 104, 4, 2, 8, true, MAGENTA);
	IMAGEMANAGER->addFrameImage(KEY_PLAYER_ARMOR_JUMP_RIGHT, DIR_PLAYER_ARMOR_JUMP_RIGHT, 384, 104, 4, 2, 8, true, MAGENTA);

	IMAGEMANAGER->addFrameImage(KEY_PLAYER_HEAD_JUMP_LEFT, DIR_PLAYER_HEAD_JUMP_LEFT, 384, 144, 4, 2, 8, true, MAGENTA);
	IMAGEMANAGER->addFrameImage(KEY_PLAYER_BODY_JUMP_LEFT, DIR_PLAYER_BODY_JUMP_LEFT, 384, 104, 4, 2, 8, true, MAGENTA);
	IMAGEMANAGER->addFrameImage(KEY_PLAYER_ARMOR_JUMP_LEFT, DIR_PLAYER_ARMOR_JUMP_LEFT, 384, 104, 4, 2, 8, true, MAGENTA);

	IMAGEMANAGER->addFrameImage(KEY_PLAYER_HEAD_JUMP_TOP, DIR_PLAYER_HEAD_JUMP_TOP, 192, 192, 4, 2, 8, true, MAGENTA);
	IMAGEMANAGER->addFrameImage(KEY_PLAYER_BODY_JUMP_TOP, DIR_PLAYER_BODY_JUMP_TOP, 192, 152, 4, 2, 8, true, MAGENTA);
	IMAGEMANAGER->addFrameImage(KEY_PLAYER_ARMOR_JUMP_TOP, DIR_PLAYER_ARMOR_JUMP_TOP, 192, 152, 4, 2, 8, true, MAGENTA);

	IMAGEMANAGER->addFrameImage(KEY_PLAYER_HEAD_JUMP_BOTTOM, DIR_PLAYER_HEAD_JUMP_BOTTOM, 192, 192, 4, 2, 8, true, MAGENTA);
	IMAGEMANAGER->addFrameImage(KEY_PLAYER_BODY_JUMP_BOTTOM, DIR_PLAYER_BODY_JUMP_BOTTOM, 192, 152, 4, 2, 8, true, MAGENTA);
	IMAGEMANAGER->addFrameImage(KEY_PLAYER_ARMOR_JUMP_BOTTOM, DIR_PLAYER_ARMOR_JUMP_BOTTOM, 192, 152, 4, 2, 8, true, MAGENTA);

	IMAGEMANAGER->addImage(KEY_PLAYER_MINIMAP, DIR_PLAYER_MINIMAP, TILE_SIZE_MINIMAP, TILE_SIZE_MINIMAP, true, MAGENTA);

	// enemy.
	IMAGEMANAGER->addFrameImage(KEY_NECRODANCER_RIGHT_IDLE, DIR_NECRODANCER_RIGHT_IDLE, 352, 212, 4, 2, 4, true, MAGENTA);
	IMAGEMANAGER->addFrameImage(KEY_NECRODANCER_RIGHT_UP_JUMP, DIR_NECRODANCER_RIGHT_UP_JUMP, 704, 286, 4, 2, 4, true, MAGENTA);
	IMAGEMANAGER->addFrameImage(KEY_NECRODANCER_RIGHT_DOWN_JUMP, DIR_NECRODANCER_RIGHT_DOWN_JUMP, 704, 286, 4, 2, 4, true, MAGENTA);
	IMAGEMANAGER->addFrameImage(KEY_NECRODANCER_LEFT_IDLE, DIR_NECRODANCER_LEFT_IDLE, 352, 212, 4, 2, 4, true, MAGENTA);
	IMAGEMANAGER->addFrameImage(KEY_NECRODANCER_LEFT_UP_JUMP, DIR_NECRODANCER_LEFT_UP_JUMP, 704, 286, 4, 2, 4, true, MAGENTA);
	IMAGEMANAGER->addFrameImage(KEY_NECRODANCER_LEFT_DOWN_JUMP, DIR_NECRODANCER_LEFT_DOWN_JUMP, 704, 286, 4, 2, 4, true, MAGENTA);
	IMAGEMANAGER->addFrameImage(KEY_NECRODANCER_EXPLOSION_IDLE, DIR_NECRODANCER_EXPLOSION_IDLE, 352, 212, 4, 2, 4, true, MAGENTA);
	IMAGEMANAGER->addFrameImage(KEY_NECRODANCER_EXPLOSION, DIR_NECRODANCER_EXPLOSION, 440, 212, 5, 2, 5, true, MAGENTA);
	IMAGEMANAGER->addFrameImage(KEY_NECRODANCER_RIGHT_BLUEATT, DIR_NECRODANCER_RIGHT_BLUEATT, 352, 212, 4, 2, 4, true, MAGENTA);
	IMAGEMANAGER->addFrameImage(KEY_NECRODANCER_LEFT_BLUEATT, DIR_NECRODANCER_LEFT_BLUEATT, 352, 212, 4, 2, 4, true, MAGENTA);
	IMAGEMANAGER->addFrameImage(KEY_NECRODANCER_SOHWAN_IDLE, DIR_NECRODANCER_SOHWAN_IDLE, 88, 212, 1, 2, 1, true, MAGENTA);
	IMAGEMANAGER->addFrameImage(KEY_NECRODANCER_IDLE2, DIR_NECRODANCER_IDLE2, 176, 212, 2, 2, 2, true, MAGENTA);
	IMAGEMANAGER->addFrameImage(KEY_SLIME, DIR_SLIME, 208, 104, 4, 2, 4, true, MAGENTA);
	IMAGEMANAGER->addFrameImage(KEY_SLIME_JUMP, DIR_SLIME_JUMP, 208, 164, 4, 2, 4, true, MAGENTA);
	IMAGEMANAGER->addFrameImage(KEY_SLIME_BLUE, DIR_SLIME_BLUE, 208, 104, 4, 2, 4, true, MAGENTA);
	IMAGEMANAGER->addFrameImage(KEY_SLIME_BLUE_JUMP, DIR_SLIME_BLUE_JUMP, 208, 184, 4, 2, 4, true, MAGENTA);
	IMAGEMANAGER->addFrameImage(KEY_SLIME_BLUE_JUMP_TOP, DIR_SLIME_BLUE_JUMP_TOP, 208, 224, 4, 2, 4, true, MAGENTA);
	IMAGEMANAGER->addFrameImage(KEY_SLIME_BLUE_JUMP_BOTTOM, DIR_SLIME_BLUE_JUMP_BOTTOM, 208, 188, 4, 2, 4, true, MAGENTA);
	IMAGEMANAGER->addFrameImage(KEY_SKELETON_LEFT, DIR_SKELETON_LEFT, 384, 100, 8, 2, 8, true, MAGENTA);
	IMAGEMANAGER->addFrameImage(KEY_SKELETON_RIGHT, DIR_SKELETON_RIGHT, 384, 100, 8, 2, 8, true, MAGENTA);
	IMAGEMANAGER->addFrameImage(KEY_BAT_LEFT, DIR_BAT_LEFT, 288, 96, 4, 2, 4, true, MAGENTA);
	IMAGEMANAGER->addFrameImage(KEY_BAT_RIGHT, DIR_BAT_RIGHT, 288, 96, 4, 2, 4, true, MAGENTA);
	   
	// tile.
	IMAGEMANAGER->addImage(KEY_TILE_DIRT, DIR_TILE_DIRT, TILE_SIZE, TILE_SIZE, true, MAGENTA);
	IMAGEMANAGER->findImage(KEY_TILE_DIRT)->initForAlphaBlend();

	IMAGEMANAGER->addImage(KEY_TILE_DIRT_MINIMAP, DIR_TILE_DIRT_MINIMAP, TILE_SIZE_MINIMAP, TILE_SIZE_MINIMAP, true, MAGENTA);
	IMAGEMANAGER->findImage(KEY_TILE_DIRT_MINIMAP)->initForAlphaBlend();

	// wall.
	IMAGEMANAGER->addFrameImage(KEY_WALL_UNBREAKABLE, DIR_WALL_UNBREAKABLE, TILE_SIZE, TILE_SIZE * 2, 1, 1, 1, true, MAGENTA);
	IMAGEMANAGER->findImage(KEY_WALL_UNBREAKABLE)->initForAlphaBlend();
	IMAGEMANAGER->addFrameImage(KEY_WALL_DIRT, DIR_WALL_DIRT, TILE_SIZE * 16, TILE_SIZE * 2, 16, 1, 16, true, MAGENTA);
	IMAGEMANAGER->findImage(KEY_WALL_DIRT)->initForAlphaBlend();
	IMAGEMANAGER->addFrameImage(KEY_WALL_SHOP, DIR_WALL_SHOP, TILE_SIZE, TILE_SIZE * 2, 1, 1, 1, true, MAGENTA);
	IMAGEMANAGER->findImage(KEY_WALL_SHOP)->initForAlphaBlend();

	IMAGEMANAGER->addImage(KEY_WALL_UNBREAKABLE_MINIMAP, DIR_WALL_UNBREAKABLE_MINIMAP, TILE_SIZE_MINIMAP, TILE_SIZE_MINIMAP, true, MAGENTA);
	IMAGEMANAGER->findImage(KEY_WALL_UNBREAKABLE_MINIMAP)->initForAlphaBlend();
	IMAGEMANAGER->addImage(KEY_WALL_DIRT_MINIMAP, DIR_WALL_DIRT_MINIMAP, TILE_SIZE_MINIMAP, TILE_SIZE_MINIMAP, true, MAGENTA);
	IMAGEMANAGER->findImage(KEY_WALL_DIRT_MINIMAP)->initForAlphaBlend();
	IMAGEMANAGER->addImage(KEY_WALL_SHOP_MINIMAP, DIR_WALL_SHOP_MINIMAP, TILE_SIZE_MINIMAP, TILE_SIZE_MINIMAP, true, MAGENTA);
	IMAGEMANAGER->findImage(KEY_WALL_SHOP_MINIMAP)->initForAlphaBlend();

	// object.
	IMAGEMANAGER->addImage(KEY_STEPPING_STONE_LEFT, DIR_STEPPING_STONE_LEFT, 48, 48, true, MAGENTA);
	IMAGEMANAGER->addImage(KEY_STEPPING_STONE_TOP, DIR_STEPPING_STONE_TOP, 48, 48, true, MAGENTA);
	IMAGEMANAGER->addImage(KEY_STEPPING_STONE_RIGHT, DIR_STEPPING_STONE_RIGHT, 48, 48, true, MAGENTA);
	IMAGEMANAGER->addImage(KEY_STEPPING_STONE_BOTTOM, DIR_STEPPING_STONE_BOTTOM, 48, 48, true, MAGENTA);
	IMAGEMANAGER->addImage(KEY_STAIR, DIR_STAIR, 48, 48, true, MAGENTA);
	IMAGEMANAGER->addImage(KEY_STAIR_MINIMAP, DIR_STAIR_MINIMAP, TILE_SIZE_MINIMAP, TILE_SIZE_MINIMAP, true, MAGENTA);

	IMAGEMANAGER->addFrameImage(KEY_ITEM_GOLD, DIR_ITEM_GOLD, 480, 96, 10, 2, 20, true, MAGENTA);

	IMAGEMANAGER->addImage(KEY_ITEM_SHOVEL, DIR_ITEM_SHOVEL, 48, 48, true, MAGENTA);
	IMAGEMANAGER->addImage(KEY_ITEM_DAGGER, DIR_ITEM_DAGGER, 48, 48, true, MAGENTA);
	IMAGEMANAGER->addImage(KEY_ITEM_BROADSWORD, DIR_ITEM_BROADSWORD, 48, 48, true, MAGENTA);
	IMAGEMANAGER->addImage(KEY_ITEM_BODY, DIR_ITEM_BODY, 48, 48, true, MAGENTA);
	IMAGEMANAGER->addImage(KEY_ITEM_HEAD, DIR_ITEM_HEAD, 48, 48, true, MAGENTA);
	IMAGEMANAGER->addImage(KEY_ITEM_TORCH, DIR_ITEM_TORCH, 48, 48, true, MAGENTA);
	IMAGEMANAGER->addImage(KEY_ITEM_APPLE, DIR_ITEM_APPLE, 48, 48, true, MAGENTA);
	IMAGEMANAGER->addImage(KEY_ITEM_BOMB, DIR_ITEM_BOMB, 48, 48, true, MAGENTA);
	IMAGEMANAGER->addImage(KEY_ITEM_GOLDENLUTE, DIR_ITEM_GOLDENLUTE, 60, 50, true, MAGENTA);

	IMAGEMANAGER->addFrameImage(KEY_ITEM_BOMBDROP, DIR_ITEM_BOMBDROP, 240, 48, 5, 1, 5, true, MAGENTA);
	IMAGEMANAGER->addFrameImage(KEY_SFX_EXPLOSION, DIR_SFX_EXPLOSION, 1184, 148, 8, 1, 8, true, MAGENTA);

	IMAGEMANAGER->addImage(KEY_UI_MONSTER_HEART_FULL, DIR_UI_MONSTER_HEART_FULL, 24, 24, true, MAGENTA);
	IMAGEMANAGER->addImage(KEY_UI_MONSTER_HEART_EMPTY, DIR_UI_MONSTER_HEART_EMPTY, 24, 24, true, MAGENTA);

	IMAGEMANAGER->addFrameImage(KEY_NPC_SHOPKEEPER, DIR_NPC_SHOPKEEPER, 752, 152, 8, 2, 8, true, MAGENTA);

	IMAGEMANAGER->addFrameImage(KEY_ITEM_BOMBDROP, DIR_ITEM_BOMBDROP, 240, 48, 5, 1, 5, true, MAGENTA);

	// effect.
	IMAGEMANAGER->addFrameImage(KEY_SFX_EXPLOSION, DIR_SFX_EXPLOSION, 1184, 148, 8, 1, 8, true, MAGENTA);

	IMAGEMANAGER->addFrameImage(KEY_EFFECT_EXPLOSION55, DIR_EFFECT_EXPLOSION55, 1776, 222, 8, 1, 8, true, MAGENTA);
	IMAGEMANAGER->addFrameImage(KEY_EFFECT_ICEBLAST, DIR_EFFECT_ICEBLASE, 1408, 436, 4, 2, 8, true, MAGENTA);

	IMAGEMANAGER->addFrameImage(KEY_SWIPE_DAGGER_RIGHT, DIR_SWIPE_DAGGER_RIGHT, 144, 48, 3, 1, 3, true, MAGENTA);
	IMAGEMANAGER->addFrameImage(KEY_SWIPE_DAGGER_LEFT, DIR_SWIPE_DAGGER_LEFT, 144, 48, 3, 1, 3, true, MAGENTA);
	IMAGEMANAGER->addFrameImage(KEY_SWIPE_DAGGER_TOP, DIR_SWIPE_DAGGER_TOP, 144, 48, 3, 1, 3, true, MAGENTA);
	IMAGEMANAGER->addFrameImage(KEY_SWIPE_DAGGER_BOTTOM, DIR_SWIPE_DAGGER_BOTTOM, 144, 48, 3, 1, 3, true, MAGENTA);

	IMAGEMANAGER->addFrameImage(KEY_SWIPE_ENEMY_LEFT, DIR_SWIPE_ENEMY_LEFT, 270, 48, 5, 1, 5, true, MAGENTA);
	IMAGEMANAGER->addFrameImage(KEY_SWIPE_ENEMY_RIGHT, DIR_SWIPE_ENEMY_RIGHT, 270, 48, 5, 1, 5, true, MAGENTA);
	IMAGEMANAGER->addFrameImage(KEY_SWIPE_ENEMY_TOP, DIR_SWIPE_ENEMY_TOP, 240, 54, 5, 1, 5, true, MAGENTA);
	IMAGEMANAGER->addFrameImage(KEY_SWIPE_ENEMY_BOTTOM, DIR_SWIPE_ENEMY_BOTTOM, 240, 54, 5, 1, 5, true, MAGENTA);

	// background.
	IMAGEMANAGER->addImage(KEY_BACKGROUND_START_SCENE, DIR_BACKGROUND_START_SCENE, WINSIZEX, WINSIZEY);

	// ui.
	IMAGEMANAGER->addImage(KEY_UI_PRESS_ANY_KEY, DIR_UI_PRESS_ANY_KEY, 876, 72, true, MAGENTA);
	IMAGEMANAGER->findImage(KEY_UI_PRESS_ANY_KEY)->initForAlphaBlend();

	IMAGEMANAGER->addImage(KEY_UI_SLOT_1, DIR_UI_SLOT_1, 60, 66, true, MAGENTA);
	IMAGEMANAGER->addImage(KEY_UI_SLOT_2, DIR_UI_SLOT_2, 60, 66, true, MAGENTA);
	IMAGEMANAGER->addImage(KEY_UI_SLOT_3, DIR_UI_SLOT_3, 60, 66, true, MAGENTA);
	IMAGEMANAGER->addImage(KEY_UI_SLOT_4, DIR_UI_SLOT_4, 60, 66, true, MAGENTA);
	IMAGEMANAGER->addImage(KEY_UI_SLOT_5, DIR_UI_SLOT_5, 60, 66, true, MAGENTA);
	IMAGEMANAGER->addImage(KEY_UI_ACTION_1, DIR_UI_ACTION_1, 60, 84, true, MAGENTA);
	IMAGEMANAGER->addImage(KEY_UI_ACTION_2, DIR_UI_ACTION_2, 60, 84, true, MAGENTA);

	IMAGEMANAGER->addImage(KEY_UI_FULLHP, DIR_UI_FULLHP, 48, 44, true, MAGENTA);
	IMAGEMANAGER->addImage(KEY_UI_HALFHP, DIR_UI_HALFHP, 48, 44, true, MAGENTA);
	IMAGEMANAGER->addImage(KEY_UI_EMPTYHP, DIR_UI_EMPTYHP, 48, 44, true, MAGENTA);

	IMAGEMANAGER->addFrameImage(KEY_UI_HEART, DIR_UI_HEART, 164, 104, 2, 1, 2, true, MAGENTA);
	IMAGEMANAGER->addImage(KEY_UI_NOTE_GREEN, DIR_UI_NOTE_GREEN, 12, 64, true, MAGENTA);
	IMAGEMANAGER->addImage(KEY_UI_NOTE_RED, DIR_UI_NOTE_RED, 12, 64, true, MAGENTA);

	IMAGEMANAGER->addImage(KEY_UI_GOLD, DIR_UI_GOLD, 48, 48, true, MAGENTA);

	// sound.
	SOUNDMANAGER->addSound(KEY_BGM_INTRO, DIR_BGM_INTRO, true, true);
	SOUNDMANAGER->addSound(KEY_BGM_LOBBY, DIR_BGM_LOBBY, true, true);
	SOUNDMANAGER->addSound(KEY_BGM_MAIN_MENU, DIR_BGM_MAIN_MENU, true, true);
	SOUNDMANAGER->addSound(KEY_BGM_ZONE_1_1, DIR_BGM_ZONE_1_1, true, true);
	SOUNDMANAGER->addSound(KEY_BGM_BOSS_NECRODANCER, DIR_BGM_BOSS_NECRODANCER, true, true);
	
	SOUNDMANAGER->addSound3d(DIR_SHOPKEEPER);
	
	SOUNDMANAGER->addSound(KEY_VO_CAD_MELLE_1_01, DIR_VO_CAD_MELLE_1_01, false, false);
	SOUNDMANAGER->addSound(KEY_EN_SLIME_ATTACK, DIR_EN_SLIME_ATTACK, false, false);
	SOUNDMANAGER->addSound(KEY_EN_SLIME_DEATH, DIR_EN_SLIME_DEATH, false, false);
	SOUNDMANAGER->addSound(KEY_EN_BAT_ATTACK, DIR_EN_BAT_ATTACK, false, false);
	SOUNDMANAGER->addSound(KEY_EN_BAT_DEATH, DIR_EN_BAT_DEATH, false, false);
	SOUNDMANAGER->addSound(KEY_EN_SKEL_ATTACK_MELEE, DIR_EN_SKEL_ATTACK_MELEE, false, false);
	SOUNDMANAGER->addSound(KEY_VO_NEC_ATT_V1_01, DIR_VO_NEC_ATT_V1_01, false, false);
	SOUNDMANAGER->addSound(KEY_VO_NEC_DEATH, DIR_VO_NEC_DEATH, false, false);
	SOUNDMANAGER->addSound(KEY_VO_NEC_LAUGH_01, DIR_VO_NEC_LAUGH_01, false, false);
	SOUNDMANAGER->addSound(KEY_VO_NEC_LAUGH_02, DIR_VO_NEC_LAUGH_02, false, false);
	SOUNDMANAGER->addSound(KEY_SFX_BOMB_EXPLODE, DIR_SFX_BOMB_EXPLODE, false, false);
	SOUNDMANAGER->addSound(KEY_WEP_SPELL_GENERAL_ST, DIR_WEP_SPELL_GENERAL_ST, false, false);

	ITEMINFOMANAGER->init();
	MAPINFOMANAGER->init();
	PLAYERINFOMANAGER->init();
}

void releaseResources()
{
	PLAYERINFOMANAGER->release();
	PLAYERINFOMANAGER->releaseSingleton();
	MAPINFOMANAGER->release();
	MAPINFOMANAGER->releaseSingleton();
	ITEMINFOMANAGER->release();
	ITEMINFOMANAGER->releaseSingleton();

	XMLMANAGER->release();
	XMLMANAGER->releaseSingleton();
	TIMEMANAGER->release();
	TIMEMANAGER->releaseSingleton();
	TEXTDATAMANAGER->release();
	TEXTDATAMANAGER->releaseSingleton();
	SOUNDMANAGER->release();
	SOUNDMANAGER->releaseSingleton();
	SCENEMANAGER->release();
	SCENEMANAGER->releaseSingleton();
	MAPINFOMANAGER->release();
	MAPINFOMANAGER->releaseSingleton();
	KEYMANAGER->releaseSingleton();
	IMAGEMANAGER->release();
	IMAGEMANAGER->releaseSingleton();
	FONTMANAGER->releaseSingleton();
	CAMERAMANAGER->release();
	CAMERAMANAGER->releaseSingleton();
	RND->releaseSingleton();
}

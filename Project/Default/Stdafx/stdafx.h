#pragma once

#include <sdkddkver.h>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

//#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")	//Multibyte.
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")	
#pragma comment(lib, "Winmm.lib") // mmsystem.h	//Unicode.

#include <malloc.h>
#include <memory.h>
#include <mmsystem.h>
#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>
#include <time.h>

#include <bitset>
#include <cassert>
#include <iostream>
#include <map>
#include <random>
#include <vector>

#include "GameNode/MainGame/MainGame.h"
#include "Manager/ImageManager/ImageManager.h"
#include "Manager/KeyManager/KeyManager.h"
#include "Manager/FontManager/FontManager.h"
#include "Manager/ItemInfoManager/ItemInfoManager.h"
#include "Manager/MapInfoManager/MapInfoManager.h"
#include "Manager/PlayerInfoManager/PlayerInfoManager.h"
#include "Manager/SceneManager/SceneManager.h"
#include "Manager/SoundManager/SoundManager.h"
#include "Manager/TimeManager/TimeManager.h"
#include "Manager/XmlManager/XmlManager.h"
#include "Utility/CommonMacroFunction.h"
#include "Utility/Constants.h"
#include "Utility/Enums.h"
#include "Utility/RandomFunction.h"

using namespace std;

#define WINNAME				    L"WindowsAPI"

#define WINSTART_X			    100
#define WINSTART_Y			    100
#define WINSIZE_X				1920
#define WINSIZE_Y				1080
#define WINSTYLE				WS_CAPTION | WS_SYSMENU

#define RND						RandomFunction::GetSingleton()
#define KEY						KeyManager::GetSingleton()
#define IMG						ImageManager::GetSingleton()
#define FONT					FontManager::GetSingleton()
#define ITEM					ItemInfoManager::GetSingleton()
#define MAP_INFO				MapInfoManager::GetSingleton()
#define PLAYER_INFO				PlayerInfoManager::GetSingleton()
#define TIME					TimeManager::GetSingleton()
#define SCENE					SceneManager::GetSingleton()
#define SOUND					SoundManager::GetSingleton()
#define XML						XmlManager::GetSingleton()

#define SAFE_RELEASE(p)			{if((p) != NULL) { (p)->Release();}}
#define SAFE_DELETE(p)			{if((p) != NULL) { delete (p); (p) = NULL;}}
#define SAFE_DELETE_ARRAY(p)	{if((p) != NULL) { delete[] (p); (p) = NULL;}}

extern HINSTANCE				HANDLE_INSTANCE;
extern HWND						HANDLE_WINDOW;
extern POINT					POINT_MOUSE;
extern MainGame*				MAIN_GAME;
extern bool						MOUSE_CLICKED;

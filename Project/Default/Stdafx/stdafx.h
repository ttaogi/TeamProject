#pragma once

#include <sdkddkver.h>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

//#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")	//Multibyte.
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")		//Unicode.

#include <malloc.h>
#include <memory.h>
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
#include "Utility/CommonMacroFunction.h"
#include "Utility/Constants.h"
#include "Utility/Enums.h"
#include "Utility/RandomFunction.h"

using namespace std;

#define WINNAME				    L"WindowsAPI"

#define WINSTART_X			    1180
#define WINSTART_Y			    500
#define WINSIZE_X				1280
#define WINSIZE_Y				800
#define WINSTYLE				WS_CAPTION | WS_SYSMENU

#define RND						RandomFunction::GetSingleton()
#define KEY						KeyManager::GetSingleton()
#define IMG						ImageManager::GetSingleton()
#define FONT					FontManager::GetSingleton()

#define SAFE_RELEASE(p)			{if((p) != NULL) { (p)->Release();}}
#define SAFE_DELETE(p)			{if((p) != NULL) { delete (p); (p) = NULL;}}
#define SAFE_DELETE_ARRAY(p)	{if((p) != NULL) { delete[] (p); (p) = NULL;}}

extern HINSTANCE				HANDLE_INSTANCE;
extern HWND						HANDLE_WINDOW;
extern POINT					POINT_MOUSE;
extern bool						MOUSE_CLICKED;

const COLORREF MAGENTA			RGB(255, 0, 255);

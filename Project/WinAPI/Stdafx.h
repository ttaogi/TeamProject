#pragma once
#include <SDKDDKver.h>

// 거의 사용되지 않는 내용은 Windows 헤더에서 제외
#define WIN32_LEAN_AND_MEAN 

//! Windows 헤더 파일
#include <Windows.h>

//! 라이브러리
//#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
//멀티미디어
#pragma comment(lib,"Winmm.lib")
//알파 블렌드를 사용하기 위한 라이브러리 추가
#pragma comment (lib,"msimg32.lib")

//! C 런타임 헤더 파일
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <tchar.h>
#include <time.h>
#include <assert.h>
#include <mmsystem.h>
#include <mciapi.h>

//! C++ 런타임 헤더 파일
#include <iostream>
#include <random>
#include <bitset>
#include <vector>
#include <map>
#include <cassert>
#include <algorithm>
#include <functional>
// bind

using namespace std;

//===================================
// # 내가 만든 헤더파일을 이곳에 추가 #
//===================================
#include "CommonMacroFunction.h"
#include "RandomFunction.h"
#include "KeyManager.h"
#include "ImageManager.h"
#include "FontManager.h"
#include "TempSoundManager.h"
#include "Utils.h"
#include "TimeManager.h"
#include "TextDataManager.h"
#include "SceneManager.h"

using namespace MY_UTIL;

//========================
// # 싱글톤을 이곳에 추가 #
//========================
#define RND RandomFunction::getSingleton()
#define KEYMANAGER KeyManager::getSingleton()
#define IMAGEMANAGER ImageManager::getSingleton()
#define FONTMANAGER FontManager::getSingleton()
#define TEMPSOUNDMANAGER TempSoundManager::getSingleton()
#define TIMEMANAGER TimeManager::getSingleton()
#define TEXTDATAMANAGER TextDataManager::getSingleton()
#define SCENEMANAGER SceneManager::getSingleton()

//============================
// # 매크로 # (윈도우창 초기화)
//============================
#define WINNAME		 (LPTSTR)(TEXT("WindowsAPI"))

//#define FULLSCREEN

#ifdef FULLSCREEN
#define WINSTARTX	 1920
#define WINSTARTY	 0
//GetSystemMetrics() : 인자로 전달되는 시스템 설정 정보 반환
//	ㄴSM_CXSCREEN: 현재 화면 해상도 X축 반환
//	ㄴSM_CYSCREEN: 현재 화면 해상도 Y축 반환
#define WINSIZEX	 GetSystemMetrics(SM_CXSCREEN)
#define WINSIZEY	 GetSystemMetrics(SM_CYSCREEN)
#define WINSTYLE	 WS_POPUPWINDOW | WS_MAXIMIZE

#else

#define WINSTARTX	 200
#define WINSTARTY	 100
#define WINSIZEX	 1280
#define WINSIZEY	 800
#define WINSTYLE	 WS_CAPTION | WS_SYSMENU
#endif

//=========================
// # 매크로 # (기능 및 효율)
//=========================
#define CENTER_X		WINSIZEX /2
#define CENTER_Y		WINSIZEY /2


//===============================================
// # 매크로 함수 # (클래스에서 동적할당된 부분 해제)
//===============================================
#define SAFE_DELETE(p)			{if(p) {delete (p); (p) = nullptr;}}
#define SAFE_DELETE_ARRAY(p)	{if(p) {delete[] (p); (p) = nullptr;}}
#define SAFE_RELEASE(p)			{if(p) {(p)->release(); (p) = nullptr;}}

//=============
// # 전역변수 #
//=============
extern HINSTANCE	_hInstance;
extern HWND			_hWnd;
extern POINT		_ptMouse;
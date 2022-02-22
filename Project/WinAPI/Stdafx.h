#pragma once
#include <SDKDDKver.h>

// ���� ������ �ʴ� ������ Windows ������� ����
#define WIN32_LEAN_AND_MEAN 

//! Windows ��� ����
#include <Windows.h>

//! ���̺귯��
//#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
//��Ƽ�̵��
#pragma comment(lib,"Winmm.lib")
//���� ���带 ����ϱ� ���� ���̺귯�� �߰�
#pragma comment (lib,"msimg32.lib")

//! C ��Ÿ�� ��� ����
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <tchar.h>
#include <time.h>
#include <assert.h>
#include <mmsystem.h>
#include <mciapi.h>

//! C++ ��Ÿ�� ��� ����
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
// # ���� ���� ��������� �̰��� �߰� #
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
// # �̱����� �̰��� �߰� #
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
// # ��ũ�� # (������â �ʱ�ȭ)
//============================
#define WINNAME		 (LPTSTR)(TEXT("WindowsAPI"))

//#define FULLSCREEN

#ifdef FULLSCREEN
#define WINSTARTX	 1920
#define WINSTARTY	 0
//GetSystemMetrics() : ���ڷ� ���޵Ǵ� �ý��� ���� ���� ��ȯ
//	��SM_CXSCREEN: ���� ȭ�� �ػ� X�� ��ȯ
//	��SM_CYSCREEN: ���� ȭ�� �ػ� Y�� ��ȯ
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
// # ��ũ�� # (��� �� ȿ��)
//=========================
#define CENTER_X		WINSIZEX /2
#define CENTER_Y		WINSIZEY /2


//===============================================
// # ��ũ�� �Լ� # (Ŭ�������� �����Ҵ�� �κ� ����)
//===============================================
#define SAFE_DELETE(p)			{if(p) {delete (p); (p) = nullptr;}}
#define SAFE_DELETE_ARRAY(p)	{if(p) {delete[] (p); (p) = nullptr;}}
#define SAFE_RELEASE(p)			{if(p) {(p)->release(); (p) = nullptr;}}

//=============
// # �������� #
//=============
extern HINSTANCE	_hInstance;
extern HWND			_hWnd;
extern POINT		_ptMouse;
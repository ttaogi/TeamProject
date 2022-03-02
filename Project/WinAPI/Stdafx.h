#pragma once

#include <SDKDDKver.h>

// ���� ������ �ʴ� ������ Windows ������� ����
#define WIN32_LEAN_AND_MEAN 

//! Windows ��� ����
#include <Windows.h>

#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
//! ���̺귯��
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
#pragma region Manager
#include "CameraManager.h"
#include "FontManager.h"
#include "ImageManager.h"
#include "ItemInfoManager.h"
#include "KeyManager.h"
#include "MapInfoManager.h"
#include "PlayerInfoManager.h"
#include "SceneManager.h"
#include "SoundManager.h"
#include "TextDataManager.h"
#include "TimeManager.h"
#include "XmlManager.h"
#pragma endregion Manager
#pragma region Utility
#include "CommonMacroFunction.h"
#include "Constants.h"
#include "Enums.h"
#include "RandomFunction.h"
#include "Utils.h"
#pragma endregion Utility

using namespace MY_UTIL;

//========================
// # �̱����� �̰��� �߰� #
//========================
#define RND						RandomFunction::getSingleton()
#define CAMERAMANAGER			CameraManager::getSingleton()
#define FONTMANAGER				FontManager::getSingleton()
#define IMAGEMANAGER			ImageManager::getSingleton()
#define ITEMINFOMANAGER			ItemInfoManager::getSingleton()
#define KEYMANAGER				KeyManager::getSingleton()
#define MAPINFOMANAGER			MapInfoManager::getSingleton()
#define PLAYERINFOMANAGER		PlayerInfoManager::getSingleton()
#define SCENEMANAGER			SceneManager::getSingleton()
#define SOUNDMANAGER			SoundManager::getSingleton()
#define TEXTDATAMANAGER			TextDataManager::getSingleton()
#define TIMEMANAGER				TimeManager::getSingleton()
#define XMLMANAGER				XmlManager::getSingleton()

//============================
// # ��ũ�� # (������â �ʱ�ȭ)
//============================
#define WINNAME		 (LPTSTR)(TEXT("WindowsAPI"))
#define WINSTARTX	 200
#define WINSTARTY	 100
#define WINSIZEX	 960
#define WINSIZEY	 540
#define WINSTYLE	 WS_CAPTION | WS_SYSMENU

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
class MainGame;
extern MainGame*	_mg;

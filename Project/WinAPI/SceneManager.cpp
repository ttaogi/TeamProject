#include "Stdafx.h"
#include "SceneManager.h"
#include "GameNode.h"

//함수에 종속되지않은 외부영역에 선언
GameNode* SceneManager::_currentScene = nullptr;
GameNode* SceneManager::_loadingScene = nullptr;
GameNode* SceneManager::_readyScene   = nullptr;

//콜백을 빼먹으면 죽은 친구
DWORD CALLBACK loadingThread(LPVOID prc)
{
	//교체될 씬의 함수 실행
	SceneManager::_readyScene->init();
	
	//현재 씬을 교체될 씬으로 변경
	SceneManager::_currentScene = SceneManager::_readyScene;

	//로딩 씬 해제
	SceneManager::_loadingScene->release();
	SceneManager::_loadingScene = nullptr;
	SceneManager::_readyScene   = nullptr;
	
	return 0;
}

HRESULT SceneManager::init(void)
{
	_currentScene = nullptr;
	_loadingScene = nullptr;
	_readyScene = nullptr;

	return S_OK;
}

void SceneManager::release(void)
{
	mapSceneIter miSceneList = _mSceneList.begin();
	for (; miSceneList != _mSceneList.end();)
	{
		if (miSceneList->second != nullptr)
		{
			if (miSceneList->second == _currentScene)
			{
				miSceneList->second->release();
			}

			SAFE_DELETE(miSceneList->second);
			miSceneList = _mSceneList.erase(miSceneList);
		}
		else ++miSceneList;
	}
	_mSceneList.clear();

	/*
	//같은건데 예외처리 없는거.. 
	//예외처리 생각하면서 작성하는것이 베스트 코드가 짧다고 좋은게 아님 코드 수에 연연하지말것
	
	for each(auto scene in _mSceneList)
	{
		scene.second->release();
		SAFE_DELETE(scene.second);
	}
	*/
}

void SceneManager::update(void)
{
	//현재 씬이 존재하면 현재씬만 업데이트
	//이렇게 한번씩 더 묻기
	if(_currentScene) _currentScene->update();
}

void SceneManager::render(void)
{
	//현재 씬이 존재하면 현재씬만 렌더
	if (_currentScene) _currentScene->render();
}

//씬 추가
GameNode* SceneManager::addScene(string sceneName, GameNode* scene)
{
	// 씬이 없다면 리턴
	if (!scene) return nullptr;

	_mSceneList.insert(make_pair(sceneName, scene));

	return scene;
}

GameNode* SceneManager::addLoadingScene(string loadingSceneName, GameNode* scene)
{
	if (!scene) return nullptr;

	_mSceneList.insert(make_pair(loadingSceneName, scene));

	return scene;
}

//씬 변경
HRESULT SceneManager::changeScene(string sceneName)
{
	//변경하려고 하는 씬을 찾는다.
	mapSceneIter find = _mSceneList.find(sceneName);

	if (find == _mSceneList.end()) return E_FAIL;
	if (find->second == _currentScene) return S_OK;

	if (SUCCEEDED(find->second->init()))
	{
		_currentScene = find->second;

		return S_OK;
	}

	return E_FAIL;
}



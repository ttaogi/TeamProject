#include "Stdafx/stdafx.h"

#include "SceneManager.h"

#include "GameNode/GameNode.h"
#include "Scene/Scene.h"

wstring SceneManager::nextSceneKey = KEY_NONE_SCENE;
Scene* SceneManager::currentScene = NULL;
Scene* SceneManager::loadingScene = NULL;
Scene* SceneManager::readyScene = NULL;

HRESULT SceneManager::Init()
{
	currentScene = NULL;
	loadingScene = NULL;
	readyScene = NULL;

	return S_OK;
}

void SceneManager::Release()
{
	currentScene = NULL;
	loadingScene = NULL;
	readyScene = NULL;

	map<wstring, Scene*>::iterator iter = sceneMap.begin();

	for (; iter != sceneMap.end();) {
		if (iter->second) {
			if (iter->second == currentScene)
				iter->second->Release();

			SAFE_DELETE(iter->second);
			iter = sceneMap.erase(iter);
		}
		else ++iter;
	}
	sceneMap.clear();
}

void SceneManager::Update()
{
	if (nextSceneKey == KEY_TITLE_SCENE)
	{
		SCENE->ChangeScene(nextSceneKey);
		nextSceneKey = KEY_NONE_SCENE;
	}
	else if (nextSceneKey == KEY_ONGAME_SCENE)
	{
		SCENE->ChangeScene(nextSceneKey);
		nextSceneKey = KEY_NONE_SCENE;
	}
	else if (nextSceneKey == KEY_END_SCENE)
	{
		SCENE->ChangeScene(nextSceneKey);
		nextSceneKey = KEY_NONE_SCENE;
	}
	else
	{
		nextSceneKey = KEY_NONE_SCENE;
	}

	if (currentScene) currentScene->Update();
}

void SceneManager::Render() { if (currentScene) currentScene->Render(); }

std::wstring SceneManager::GetNextSceneKey() const { return nextSceneKey; }

void SceneManager::SetNextSceneKey(std::wstring _nextSceneKey) { nextSceneKey = _nextSceneKey; }

void SceneManager::SetNextSceneKeyTitleScene() { nextSceneKey = KEY_TITLE_SCENE; }

void SceneManager::SetNextSceneKeyOnGameScene() { nextSceneKey = KEY_ONGAME_SCENE; }

void SceneManager::SetNextSceneKeyEndScene() { nextSceneKey = KEY_END_SCENE; }

Scene* SceneManager::AddScene(wstring _sceneName, Scene* _scene)
{
	if (!_scene) return NULL;

	sceneMap.insert(make_pair(_sceneName, _scene));

	return _scene;
}

Scene* SceneManager::AddLoadingScene(wstring _loadingSceneName, Scene* _scene)
{
	if (!_scene) return NULL;

	sceneMap.insert(make_pair(_loadingSceneName, _scene));

	return _scene;
}

HRESULT SceneManager::ChangeScene(wstring _sceneName)
{
	map<wstring, Scene*>::iterator iter = sceneMap.find(_sceneName);

	if (iter == sceneMap.end()) return E_FAIL;
	if (iter->second == currentScene) return S_OK;

	if (SUCCEEDED(iter->second->Init()))
	{
		SAFE_RELEASE(currentScene);
		currentScene = iter->second;
		return S_OK;
	}

	return E_FAIL;
}

DWORD CALLBACK LoadingThread(LPVOID _prc)
{
	SceneManager::readyScene->Init();
	SceneManager::currentScene = SceneManager::readyScene;

	SceneManager::loadingScene->Release();
	SceneManager::loadingScene = NULL;
	SceneManager::readyScene = NULL;

	return 0;
}

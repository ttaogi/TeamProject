#include "Stdafx.h"
#include "SceneManager.h"
#include "GameNode.h"

//�Լ��� ���ӵ������� �ܺο����� ����
GameNode* SceneManager::_currentScene = nullptr;
GameNode* SceneManager::_loadingScene = nullptr;
GameNode* SceneManager::_readyScene   = nullptr;

//�ݹ��� �������� ���� ģ��
DWORD CALLBACK loadingThread(LPVOID prc)
{
	//��ü�� ���� �Լ� ����
	SceneManager::_readyScene->init();
	
	//���� ���� ��ü�� ������ ����
	SceneManager::_currentScene = SceneManager::_readyScene;

	//�ε� �� ����
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
	//�����ǵ� ����ó�� ���°�.. 
	//����ó�� �����ϸ鼭 �ۼ��ϴ°��� ����Ʈ �ڵ尡 ª�ٰ� ������ �ƴ� �ڵ� ���� ������������
	
	for each(auto scene in _mSceneList)
	{
		scene.second->release();
		SAFE_DELETE(scene.second);
	}
	*/
}

void SceneManager::update(void)
{
	//���� ���� �����ϸ� ������� ������Ʈ
	//�̷��� �ѹ��� �� ����
	if(_currentScene) _currentScene->update();
}

void SceneManager::render(void)
{
	//���� ���� �����ϸ� ������� ����
	if (_currentScene) _currentScene->render();
}

//�� �߰�
GameNode* SceneManager::addScene(string sceneName, GameNode* scene)
{
	// ���� ���ٸ� ����
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

//�� ����
HRESULT SceneManager::changeScene(string sceneName)
{
	//�����Ϸ��� �ϴ� ���� ã�´�.
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



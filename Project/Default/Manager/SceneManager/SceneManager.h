#pragma once

#include "DesignPattern/SingletonBase/SingletonBase.h"

class Scene;

class SceneManager : public SingletonBase<SceneManager>
{
private:
	static std::wstring nextSceneKey;
	static Scene* currentScene;
	static Scene* loadingScene;
	static Scene* readyScene;

	std::map<std::wstring, Scene*> sceneMap;
	std::map<std::wstring, Scene*> loadingSceneMap;
public:
	SceneManager() { }
	~SceneManager() { }

	HRESULT Init();
	void Release();
	void Update();
	void Render();

	std::wstring GetNextSceneKey() const;
	void SetNextSceneKey(std::wstring _nextSceneKey);
	void SetNextSceneKeyTitleScene();
	void SetNextSceneKeyOnGameScene();
	void SetNextSceneKeyEndScene();

	Scene* AddScene(std::wstring _sceneName, Scene* _scene);
	Scene* AddLoadingScene(std::wstring _loadingSceneName, Scene* _scene);

	HRESULT ChangeScene(std::wstring _sceneName);

	friend DWORD CALLBACK LoadingThread(LPVOID _prc);
};
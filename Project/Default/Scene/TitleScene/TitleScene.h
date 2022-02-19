#pragma once

#include "Scene/Scene.h"

class TitleScene : public Scene {
private:
public:
	TitleScene();
	~TitleScene();

	HRESULT Init();
	void Release();
	void Update();
	void Render();
};
#pragma once

#include "Scene/Scene.h"

class EndScene : public Scene
{
private:
public:
	EndScene();
	~EndScene();

	HRESULT Init();
	void Update();
	void Release();
	void Render();
};
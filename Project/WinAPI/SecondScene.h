#pragma once
#include "GameNode.h"
#include "TempSoundTest.h"

#define ENEMY_MAX 1

struct tagPlayer
{
	RECT rc1;
	RECT rc2;
	RECT rc3;
	RECT rc4;
};

struct tagEnemy
{
	RECT en1;
	RECT en2;
	RECT en3;
	RECT en4;
	int speed1;
	int speed2;
	int speed3;
	int speed4;
	bool die;
};

class SecondScene:public GameNode
{
private:
	TempSoundTest* _tempSound;
	tagPlayer _player;
	tagEnemy _enemy[ENEMY_MAX];

	//루프용 변수
	int _offsetX, _offsetY;
	int _bgSpeed;

	int _textBufferCnt;
	RECT temp;
	
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	SecondScene() {}
	~SecondScene() {}
};


#pragma once
#include "GameNode.h"

enum Note
{
	Heat, Miss, Dungeon
};

//장비창
class PlEquip : public GameNode
{
private:
	RECT _slot_1_rc;
	RECT _slot_2_rc;
	RECT _slot_3_rc;
	RECT _slot_4_rc;
	RECT _slot_5_rc;
	
	RECT _action_1_rc;
	RECT _action_2_rc;
	
	Image* _slot_1;
	Image* _slot_2;
	Image* _slot_3;
	Image* _slot_4;
	Image* _slot_5;

	Image* _action_1;
	Image* _action_2;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	PlEquip() {}
	~PlEquip() {}
};

//====================================================================================
//플레이어 체력
class PlHp : public GameNode
{
private:
	RECT _Hp_rc;

	Image* _Hp;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	
	PlHp();
	~PlHp();
};

//====================================================================================
//리듬노트
class RhythmNote : public GameNode
{
private:
	float Bpm;
	float* _x;
	float* _y;
	float _rndTimeCount;
	float _worldTimeCount;

	int _currentFrameX;
	int _currentFrameY;
		
	RECT Heart_rc;
	RECT HeatBox;
	RECT Note_rc_L;
	RECT Note_rc_R;

	Image* heart;
	Image* Note_Green_L;
	Image* Note_Green_R;
	Image* Note_Red_L;
	Image* Note_Red_R;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void animation(void);

	RhythmNote() {}
	~RhythmNote() {}
};

//====================================================================================
//재화
class PlGold : public GameNode
{
private:
	RECT Gold_rc;
	Image* Gold;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	PlGold() {}
	~PlGold() {}
};


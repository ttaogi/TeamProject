#pragma once
#include "GameNode.h"

class Animator;
class Scene;

enum Note
{
	Heat, Miss,
};

struct tagNote
{
	Image* img;
	RECT rc;
	float x, y;
	float HeartX, HeartY;
	float angle;
	float speed;
	bool fire;
	int alpha;
};

//���??
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
class PlHp : public GameNode
{
private:
	RECT _Hp_rc;

	Image* _FullHp;
	Image* _HalfHp;
	Image* _EmptyHp;

	int count;

	bool PlHeat;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	
	PlHp() {}
	~PlHp() {}
};

//====================================================================================
class RhythmNote : public GameNode
{
private:
	vector<tagNote> _vNote;
	vector<tagNote> ::iterator _viNote;
	RhythmNote* _rhythmNote;
	
	double _count;

	double _turnInterval;
	float _noteSpeed;
	float _SceneStartTime;
	
	Note _NoteHeat;

	RECT Heart_rc;
	RECT HeatBox;
	
	Image* heart;
	Image* Note_Green;
	Image* Note_Red;

	Animator* _animator;
	Scene* scene;
public:
	HRESULT init(Scene* _scene);
	void release(void);
	void update(void);
	void render(void);
		
	void NoteCreate(float x, float y, float angle, float speed);
	void NoteMove(void);
	void Notedraw(void);

	void NoteCollision(void);
	void removeNote(int arrNum);

	vector<tagNote> getNote(void) { return _vNote; }
	RECT getHeatBox(void) { return HeatBox; }

	RhythmNote() {}
	~RhythmNote() {}
};

//====================================================================================
//��ȭ
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


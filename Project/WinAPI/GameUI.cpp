#include "stdafx.h"
#include "GameUI.h"

//장비창
HRESULT PlEquip::init(void)
{
	_slot_1 = IMAGEMANAGER->addImage(KEY_UI_SLOT_1, DIR_UI_SLOT_1, 60, 66, true, MAGENTA);
	_slot_2 = IMAGEMANAGER->addImage(KEY_UI_SLOT_2, DIR_UI_SLOT_2, 60, 66, true, MAGENTA);
	_slot_3 = IMAGEMANAGER->addImage(KEY_UI_SLOT_3, DIR_UI_SLOT_3, 60, 66, true, MAGENTA);
	_slot_4 = IMAGEMANAGER->addImage(KEY_UI_SLOT_4, DIR_UI_SLOT_4, 60, 66, true, MAGENTA);
	_slot_5 = IMAGEMANAGER->addImage(KEY_UI_SLOT_5, DIR_UI_SLOT_5, 60, 66, true, MAGENTA);

	_action_1 = IMAGEMANAGER->addImage(KEY_UI_ACTION_1, DIR_UI_ACTION_1, 60, 84, true, MAGENTA);
	_action_2 = IMAGEMANAGER->addImage(KEY_UI_ACTION_2, DIR_UI_ACTION_2, 60, 84, true, MAGENTA);

	_slot_1_rc = RectMakeCenter(50, 45, _slot_1->getWidth(), _slot_1->getHeight());
	_slot_2_rc = RectMakeCenter(120, 45, _slot_2->getWidth(), _slot_2->getHeight());
	_slot_3_rc = RectMakeCenter(190, 45, _slot_3->getWidth(), _slot_3->getHeight());
	_slot_4_rc = RectMakeCenter(260, 45, _slot_4->getWidth(), _slot_4->getHeight());
	_slot_5_rc = RectMakeCenter(330, 45, _slot_5->getWidth(), _slot_5->getHeight());

	_action_1_rc = RectMakeCenter(50, 130, _slot_5->getWidth(), _slot_5->getHeight());
	_action_2_rc = RectMakeCenter(50, 210, _slot_5->getWidth(), _slot_5->getHeight());

	return S_OK;
}

void PlEquip::release(void)
{
}

void PlEquip::update(void)
{
}

void PlEquip::render(void)
{
	_slot_1->render(getMemDC(), _slot_1_rc.left, _slot_1_rc.top);
	_slot_2->render(getMemDC(), _slot_2_rc.left, _slot_2_rc.top);
	_slot_3->render(getMemDC(), _slot_3_rc.left, _slot_3_rc.top);
	_slot_4->render(getMemDC(), _slot_4_rc.left, _slot_4_rc.top);
	_slot_5->render(getMemDC(), _slot_5_rc.left, _slot_5_rc.top);

	_action_1->render(getMemDC(), _action_1_rc.left, _action_1_rc.top);
	_action_2->render(getMemDC(), _action_2_rc.left, _action_2_rc.top);
}

//====================================================================================
//플레이어 체력
HRESULT PlHp::init(void)
{
	_Hp = IMAGEMANAGER->addImage(KEY_UI_HP, DIR_UI_HP, 48, 44, true, MAGENTA);
	
	_Hp_rc = RectMakeCenter(810, 45, _Hp->getWidth(), _Hp->getHeight());
	
	return S_OK;
}

void PlHp::release(void)
{
}

void PlHp::update(void)
{
}

void PlHp::render(void)
{
	_Hp->render(getMemDC(), _Hp_rc.left, _Hp_rc.top);
}

PlHp::PlHp()
{
}

PlHp::~PlHp()
{
}

//====================================================================================
//리듬노트
HRESULT RhythmNote::init(const char* imageName, int NoteMax, float range)
{
	heart		 = IMAGEMANAGER->addFrameImage(KEY_UI_HEART, DIR_UI_HEART, 164, 104, 2, 1, 2, true, MAGENTA);
	Note_Green	 = IMAGEMANAGER->addImage(KEY_UI_NOTE_GREEN, DIR_UI_NOTE_GREEN, 12, 64, true, MAGENTA);
	Note_Red	 = IMAGEMANAGER->addImage(KEY_UI_NOTE_RED, DIR_UI_NOTE_RED, 12, 64, true, MAGENTA);
		
	Heart_rc	 = RectMakeCenter(WINSIZEX / 2, 480, heart->getFrameWidth(), heart->getFrameHeight());
	HeatBox		 = RectMakeCenter(WINSIZEX / 2, 480, 150, heart->getHeight());

	_worldTimeCount = TIMEMANAGER->getWorldTime();
	_SceneStartTime = TIMEMANAGER->getWorldTime();
	
	_count = 0;
	_imageName = imageName;
	_range = range;
	_NoteMax = NoteMax;

	return S_OK;
}

void RhythmNote::release(void)
{
	_vNote.clear();
}

void RhythmNote::update(void)
{
	_count += TIMEMANAGER->getElapsedTime();
	if (_count > 0.5f)
	{
		_count -= 0.5f;
		NoteCreate(0, 480, 1, 7);
		NoteCreate(WINSIZEX, 480, -1, 7);
	}

	NoteMove();
}

void RhythmNote::render(void)
{
	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		Rectangle(getMemDC(), HeatBox.left, HeatBox.top, HeatBox.right, HeatBox.bottom);
	}
		
	//animation();

	Notedraw();
	heart->frameRender(getMemDC(), Heart_rc.left, Heart_rc.top, heart->getFrameX(), heart->getFrameY());
}

void RhythmNote::animation(void)
{
	/*if (_rndTimeCount + _worldTimeCount <= TIMEMANAGER->getWorldTime())
	{
		_worldTimeCount = TIMEMANAGER->getWorldTime();
		_currentFrameX++;
		if (heart->getMaxFrameX() <= _currentFrameX)
		{
			_currentFrameX = 0;
		}
	}*/
}

void RhythmNote::NoteCreate(float x, float y, float angle, float speed)
{
	if (_NoteMax <= _vNote.size()) return;

	tagNote Note;
	ZeroMemory(&Note, sizeof(tagNote));
	Note.img = Note_Green;
	/*
	if(TIMEMANAGER->getWorldTime() - _SceneStartTime < 150)
	Note.img = Note_Green;
	시간여유가 있으면 초록색 출력
	else
	남은 시간이 30초이하이면 빨강색 출력
	
	_worldTimeCount = TIMEMANAGER->getWorldTime();
	_SceneStartTime = TIMEMANAGER->getWorldTime();
	*/

	Note.speed	= speed;
	Note.angle	= angle;
	Note.x = Note.HeartX = x;
	Note.y = Note.HeartY = y;
	Note.rc = RectMakeCenter((int)Note.x, (int)Note.y, Note.img->getWidth(), Note.img->getHeight());

	_vNote.push_back(Note);
}

void RhythmNote::NoteMove(void)
{
	for (_viNote = _vNote.begin(); _viNote != _vNote.end(); ++_viNote)
	{
		_viNote->x += _viNote->angle * _viNote->speed;
		
		_viNote->rc = RectMakeCenter(_viNote->x, _viNote->y, _viNote->img->getWidth(), _viNote->img->getHeight());
	}
	
}

void RhythmNote::Notedraw(void)
{
	for (_viNote = _vNote.begin(); _viNote != _vNote.end(); ++_viNote)
	{
		_viNote->img->render(getMemDC(), _viNote->rc.left, _viNote->rc.top);
	}
}


//====================================================================================
//재화
HRESULT PlGold::init(void)
{
	Gold = IMAGEMANAGER->addImage(KEY_UI_GOLD, DIR_UI_GOLD, 48, 48, true, MAGENTA);
	
	Gold_rc = RectMakeCenter(870, 45, Gold->getWidth(), Gold->getHeight());

	return S_OK;
}

void PlGold::release(void)
{
}

void PlGold::update(void)
{
}

void PlGold::render(void)
{
	Gold->render(getMemDC(), Gold_rc.left, Gold_rc.top);
}
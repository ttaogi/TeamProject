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
HRESULT RhythmNote::init(void)
{
	heart		 = IMAGEMANAGER->addFrameImage(KEY_UI_HEART, DIR_UI_HEART, 164, 104, 2, 1, 2, true, MAGENTA);
	
	Note_Green_L = IMAGEMANAGER->addImage(KEY_UI_NOTE_GREEN_L, DIR_UI_NOTE_GREEN_L, 12, 64, true, MAGENTA);
	Note_Green_R = IMAGEMANAGER->addImage(KEY_UI_NOTE_GREEN_R, DIR_UI_NOTE_GREEN_R, 12, 64, true, MAGENTA);
	
	Note_Red_L	 = IMAGEMANAGER->addImage(KEY_UI_NOTE_RED_L, DIR_UI_NOTE_RED_L, 12, 64, true, MAGENTA);
	Note_Red_R	 = IMAGEMANAGER->addImage(KEY_UI_NOTE_RED_R, DIR_UI_NOTE_RED_R, 12, 64, true, MAGENTA);
	
	Heart_rc	 = RectMakeCenter(WINSIZEX / 2, 420, heart->getFrameX(), heart->getFrameY());

	Note_rc_L	 = RectMakeCenter(WINSIZEX / 2 - 50, 420, Note_Green_L->getFrameX(), Note_Green_L->getFrameY());
	Note_rc_R    = RectMakeCenter(WINSIZEX / 2 - 50, 420, Note_Green_R->getFrameX(), Note_Green_R->getFrameY());
	
	HeatBox		 = RectMakeCenter(WINSIZEX / 2, 420, 150, heart->getHeight());

	_worldTimeCount = TIMEMANAGER->getWorldTime();
	_rndTimeCount = RND->getFromFloatTo(0.04f, 0.1f);

	return S_OK;
}

void RhythmNote::release(void)
{
}

void RhythmNote::update(void)
{
	
}

void RhythmNote::render(void)
{
	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		Rectangle(getMemDC(), HeatBox.left, HeatBox.top, HeatBox.right, HeatBox.bottom);
	}
	
	//animation();
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
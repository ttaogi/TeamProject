#include "Stdafx.h"

#include "GameUI.h"

#include "Animator.h"
#include "Animation.h"
#include "Scene.h"

HRESULT PlEquip::init(void)
{
	// shovel, attack, body, head, ring.
	_slot_1 = IMAGEMANAGER->addImage(KEY_UI_SLOT_1, DIR_UI_SLOT_1, 60, 66, true, MAGENTA);
	_slot_2 = IMAGEMANAGER->addImage(KEY_UI_SLOT_2, DIR_UI_SLOT_2, 60, 66, true, MAGENTA);
	_slot_3 = IMAGEMANAGER->addImage(KEY_UI_SLOT_3, DIR_UI_SLOT_3, 60, 66, true, MAGENTA);
	_slot_4 = IMAGEMANAGER->addImage(KEY_UI_SLOT_4, DIR_UI_SLOT_4, 60, 66, true, MAGENTA);
	_slot_5 = IMAGEMANAGER->addImage(KEY_UI_SLOT_5, DIR_UI_SLOT_5, 60, 66, true, MAGENTA);

	// item, bomb.
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
	Item tmpItem;
	_slot_1->render(getMemDC(), _slot_1_rc.left, _slot_1_rc.top);
	tmpItem = PLAYERINFOMANAGER->getShovel();
	if (tmpItem.stripe) tmpItem.stripe->render(getMemDC(), _slot_1_rc.left + 6, _slot_1_rc.top + 9);

	_slot_2->render(getMemDC(), _slot_2_rc.left, _slot_2_rc.top);
	tmpItem = PLAYERINFOMANAGER->getAttack();
	if (tmpItem.stripe) tmpItem.stripe->render(getMemDC(), _slot_2_rc.left + 6, _slot_2_rc.top + 9);

	_slot_3->render(getMemDC(), _slot_3_rc.left, _slot_3_rc.top);
	tmpItem = PLAYERINFOMANAGER->getBody();
	if (tmpItem.stripe) tmpItem.stripe->render(getMemDC(), _slot_3_rc.left + 6, _slot_3_rc.top + 9);

	_slot_4->render(getMemDC(), _slot_4_rc.left, _slot_4_rc.top);
	tmpItem = PLAYERINFOMANAGER->getHead();
	if (tmpItem.stripe) tmpItem.stripe->render(getMemDC(), _slot_4_rc.left + 6, _slot_4_rc.top + 9);

	_slot_5->render(getMemDC(), _slot_5_rc.left, _slot_5_rc.top);
	tmpItem = PLAYERINFOMANAGER->getTorch();
	if (tmpItem.stripe) tmpItem.stripe->render(getMemDC(), _slot_5_rc.left + 6, _slot_5_rc.top + 9);
	
	_action_1->render(getMemDC(), _action_1_rc.left, _action_1_rc.top);
	tmpItem = PLAYERINFOMANAGER->getHeal();
	if (tmpItem.stripe) tmpItem.stripe->render(getMemDC(), _action_1_rc.left + 6, _action_1_rc.top + 18);
	_action_2->render(getMemDC(), _action_2_rc.left, _action_2_rc.top);
	tmpItem = PLAYERINFOMANAGER->getBomb();
	if (tmpItem.stripe) tmpItem.stripe->render(getMemDC(), _action_2_rc.left + 6, _action_2_rc.top + 18);

	string script = "Z";
	FONTMANAGER->drawText(getMemDC(), 45, 155, "PFStardust", 15, 2000, (char*)script.c_str(), (int)script.length(), RGB(255, 255, 255));

	script = "X";
	FONTMANAGER->drawText(getMemDC(), 45, 235, "PFStardust", 15, 2000, (char*)script.c_str(), (int)script.length(), RGB(255, 255, 255));

}

//====================================================================================
HRESULT PlHp::init(void)
{
	_FullHp	 = IMAGEMANAGER->addImage(KEY_UI_FULLHP, DIR_UI_FULLHP, 48, 44, true, MAGENTA);
	_HalfHp  = IMAGEMANAGER->addImage(KEY_UI_HALFHP, DIR_UI_HALFHP, 48, 44, true, MAGENTA);
	_EmptyHp = IMAGEMANAGER->addImage(KEY_UI_EMPTYHP, DIR_UI_EMPTYHP, 48, 44, true, MAGENTA);
	
	_Hp_rc = RectMakeCenter(810, 45, _FullHp->getWidth(), _FullHp->getHeight());
	
	count = 0;
	
	return S_OK;
}

void PlHp::release(void)
{
}

void PlHp::update(void)
{
	if (KEYMANAGER->isOnceKeyDown('1'))
	{
		PLAYERINFOMANAGER->setHp(PLAYERINFOMANAGER->getHp() - 1);
	}

	if (KEYMANAGER->isOnceKeyDown('2'))
	{
		PLAYERINFOMANAGER->setHp(PLAYERINFOMANAGER->getHpMax());
	}
}

void PlHp::render(void)
{
	count = PLAYERINFOMANAGER->getHp();
	for (int i = 0; i < PLAYERINFOMANAGER->getHpMax() / 2; i++)
	{
		if (count >= 2)
		{
			_FullHp->render(getMemDC(), _Hp_rc.left - 54 * (PLAYERINFOMANAGER->getHpMax() / 2 - i - 1), _Hp_rc.top);
		}

		else if (count == 1)
		{
			_HalfHp->render(getMemDC(), _Hp_rc.left - 54 * (PLAYERINFOMANAGER->getHpMax() / 2 - i - 1), _Hp_rc.top);
		}

		else
		{
			_EmptyHp->render(getMemDC(), _Hp_rc.left - 54 * (PLAYERINFOMANAGER->getHpMax() / 2 - i - 1), _Hp_rc.top);
		}
		count -= 2;
	}
}

//====================================================================================
HRESULT RhythmNote::init(Scene* _scene)
{
	heart		 = IMAGEMANAGER->addFrameImage(KEY_UI_HEART, DIR_UI_HEART, 164, 104, 2, 1, 2, true, MAGENTA);
	Note_Green	 = IMAGEMANAGER->addImage(KEY_UI_NOTE_GREEN, DIR_UI_NOTE_GREEN, 12, 64, true, MAGENTA);
	Note_Red	 = IMAGEMANAGER->addImage(KEY_UI_NOTE_RED, DIR_UI_NOTE_RED, 12, 64, true, MAGENTA);
		
	Heart_rc	 = RectMakeCenter(WINSIZEX / 2, 470, heart->getFrameWidth(), heart->getFrameHeight());
	HeatBox		 = RectMakeCenter(WINSIZEX / 2, 470, 150, heart->getHeight());

	scene = _scene;

	_turnInterval = scene->getMapInfo()->getTurnInterval();
	_SceneStartTime = TIMEMANAGER->getWorldTime();
	
	_count = 0;

	_animator = new Animator();
	Animation* _anim = new Animation();
	_anim->init(KEY_UI_HEART, POINT{-41, -52}, CHARACTER_STATE::IDLE_RIGHT, true, false, 10);
	_animator->addAnimation(CHARACTER_STATE::IDLE_RIGHT, _anim);

	return S_OK;
}

void RhythmNote::release(void)
{
	_vNote.clear();

	SAFE_RELEASE(_animator);
	SAFE_DELETE(_animator);
}

void RhythmNote::update(void)
{
	_count += TIMEMANAGER->getElapsedTime();
	if (_count > _turnInterval)
	{
		_count -= _turnInterval;
		NoteCreate(0, 470, 1, 8.5f);
		NoteCreate(WINSIZEX, 470, -1, 8.5f);
	}

	NoteMove();
	NoteCollision();
	_animator->update();
}

void RhythmNote::render(void)
{
	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		Rectangle(getMemDC(), HeatBox.left, HeatBox.top, HeatBox.right, HeatBox.bottom);
	}

	Notedraw();
	_animator->animationRender(getMemDC(), POINT{ (Heart_rc.left + Heart_rc.right) / 2, (Heart_rc.top + Heart_rc.bottom) / 2 });
}

void RhythmNote::NoteCreate(float x, float y, float angle, float speed)
{
	tagNote Note;
	ZeroMemory(&Note, sizeof(tagNote));
	if (TIMEMANAGER->getWorldTime() - _SceneStartTime < 150)
	{
		Note.img = Note_Green;
	}

	else
	{
		Note.img = Note_Red;
	}
	
	Note.speed	= speed;
	Note.angle	= angle;
	Note.x = Note.HeartX = x;
	Note.y = Note.HeartY = y;
	Note.rc = RectMakeCenter((int)Note.x, (int)Note.y, Note.img->getWidth(), Note.img->getHeight());

	Note.alpha = 80;

	_vNote.push_back(Note);
}

void RhythmNote::NoteMove(void)
{
	for (_viNote = _vNote.begin(); _viNote != _vNote.end(); ++_viNote)
	{
		_viNote->x += _viNote->angle * _viNote->speed;
		
		_viNote->rc = RectMakeCenter((int)_viNote->x, (int)_viNote->y, _viNote->img->getWidth(), _viNote->img->getHeight());
		
		_viNote->alpha += 5;
		if (_viNote->alpha >= 255)
		{
			_viNote->alpha = 255;
		}
	}
}

void RhythmNote::Notedraw(void)
{
	for (_viNote = _vNote.begin(); _viNote != _vNote.end(); ++_viNote)
	{
		_viNote->img->alphaRender(getMemDC(), _viNote->rc.left, _viNote->rc.top, _viNote->alpha);
	}
}

void RhythmNote::NoteCollision(void)
{
	if (!_vNote.empty())
	{
		RECT rc;
		if (IntersectRect(&rc, &_vNote[0].rc, &Heart_rc))
		{
			removeNote(1);
			removeNote(0);
		}
	}
}

void RhythmNote::removeNote(int arrNum)
{
	if(_vNote.size() > arrNum)
	_vNote.erase(_vNote.begin() + arrNum);
}


//====================================================================================
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

	string script = "x" + to_string(PLAYERINFOMANAGER->getMoney());
	FONTMANAGER->drawText(getMemDC(), 895, 33, "PFStardust", 20, 2000, (char*)script.c_str(), (int)script.length(), RGB(255, 255, 255));
		
	script = "COIN MULTIPLIER : 2";
	FONTMANAGER->drawText(getMemDC(), WINSIZEX / 2 - 100, 520, "PFStardust", 15, 2000, (char*)script.c_str(), (int)script.length(), RGB(255, 255, 255));
	
	/*
	//COIN MULTIPLIER
	script = "";
	if (NoteCount >= 5)
	{
		script = "COIN MULTIPLIER : 1.5";
	}

	if (NoteCount >= 10)
	{
		script = "COIN MULTIPLIER : 2";
	}

	if (NoteCount >= 15)
	{
		script = "COIN MULTIPLIER : 2.5";
	}

	if (NoteCount >= 20)
	{
		script = "COIN MULTIPLIER : 3";
	}
	FONTMANAGER->drawText(getMemDC(), WINSIZEX / 2 - 100, 520, "PFStardust", 15, 2000, (char*)script.c_str(), (int)script.length(), RGB(255, 255, 255));
	*/
}
	
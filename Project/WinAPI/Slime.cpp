#include "Stdafx.h"

#include "Slime.h"

#include "Animation.h"
#include "Animator.h"
#include "Player.h"
#include "Scene.h"

HRESULT Slime::init(Scene* scenePtr, POINT position)
{
	// object.
	destroyed = false;
	type = OBJECT_TYPE::MONSTER_SLIME;
	scene = scenePtr;

	animator = new Animator();
	atk_animator = new Animator;

	// enemy.
	hp = hpMax = 1;
	turnInterval = scene->getMapInfo()->getTurnInterval();
	_rc = RECT{ 0, 0, TILE_SIZE, TILE_SIZE };
	move(position);

	act = true;

	turnCount = 0;
	fieldOfVision = 2;
	atkRange = 1;

	Animation* Idle_Animation = new Animation();
	
	Animation* Attak_left_Animation		= new Animation();
	Animation* Attak_Right_Animation	= new Animation();
	Animation* Attak_Top_Animation		= new Animation();
	Animation* Attak_Bottom_Animation	= new Animation();
	Animation* null_animation			= new Animation();

	Idle_Animation->init( KEY_SLIME_JUMP, POINT{ -26, -80 }, CHARACTER_STATE::IDLE_RIGHT, true, false, 16 );

	Attak_left_Animation->init(KEY_SWIPE_ENEMY_LEFT, POINT{ -70, -50 }, CHARACTER_STATE::ATTACK_LEFT, false, false, 50);
	Attak_Right_Animation->init(KEY_SWIPE_ENEMY_RIGHT, POINT{ 20, -50 }, CHARACTER_STATE::ATTACK_RIGHT, false, false, 50);
	Attak_Top_Animation->init(KEY_SWIPE_ENEMY_TOP, POINT{ -20, -80 }, CHARACTER_STATE::ATTACK_TOP, false, false, 50);
	Attak_Bottom_Animation->init(KEY_SWIPE_ENEMY_BOTTOM, POINT{ -20, 10 }, CHARACTER_STATE::ATTACK_BOTTOM, false, false, 50);

	null_animation->init(KEY_SWIPE_ENEMY_LEFT, POINT{ -54, -48 }, CHARACTER_STATE::IDLE_RIGHT, true, false, 16);

	animator->addAnimation(CHARACTER_STATE::IDLE_RIGHT, Idle_Animation);

	atk_animator->addAnimation(CHARACTER_STATE::ATTACK_LEFT, Attak_left_Animation);
	atk_animator->addAnimation(CHARACTER_STATE::ATTACK_RIGHT, Attak_Right_Animation);
	atk_animator->addAnimation(CHARACTER_STATE::ATTACK_TOP, Attak_Top_Animation);
	atk_animator->addAnimation(CHARACTER_STATE::ATTACK_BOTTOM, Attak_Bottom_Animation);
	atk_animator->addAnimation(CHARACTER_STATE::IDLE_RIGHT, null_animation);

	return S_OK;
}

void Slime::release(void)
{
	SAFE_RELEASE(animator);
	SAFE_DELETE(animator);
	SAFE_RELEASE(atk_animator);
	SAFE_DELETE(atk_animator);
}

void Slime::update(void)
{
	if (atk_animator->isEnd())
	{
		atk_animator->changeAnimation(CHARACTER_STATE::IDLE_RIGHT);
	}

	turnCount += TIMEMANAGER->getElapsedTime();

	distanceX = (float)(scene->getPlayer()->getPos().x - pos.x);
	distanceY = (float)(scene->getPlayer()->getPos().y - pos.y);

	if (turnCount >= turnInterval)
	{
		turnCount -= turnInterval;

		if (!act)
		{
			animator->update();
			atk_animator->update();
			act = true;

			return;
		}

		act = false;

		/*if ((distanceX * distanceX) + (distanceY * distanceY) <= fieldOfVision * fieldOfVision)
		{
			if ((distanceX * distanceX) + (distanceY * distanceY) <= (atkRange * atkRange))
			{
				attackTarget();
			}
		}*/
	}
	animator->update();
	atk_animator->update();
}

void Slime::render(void)
{
	POINT renderPos = GridPointToPixelPointCenter(pos);
	POINT revision = CAMERAMANAGER->getRevision();

	renderPos.x -= revision.x;
	renderPos.y -= revision.y;

	if (KEYMANAGER->isToggleKey(VK_F1))
		Rectangle(getMemDC(),
			_rc.left - revision.x, _rc.top - revision.y,
			_rc.right - revision.x, _rc.bottom - revision.y);

	POINT p = scene->getPlayer()->getPos();
	int distance = abs(p.x - pos.x) + abs(p.y - pos.y);

	if (distance < PLAYERINFOMANAGER->getViewDistance())
	{
		animator->animationRender(getMemDC(), renderPos);
	}

	int count = hp;
	if (hp != hpMax)
		for (int i = 0; i < hpMax; ++i)
		{
			if (count >= 1)
				IMAGEMANAGER->findImage(KEY_UI_MONSTER_HEART_FULL)->
				render(getMemDC(), renderPos.x - 48 + i * 24, renderPos.y - 78);
			else
				IMAGEMANAGER->findImage(KEY_UI_MONSTER_HEART_EMPTY)->
				render(getMemDC(), renderPos.x - 48 + i * 24, renderPos.y - 78);
			--count;
		}

	if (atk_animator->getCurrentState() != CHARACTER_STATE::IDLE_RIGHT)
	{
		atk_animator->animationRender(getMemDC(), renderPos);
	}
}

bool Slime::interact(Player* player)
{
	if (player)	hp--;
	else		hp -= 4;

	if (hp <= 0) destroyed = true;

	return false;
}

void Slime::attackTarget()
{
	PLAYERINFOMANAGER->setHp(PLAYERINFOMANAGER->getHp() - 1);

	//Target Left
	if (scene->getPlayer()->getPos().x - pos.x < 0)
	{
		atk_animator->changeAnimation(CHARACTER_STATE::ATTACK_LEFT);
	}

	//Target right
	if (scene->getPlayer()->getPos().x - pos.x > 0)
	{
		atk_animator->changeAnimation(CHARACTER_STATE::ATTACK_RIGHT);
	}

	//Target top
	if (scene->getPlayer()->getPos().y - pos.y < 0)
	{
		atk_animator->changeAnimation(CHARACTER_STATE::ATTACK_TOP);
	}

	//Target bottom
	if (scene->getPlayer()->getPos().y - pos.y > 0)
	{
		atk_animator->changeAnimation(CHARACTER_STATE::ATTACK_BOTTOM);
	}
}

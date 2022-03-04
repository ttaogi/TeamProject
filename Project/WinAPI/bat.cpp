#include "stdafx.h"

#include "Bat.h"

#include "Animation.h"
#include "Animator.h"
#include "Player.h"
#include "Scene.h"

HRESULT Bat::init(Scene* scenePtr, POINT position)
{
	// object.
	destroyed = false;
	type = OBJECT_TYPE::MONSTER_BAT;
	scene = scenePtr;
	animator = new Animator;
	atk_animator = new Animator;
		
	// enemy.
	hp = hpMax = 4;
	turnInterval = scene->getMapInfo()->getTurnInterval();
	_rc = RECT{ 0, 0, TILE_SIZE, TILE_SIZE };
	Enemy::move(position); 

	posCheck = true;
	act = true;

	turnCount = 0;
	rightCount = 0;
	leftCount = 0;

	fieldOfVision = 4; //인식범위
	atkRange = 1; //공격범위
		
	Animation* Idle_Left_Animation	= new Animation();
	Animation* Idle_Right_Animation = new Animation();

	Animation* Attak_left_Animation		= new Animation();
	Animation* Attak_Right_Animation	= new Animation();
	Animation* Attak_Top_Animation		= new Animation();
	Animation* Attak_Bottom_Animation	= new Animation();
	Animation* null_animation			= new Animation();
		
	Idle_Left_Animation->init(KEY_BAT_LEFT, POINT{ -37, -50 }, CHARACTER_STATE::IDLE_LEFT, true, false, 16);
	Idle_Right_Animation->init(KEY_BAT_RIGHT, POINT{ -37, -50 }, CHARACTER_STATE::IDLE_RIGHT, true, false, 16);

	Attak_left_Animation->init(KEY_SWIPE_ENEMY_LEFT, POINT{ -70, -50 }, CHARACTER_STATE::ATTACK_LEFT, false, false, 16);
	Attak_Right_Animation->init(KEY_SWIPE_ENEMY_RIGHT, POINT{ 20, -50 }, CHARACTER_STATE::ATTACK_RIGHT, false, false, 16);
	Attak_Top_Animation->init(KEY_SWIPE_ENEMY_TOP, POINT{ -20, -80 }, CHARACTER_STATE::ATTACK_TOP, false, false, 16);
	Attak_Bottom_Animation->init(KEY_SWIPE_ENEMY_BOTTOM, POINT{ -20, 10 }, CHARACTER_STATE::ATTACK_BOTTOM, false, false, 16);

	null_animation->init(KEY_SWIPE_ENEMY_LEFT, POINT{ -54, -48 }, CHARACTER_STATE::IDLE_RIGHT, true, false, 16);

	animator->addAnimation(CHARACTER_STATE::IDLE_LEFT, Idle_Left_Animation);
	animator->addAnimation(CHARACTER_STATE::IDLE_RIGHT, Idle_Right_Animation);

	atk_animator->addAnimation(CHARACTER_STATE::ATTACK_LEFT, Attak_left_Animation);
	atk_animator->addAnimation(CHARACTER_STATE::ATTACK_RIGHT, Attak_Right_Animation);
	atk_animator->addAnimation(CHARACTER_STATE::ATTACK_TOP, Attak_Top_Animation);
	atk_animator->addAnimation(CHARACTER_STATE::ATTACK_BOTTOM, Attak_Bottom_Animation);
	atk_animator->addAnimation(CHARACTER_STATE::IDLE_RIGHT, null_animation);
	
	return S_OK;
}

void Bat::release(void)
{
	SAFE_RELEASE(animator);
	SAFE_DELETE(animator);
	SAFE_RELEASE(atk_animator);
	SAFE_DELETE(atk_animator);
}

void Bat::update(void)
{
	if (atk_animator->isEnd())
	{
		atk_animator->changeAnimation(CHARACTER_STATE::IDLE_RIGHT);
	}
	
	turnCount += TIMEMANAGER->getElapsedTime();
	
	distanceX = scene->getPlayer()->getPos().x - pos.x;
	distanceY = scene->getPlayer()->getPos().y - pos.y;
	
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

		if ((distanceX * distanceX) + (distanceY * distanceY) <= fieldOfVision * fieldOfVision)
		{
			faceTarget(); //타겟 바라보기

			if ((distanceX * distanceX) + (distanceY * distanceY) <= (atkRange * atkRange)) //타겟과의 거리가 범위보다 작을때
			{
				attackTarget();
			}

			else
			{
				if (animator->getCurrentState() != CHARACTER_STATE::ATTACK_LEFT
					&& animator->getCurrentState() != CHARACTER_STATE::ATTACK_RIGHT
					&& animator->getCurrentState() != CHARACTER_STATE::ATTACK_TOP
					&& animator->getCurrentState() != CHARACTER_STATE::ATTACK_BOTTOM) //공격애니메이션이 아닐때 추적
				{
					movetoTarget();
				}
			}
		}

		else //시야범위 밖에 있을때 Idle 상태
		{
			move();
		}		

	}
		
	animator->update();
	atk_animator->update();
}

void Bat::render(void)
{
	POINT renderPos = GridPointToPixelPointCenter(pos);
	POINT revision = CAMERAMANAGER->getRevision();

	renderPos.x -= revision.x;
	renderPos.y -= revision.y;

	if (KEYMANAGER->isToggleKey(VK_F1))
		Rectangle(getMemDC(),
			_rc.left - revision.x, _rc.top - revision.y,
			_rc.right - revision.x, _rc.bottom - revision.y);

	animator->animationRender(getMemDC(), renderPos);
	
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

bool Bat::interact(Player* player)
{
	if (player)	hp--;
	else		hp -= 4;

	if (hp <= 0) destroyed = true;

	return false;
}

void Bat::move(void)
{
	if (animator->isEnd())
		animator->changeAnimation(CHARACTER_STATE::IDLE_RIGHT);

	if (posCheck)
	{
		POINT search = POINT{ pos.x + 1, pos.y };
		Object* obj = scene->getObject(search);

		if (!obj &&
			(scene->getPlayer()->getPos().x != search.x ||
				scene->getPlayer()->getPos().y != search.y))
		{
			pos.x += 1;
		}
		
		animator->changeAnimation(CHARACTER_STATE::IDLE_RIGHT);
			
		rightCount++;

		if(rightCount == 3)
		{
			leftCount = 0;
			posCheck = false;
		}
	}

	if (!posCheck)
	{
		POINT search = POINT{ pos.x - 1, pos.y };
		Object* obj = scene->getObject(search);

		if (!obj &&
			(scene->getPlayer()->getPos().x != search.x ||
				scene->getPlayer()->getPos().y != search.y))
		{
			pos.x -= 1;
		}

		animator->changeAnimation(CHARACTER_STATE::IDLE_LEFT);
		
		leftCount++;
		if (leftCount == 3)
		{
			rightCount = 0;
			posCheck = true;
		}
		
	}

	_rc = RectMakeCenter(pos.x * TILE_SIZE + TILE_SIZE / 2, pos.y * TILE_SIZE + TILE_SIZE / 2, TILE_SIZE, TILE_SIZE);

	
}

void Bat::movetoTarget()
{
	if (distanceX * distanceX > distanceY * distanceY)
	{
		//Target Left
		if (scene->getPlayer()->getPos().x - pos.x < 0)
		{
			POINT search = POINT{ pos.x - 1, pos.y };
			Object* obj = scene->getObject(search);

			if (!obj && 
				(scene->getPlayer()->getPos().x != search.x ||
				scene->getPlayer()->getPos().y != search.y))
			{
				pos.x -= 1;
			}
		}

		//Target right
		else if (scene->getPlayer()->getPos().x - pos.x > 0)
		{
			POINT search = POINT{ pos.x + 1, pos.y };
			Object* obj = scene->getObject(search);

			if (!obj &&
				(scene->getPlayer()->getPos().x != search.x ||
					scene->getPlayer()->getPos().y != search.y))
			{
				pos.x += 1;
			}
		}
	}

	else
	{
		//Target top
		if (scene->getPlayer()->getPos().y - pos.y < 0)
		{
			POINT search = POINT{ pos.x, pos.y - 1 };
			Object* obj = scene->getObject(search);

			if (!obj &&
				(scene->getPlayer()->getPos().x != search.x ||
					scene->getPlayer()->getPos().y != search.y))
			{
				pos.y -= 1;
			}
		}

		//Target bottom
		else if (scene->getPlayer()->getPos().y - pos.y > 0)
		{
			POINT search = POINT{ pos.x, pos.y + 1 };
			Object* obj = scene->getObject(search);

			if (!obj &&
				(scene->getPlayer()->getPos().x != search.x ||
					scene->getPlayer()->getPos().y != search.y))
			{
				pos.y += 1;
			}
		}
	}
}

void Bat::faceTarget()
{
	//Target Left
	if (scene->getPlayer()->getPos().x - pos.x < 0)
	{
		animator->changeAnimation(CHARACTER_STATE::IDLE_LEFT);
	}

	//Target right
	if (scene->getPlayer()->getPos().x - pos.x > 0)
	{
		animator->changeAnimation(CHARACTER_STATE::IDLE_RIGHT);
	}
}

void Bat::attackTarget()
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

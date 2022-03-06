#include "stdafx.h"

#include "Bat.h"

#include "Animation.h"
#include "Animator.h"
#include "Money.h"
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

	fieldOfVision = 4;
	atkRange = 1;
		
	Animation* Idle_Left_Animation	= new Animation();
	Animation* Idle_Right_Animation = new Animation();

	Animation* Attak_left_Animation		= new Animation();
	Animation* Attak_Right_Animation	= new Animation();
	Animation* Attak_Top_Animation		= new Animation();
	Animation* Attak_Bottom_Animation	= new Animation();
	Animation* null_animation			= new Animation();
		
	Idle_Left_Animation->init(KEY_BAT_LEFT, POINT{ -37, -50 }, CHARACTER_STATE::IDLE_LEFT, true, false, 16);
	Idle_Right_Animation->init(KEY_BAT_RIGHT, POINT{ -37, -50 }, CHARACTER_STATE::IDLE_RIGHT, true, false, 16);

	Attak_left_Animation->init(KEY_SWIPE_ENEMY_LEFT, POINT{ -70, -50 }, CHARACTER_STATE::ATTACK_LEFT, false, false, 50);
	Attak_Right_Animation->init(KEY_SWIPE_ENEMY_RIGHT, POINT{ 20, -50 }, CHARACTER_STATE::ATTACK_RIGHT, false, false, 50);
	Attak_Top_Animation->init(KEY_SWIPE_ENEMY_TOP, POINT{ -20, -80 }, CHARACTER_STATE::ATTACK_TOP, false, false, 50);
	Attak_Bottom_Animation->init(KEY_SWIPE_ENEMY_BOTTOM, POINT{ -20, 10 }, CHARACTER_STATE::ATTACK_BOTTOM, false, false, 50);

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
		atk_animator->changeAnimation(CHARACTER_STATE::IDLE_RIGHT);
	
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
			faceTarget();

			if ((distanceX * distanceX) + (distanceY * distanceY) <= (atkRange * atkRange))
				attackTarget();
			else if (animator->getCurrentState() != CHARACTER_STATE::ATTACK_LEFT && 
				animator->getCurrentState() != CHARACTER_STATE::ATTACK_RIGHT &&
				animator->getCurrentState() != CHARACTER_STATE::ATTACK_TOP &&
				animator->getCurrentState() != CHARACTER_STATE::ATTACK_BOTTOM)
				movetoTarget();
		}
		else 
			move();
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

	POINT p = scene->getPlayer()->getPos();
	int distance = abs(p.x - pos.x) + abs(p.y - pos.y);

	if (distance < PLAYERINFOMANAGER->getViewDistance())
		animator->animationRender(getMemDC(), renderPos);

	int count = hp;
	if (hp != hpMax)
		for (int i = 0; i < hpMax; ++i)
		{
			if (count >= 1)
				IMAGEMANAGER->findImage(KEY_UI_MONSTER_HEART_FULL)->render(getMemDC(), renderPos.x - (24 * hpMax / 2) + i * 24, renderPos.y - 78);
			else
				IMAGEMANAGER->findImage(KEY_UI_MONSTER_HEART_EMPTY)->render(getMemDC(), renderPos.x - (24 * hpMax / 2) + i * 24, renderPos.y - 78);

			--count;
		}

	if (atk_animator->getCurrentState() != CHARACTER_STATE::IDLE_RIGHT)
		atk_animator->animationRender(getMemDC(), renderPos);
}

bool Bat::interact(Player* player)
{
	if (player)	hp -= PLAYERINFOMANAGER->getAttack().atk;
	else		hp -= 4;

	if (hp <= 0)
	{
		destroyed = true;
		SOUNDMANAGER->play(KEY_EN_BAT_DEATH, DEFAULT_VOLUME);
		Money* m = new Money();
		m->init(scene, pos);
		m->setQuantity(RND->getFromIntTo(1, 30));
		scene->getObjectVec()->push_back(m);
	}
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

		//if (!obj && (scene->getPlayer()->getPos().x != search.x || scene->getPlayer()->getPos().y != search.y))
		if (!obj && !PointCmp(scene->getPlayer()->getPos(), search))
			pos.x += 1;
		
		animator->changeAnimation(CHARACTER_STATE::IDLE_RIGHT);
		
		if(++rightCount == 3)
		{
			leftCount = 0;
			posCheck = false;
		}
	}
	else
	{
		POINT search = POINT{ pos.x - 1, pos.y };
		Object* obj = scene->getObject(search);

		if (!obj && !PointCmp(scene->getPlayer()->getPos(), search))
			pos.x -= 1;

		animator->changeAnimation(CHARACTER_STATE::IDLE_LEFT);
		
		if (++leftCount == 3)
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
		if (scene->getPlayer()->getPos().x - pos.x < 0) //Target Left
		{
			POINT search = POINT{ pos.x - 1, pos.y };
			Object* obj = scene->getObject(search);

			if (!obj && !PointCmp(scene->getPlayer()->getPos(), search))
				pos.x -= 1;
		}
		else if (scene->getPlayer()->getPos().x - pos.x > 0) //Target right
		{
			POINT search = POINT{ pos.x + 1, pos.y };
			Object* obj = scene->getObject(search);

			if (!obj && !PointCmp(scene->getPlayer()->getPos(), search))
				pos.x += 1;
		}
	}
	else
	{
		if (scene->getPlayer()->getPos().y - pos.y < 0) //Target top
		{
			POINT search = POINT{ pos.x, pos.y - 1 };
			Object* obj = scene->getObject(search);

			if (!obj && !PointCmp(scene->getPlayer()->getPos(), search))
				pos.y -= 1;
		}
		else if (scene->getPlayer()->getPos().y - pos.y > 0) //Target bottom
		{
			POINT search = POINT{ pos.x, pos.y + 1 };
			Object* obj = scene->getObject(search);

			if (!obj && !PointCmp(scene->getPlayer()->getPos(), search))
				pos.y += 1;
		}
	}
}

void Bat::faceTarget()
{
	if (scene->getPlayer()->getPos().x - pos.x < 0) //Target Left
		animator->changeAnimation(CHARACTER_STATE::IDLE_LEFT);
	else if (scene->getPlayer()->getPos().x - pos.x > 0) //Target right
		animator->changeAnimation(CHARACTER_STATE::IDLE_RIGHT);
}

void Bat::attackTarget()
{
	PLAYERINFOMANAGER->isAttacked(1);
	SOUNDMANAGER->play(KEY_EN_BAT_ATTACK, DEFAULT_VOLUME);

	if (scene->getPlayer()->getPos().x - pos.x < 0) //Target Left
		atk_animator->changeAnimation(CHARACTER_STATE::ATTACK_LEFT);
	else if (scene->getPlayer()->getPos().x - pos.x > 0) //Target right
		atk_animator->changeAnimation(CHARACTER_STATE::ATTACK_RIGHT);
	else if (scene->getPlayer()->getPos().y - pos.y < 0) //Target top
		atk_animator->changeAnimation(CHARACTER_STATE::ATTACK_TOP);
	else if (scene->getPlayer()->getPos().y - pos.y > 0) //Target bottom
		atk_animator->changeAnimation(CHARACTER_STATE::ATTACK_BOTTOM);
}

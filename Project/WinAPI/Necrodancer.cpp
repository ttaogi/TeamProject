#include "stdafx.h"

#include "Necrodancer.h"

#include "Animation.h"
#include "Animator.h"
#include "Effect.h"
#include "Player.h"
#include "Scene.h"
#include "skeleton.h"

const int GLOBAL_COOL = 3;
const int SUMMON_COOL = 2;
const int FREEZE_COOL = 4;
const int EXPLOSION_COOL = 6;

HRESULT Necrodancer::init(Scene* scenePtr, POINT position)
{
	// object.
	destroyed = false;
	type = OBJECT_TYPE::MONSTER_NECRODANCER;
	animator = new Animator();
	scene = scenePtr;
	// enemy.
	hp = hpMax = 6;
	turnInterval = scene->getMapInfo()->getTurnInterval();
	_rc = RECT{ 0, 0, TILE_SIZE, TILE_SIZE };
	move(position);
	// Necrodancer.
	turnCount = 0;
	globalCool = GLOBAL_COOL;
	summonCool = SUMMON_COOL;
	freezeCool = FREEZE_COOL;
	explosionCool = EXPLOSION_COOL;

	{ // animation.
		Animation* necrodancerRightIdle = new Animation();
		necrodancerRightIdle->init(
			KEY_NECRODANCER_RIGHT_IDLE,
			POINT{ -45, -100 }, CHARACTER_STATE::IDLE_RIGHT,
			true, false, 16
		);

		Animation* necrodancerRightUpJump = new Animation();
		necrodancerRightUpJump->init(
			KEY_NECRODANCER_RIGHT_UP_JUMP,
			POINT{ -90, -90 }, CHARACTER_STATE::RIGHT_UP_JUMP,
			false, false, 16
		);

		Animation* necrodancerRightDownJump = new Animation();
		necrodancerRightDownJump->init(
			KEY_NECRODANCER_RIGHT_DOWN_JUMP,
			POINT{ -90, -140 }, CHARACTER_STATE::RIGHT_DOWN_JUMP,
			false, false, 16
		);

		Animation* necrodancerLeftIdle = new Animation();
		necrodancerLeftIdle->init(
			KEY_NECRODANCER_LEFT_IDLE,
			POINT{ -43, -100 }, CHARACTER_STATE::IDLE_LEFT,
			true, false, 16
		);

		Animation* necrodancerLeftUpJump = new Animation();
		necrodancerLeftUpJump->init(
			KEY_NECRODANCER_LEFT_UP_JUMP,
			POINT{ -90, -90 }, CHARACTER_STATE::LEFT_UP_JUMP,
			false, false, 16
		);

		Animation* necrodancerLeftDownJump = new Animation();
		necrodancerLeftDownJump->init(
			KEY_NECRODANCER_LEFT_DOWN_JUMP,
			POINT{ -85, -140 }, CHARACTER_STATE::LEFT_DOWN_JUMP,
			false, false, 16
		);

		Animation* necrodancerExplosionIdle = new Animation();
		necrodancerExplosionIdle->init(
			KEY_NECRODANCER_EXPLOSION_IDLE,
			POINT{ -45, -100 }, CHARACTER_STATE::EXPLOSION_IDLE,
			false, false, 16
		);

		Animation* necrodancerExplosion = new Animation();
		necrodancerExplosion->init(
			KEY_NECRODANCER_EXPLOSION,
			POINT{ -45, -100 }, CHARACTER_STATE::EXPLOSION,
			false, false, 16
		);

		Animation* necrodancerRightBuleATT = new Animation();
		necrodancerRightBuleATT->init(
			KEY_NECRODANCER_RIGHT_BLUEATT,
			POINT{ -45, -100 }, CHARACTER_STATE::RIGHT_BLUEATT,
			false, false, 16
		);

		Animation* necrodancerLeftBuleATT = new Animation();
		necrodancerLeftBuleATT->init(
			KEY_NECRODANCER_LEFT_BLUEATT,
			POINT{ -42, -100 }, CHARACTER_STATE::LEFT_BLUEATT,
			false, false, 16
		);

		Animation* necrodancerSohwanIdle = new Animation();
		necrodancerSohwanIdle->init(
			KEY_NECRODANCER_SOHWAN_IDLE,
			POINT{ -45, -100 }, CHARACTER_STATE::SOHWAN_IDLE,
			false, false, 16
		);

		/*Animation* necrodancerIdle2 = new Animation();
		necrodancerIdle2->init(
			KEY_NECRODANCER_IDLE2,
			POINT{ -45, -100 }, CHARACTER_STATE::IDLE2,
			true, false, 16
		);*/

		animator->addAnimation(CHARACTER_STATE::IDLE_RIGHT, necrodancerRightIdle);
		animator->addAnimation(CHARACTER_STATE::RIGHT_UP_JUMP, necrodancerRightUpJump);
		animator->addAnimation(CHARACTER_STATE::RIGHT_DOWN_JUMP, necrodancerRightDownJump);

		animator->addAnimation(CHARACTER_STATE::IDLE_LEFT, necrodancerLeftIdle);
		animator->addAnimation(CHARACTER_STATE::LEFT_UP_JUMP, necrodancerLeftUpJump);
		animator->addAnimation(CHARACTER_STATE::LEFT_DOWN_JUMP, necrodancerLeftDownJump);

		animator->addAnimation(CHARACTER_STATE::EXPLOSION_IDLE, necrodancerExplosionIdle);
		animator->addAnimation(CHARACTER_STATE::EXPLOSION, necrodancerExplosion);

		animator->addAnimation(CHARACTER_STATE::RIGHT_BLUEATT, necrodancerRightBuleATT);
		animator->addAnimation(CHARACTER_STATE::LEFT_BLUEATT, necrodancerLeftBuleATT);

		animator->addAnimation(CHARACTER_STATE::SOHWAN_IDLE, necrodancerSohwanIdle);
		///animator->addAnimation(CHARACTER_STATE::IDLE2, necrodancerIdle2);
	}

	return S_OK;
}

void Necrodancer::release(void)
{
	SAFE_RELEASE(animator);
	SAFE_DELETE(animator);
}

void Necrodancer::update(void)
{
	turnCount += TIMEMANAGER->getElapsedTime();

	if (animator->isEnd())
	{
		CHARACTER_STATE animState = animator->getCurrentState();
		Skeleton* skeleton = NULL;

		switch (animState)
		{
		case CHARACTER_STATE::EXPLOSION_IDLE:
			animator->changeAnimation(CHARACTER_STATE::EXPLOSION);
			break;
		case CHARACTER_STATE::EXPLOSION:
			explosion();
			animator->changeAnimation(CHARACTER_STATE::IDLE_RIGHT);
			break;
		case CHARACTER_STATE::SOHWAN_IDLE:
			summon();
			animator->changeAnimation(CHARACTER_STATE::IDLE_LEFT);
			break;
		case CHARACTER_STATE::LEFT_BLUEATT:
			freeze();
			animator->changeAnimation(CHARACTER_STATE::IDLE_LEFT);
			break;
		case CHARACTER_STATE::RIGHT_BLUEATT:
			freeze();
			animator->changeAnimation(CHARACTER_STATE::IDLE_RIGHT);
			break;
		case CHARACTER_STATE::LEFT_UP_JUMP:
		case CHARACTER_STATE::LEFT_DOWN_JUMP:
			animator->changeAnimation(CHARACTER_STATE::IDLE_LEFT);
			break;
		case CHARACTER_STATE::RIGHT_UP_JUMP:
		case CHARACTER_STATE::RIGHT_DOWN_JUMP:
		default:
			animator->changeAnimation(CHARACTER_STATE::IDLE_RIGHT);
			break;
		}
	}

	if (turnCount >= turnInterval)
	{
		turnCount -= turnInterval;

		CHARACTER_STATE animState = animator->getCurrentState();

		if (animState == CHARACTER_STATE::EXPLOSION_IDLE ||
			animState == CHARACTER_STATE::EXPLOSION ||
			animState == CHARACTER_STATE::SOHWAN_IDLE)
		{
			animator->update();
			return;
		}

		if (globalCool > 0)
		{
			--globalCool;
			moveRandom();
		}
		else
		{
			if (summonCool <= 0)
			{
				summonCool = SUMMON_COOL;
				globalCool = GLOBAL_COOL;
				animator->changeAnimation(CHARACTER_STATE::SOHWAN_IDLE);
			}
			else if (freezeCool <= 0)
			{
				freezeCool = FREEZE_COOL;
				globalCool = GLOBAL_COOL;
				animator->changeAnimation(CHARACTER_STATE::RIGHT_BLUEATT);
			}
			else if (explosionCool <= 0)
			{
				explosionCool = EXPLOSION_COOL;
				globalCool = GLOBAL_COOL;
				animator->changeAnimation(CHARACTER_STATE::EXPLOSION_IDLE);
			}
			else
			{
				moveRandom();
			}

			--summonCool;
			--freezeCool;
			--explosionCool;
		}
	}

	animator->update();
}

void Necrodancer::moveRandom()
{
	int dir = RND->getInt(6);
	POINT searchPos = POINT{ 0, 0 };
	POINT playerPos = scene->getPlayer()->getPos();
	Object* searchObj = NULL;

	switch (dir)
	{
	case 0:
		searchPos = POINT{ pos.x + 1, pos.y - 1 };
		searchObj = scene->getObject(searchPos);
		if (!searchObj && !PointCmp(searchPos, playerPos))
		{
			animator->changeAnimation(CHARACTER_STATE::RIGHT_UP_JUMP);
			move(searchPos);
		}
		break;
	case 1:
		searchPos = POINT{ pos.x + 1, pos.y + 1 };
		searchObj = scene->getObject(searchPos);
		if (!searchObj && !PointCmp(searchPos, playerPos))
		{
			animator->changeAnimation(CHARACTER_STATE::RIGHT_DOWN_JUMP);
			move(searchPos);
		}
		break;
	case 2:
		searchPos = POINT{ pos.x - 1, pos.y + 1 };
		searchObj = scene->getObject(searchPos);
		if (!searchObj && !PointCmp(searchPos, playerPos))
		{
			animator->changeAnimation(CHARACTER_STATE::LEFT_DOWN_JUMP);
			move(searchPos);
		}
		break;
	case 3:
		searchPos = POINT{ pos.x - 1, pos.y - 1 };
		searchObj = scene->getObject(searchPos);
		if (!searchObj && !PointCmp(searchPos, playerPos))
		{
			animator->changeAnimation(CHARACTER_STATE::LEFT_UP_JUMP);
			move(searchPos);
		}
		break;
	default:
		break;
	}
}

void Necrodancer::summon()
{
	POINT playerPos = scene->getPlayer()->getPos();

	while(true)
	{
		int x = RND->getFromIntTo(1, 15);
		int y = RND->getFromIntTo(6, 15);
		POINT searchPos = POINT{ x, y };
		Object* searchObj = NULL;

		if (playerPos.x == x && playerPos.y == y)
			continue;

		searchObj = scene->getObject(searchPos);

		if (searchObj)
			continue;

		Skeleton* skeleton = new Skeleton();
		if (SUCCEEDED(skeleton->init(scene, searchPos)))
		{
			scene->getObjectVec()->push_back(skeleton);
			break;
		}
		else
		{
			SAFE_RELEASE(skeleton);
			SAFE_DELETE(skeleton);
		}
	}
}

void Necrodancer::freeze()
{
	IceBlast* ice = new IceBlast();
	ice->init(scene, pos);
	scene->getEffectVec()->push_back(ice);

	POINT playerPos = scene->getPlayer()->getPos();
	if (playerPos.x >= pos.x - 3 && playerPos.x <= pos.x + 3 &&
		playerPos.y >= pos.y - 3 && playerPos.y <= pos.y + 3)
	{
		PLAYERINFOMANAGER->setHp(PLAYERINFOMANAGER->getHp() - 1);
	}
}

void Necrodancer::explosion()
{
	Explosion55* expl = new Explosion55();
	expl->init(scene, pos);
	scene->getEffectVec()->push_back(expl);

	POINT playerPos = scene->getPlayer()->getPos();
	if (playerPos.x >= pos.x - 2 && playerPos.x <= pos.x + 2 &&
		playerPos.y >= pos.y - 2 && playerPos.y <= pos.y + 2)
	{
		PLAYERINFOMANAGER->setHp(PLAYERINFOMANAGER->getHp() - 1);
	}
}

void Necrodancer::render(void)
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
			if(count >= 1)
				IMAGEMANAGER->findImage(KEY_UI_MONSTER_HEART_FULL)->
					render(getMemDC(), renderPos.x - 48 + i * 24, renderPos.y - 78);
			else
				IMAGEMANAGER->findImage(KEY_UI_MONSTER_HEART_EMPTY)->
					render(getMemDC(), renderPos.x - 48 + i * 24, renderPos.y - 78);
			--count;
		}
}

bool Necrodancer::interact(Player* player)
{
	if (player && PLAYERINFOMANAGER->getAttack().detailType == ITEM_DETAIL::ATTACK_GOLDENLUTE)
		--hp;

	if (hp <= 0)
	{
		Object* obj = NULL;

		for (int i = 6; i <= 10; ++i)
		{
			obj = NULL;
			obj = scene->getObject(POINT{ i, 5 });
			if (obj)
				obj->setDestroyed(true);
		}

		destroyed = true;

		vector<Object*>* objectVec = scene->getObjectVec();

		for (auto iter = objectVec->begin(); iter != objectVec->end(); ++iter)
		{
			OBJECT_TYPE type = (*iter)->getType();
			if (type == OBJECT_TYPE::MONSTER_BAT ||
				type == OBJECT_TYPE::MONSTER_SKELETON ||
				type == OBJECT_TYPE::MONSTER_SLIME ||
				type == OBJECT_TYPE::MONSTER_SLIME_BLUE)
			{
				(*iter)->setDestroyed(true);
			}
		}
	}
	else
	{
		POINT playerPos = scene->getPlayer()->getPos();

		while (true)
		{
			int x = RND->getFromIntTo(1, 15);
			int y = RND->getFromIntTo(6, 15);
			POINT searchPos = POINT{ x, y };
			Object* searchObj = NULL;

			if (playerPos.x == x && playerPos.y == y)
				continue;

			searchObj = scene->getObject(searchPos);

			if (!searchObj)
				continue;

			move(searchPos);
			break;
		}
	}
	
	return false;
}

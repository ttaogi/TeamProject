#include "Stdafx.h"

#include "Player.h"

#include "Animation.h"
#include "Animator.h"
#include "Scene.h"
#include "Wall.h"
#include "Explosion.h"
#include "GameUI.h"

HRESULT Player::init(Scene* scenePtr)
{
	initTime = TIMEMANAGER->getWorldTime();
	turnCount = 0;
	turnInterval = scenePtr->getMapInfo()->getTurnInterval();
	command = DIRECTION::DIRECTION_NUM;
	bounce = DIRECTION::DIRECTION_NUM;
	Move(POINT{ 0, 0 });
	scene = scenePtr;
	minimapStripe = IMAGEMANAGER->findImage(KEY_PLAYER_MINIMAP);
	effectCountIndex = 0;
	DaggerEffectRightTF = false;

	{ // animation.
		headAnimator = new Animator();
		bodyAnimator = new Animator();

		Animation* headIdleRight = new Animation();
		Animation* bodyIdleRight = new Animation();
		Animation* headJumpRight = new Animation();
		Animation* bodyJumpRight = new Animation();

		Animation* headIdleLeft = new Animation();
		Animation* bodyIdleLeft = new Animation();
		Animation* headJumpLeft = new Animation();
		Animation* bodyJumpLeft = new Animation();

		Animation* headJumpTop = new Animation();
		Animation* bodyJumpTop = new Animation();
		Animation* headJumpBottom = new Animation();
		Animation* bodyJumpBottom = new Animation();

		headIdleRight->init(
			KEY_PLAYER_HEAD_IDLE_RIGHT,
			POINT{ -24, -44 }, CHARACTER_STATE::IDLE_RIGHT,
			true, false, 16
		);
		bodyIdleRight->init(
			KEY_PLAYER_BODY_IDLE_RIGHT,
			POINT{ -24, -24 }, CHARACTER_STATE::IDLE_RIGHT,
			true, false, 16
		);
		headJumpRight->init(
			KEY_PLAYER_HEAD_JUMP_RIGHT,
			POINT{ -72, -68 }, CHARACTER_STATE::JUMP_RIGHT,
			false, false, 64
		);
		bodyJumpRight->init(
			KEY_PLAYER_BODY_JUMP_RIGHT,
			POINT{ -72, -48 }, CHARACTER_STATE::JUMP_RIGHT,
			false, false, 64
		);

		headIdleLeft->init(
			KEY_PLAYER_HEAD_IDLE_LEFT,
			POINT{ -24, -44 }, CHARACTER_STATE::IDLE_LEFT,
			true, false, 16
		);
		bodyIdleLeft->init(
			KEY_PLAYER_BODY_IDLE_LEFT,
			POINT{ -24, -24 }, CHARACTER_STATE::IDLE_LEFT,
			true, false, 16
		);
		headJumpLeft->init(
			KEY_PLAYER_HEAD_JUMP_LEFT,
			POINT{ -24, -68 }, CHARACTER_STATE::JUMP_LEFT,
			false, false, 64
		);
		bodyJumpLeft->init(
			KEY_PLAYER_BODY_JUMP_LEFT,
			POINT{ -24, -48 }, CHARACTER_STATE::JUMP_LEFT,
			false, false, 64
		);

		headJumpTop->init(
			KEY_PLAYER_HEAD_JUMP_TOP,
			POINT{ -24, -44 }, CHARACTER_STATE::JUMP_TOP,
			false, false, 64
		);
		bodyJumpTop->init(
			KEY_PLAYER_BODY_JUMP_TOP,
			POINT{ -24, -24 }, CHARACTER_STATE::JUMP_TOP,
			false, false, 64
		);
		headJumpBottom->init(
			KEY_PLAYER_HEAD_JUMP_BOTTOM,
			POINT{ -24, -92 }, CHARACTER_STATE::JUMP_BOTTOM,
			false, false, 64
		);
		bodyJumpBottom->init(
			KEY_PLAYER_BODY_JUMP_BOTTOM,
			POINT{ -24, -72 }, CHARACTER_STATE::JUMP_BOTTOM,
			false, false, 64
		);

		headAnimator->addAnimation(CHARACTER_STATE::IDLE_RIGHT, headIdleRight);
		bodyAnimator->addAnimation(CHARACTER_STATE::IDLE_RIGHT, bodyIdleRight);
		headAnimator->addAnimation(CHARACTER_STATE::IDLE_LEFT, headIdleLeft);
		bodyAnimator->addAnimation(CHARACTER_STATE::IDLE_LEFT, bodyIdleLeft);

		headAnimator->addAnimation(CHARACTER_STATE::JUMP_RIGHT, headJumpRight);
		bodyAnimator->addAnimation(CHARACTER_STATE::JUMP_RIGHT, bodyJumpRight);
		headAnimator->addAnimation(CHARACTER_STATE::JUMP_LEFT, headJumpLeft);
		bodyAnimator->addAnimation(CHARACTER_STATE::JUMP_LEFT, bodyJumpLeft);

		headAnimator->addAnimation(CHARACTER_STATE::JUMP_TOP, headJumpTop);
		bodyAnimator->addAnimation(CHARACTER_STATE::JUMP_TOP, bodyJumpTop);
		headAnimator->addAnimation(CHARACTER_STATE::JUMP_BOTTOM, headJumpBottom);
		bodyAnimator->addAnimation(CHARACTER_STATE::JUMP_BOTTOM, bodyJumpBottom);

	}

	return S_OK;
}

void Player::release(void)
{
	SAFE_RELEASE(headAnimator);
	SAFE_DELETE(headAnimator);
	SAFE_RELEASE(bodyAnimator);
	SAFE_DELETE(bodyAnimator);
}

void Player::update(void)
{
	turnCount += TIMEMANAGER->getElapsedTime();
	if (turnCount >= 0.5f)
	{
		effectCountIndex++;
		turnCount -= 0.5f;
	}

	// non-idle animation -> idle animation.
	if (headAnimator->isEnd() && bodyAnimator->isEnd())
	{
		if (bounce != DIRECTION::DIRECTION_NUM)
		{
			POINT searchPos;
			Object* searchObj = NULL;
			switch (bounce)
			{
			case DIRECTION::LEFT:
				searchPos = POINT{ pos.x - 1, pos.y };
				searchObj = scene->getObject(searchPos);
				if (!searchObj)
				{
					Move(searchPos);
					headAnimator->changeAnimation(CHARACTER_STATE::JUMP_LEFT);
					bodyAnimator->changeAnimation(CHARACTER_STATE::JUMP_LEFT);
				}
				break;
			case DIRECTION::TOP:
				searchPos = POINT{ pos.x, pos.y - 1 };
				searchObj = scene->getObject(searchPos);
				if (!searchObj)
				{
					Move(searchPos);
					headAnimator->changeAnimation(CHARACTER_STATE::JUMP_TOP);
					bodyAnimator->changeAnimation(CHARACTER_STATE::JUMP_TOP);
				}
				break;
			case DIRECTION::RIGHT:
				searchPos = POINT{ pos.x + 1, pos.y };
				searchObj = scene->getObject(searchPos);
				if (!searchObj)
				{
					Move(searchPos);
					headAnimator->changeAnimation(CHARACTER_STATE::JUMP_RIGHT);
					bodyAnimator->changeAnimation(CHARACTER_STATE::JUMP_RIGHT);
				}
				break;
			case DIRECTION::BOTTOM:
				searchPos = POINT{ pos.x, pos.y + 1};
				searchObj = scene->getObject(searchPos);
				if (!searchObj)
				{
					Move(searchPos);
					headAnimator->changeAnimation(CHARACTER_STATE::JUMP_BOTTOM);
					bodyAnimator->changeAnimation(CHARACTER_STATE::JUMP_BOTTOM);
				}
				break;
			}
			bounce = DIRECTION::DIRECTION_NUM;
		}
		else
		{
			if (headAnimator->getCurrentState() == CHARACTER_STATE::JUMP_RIGHT)
			{
				headAnimator->changeAnimation(CHARACTER_STATE::IDLE_RIGHT);
				bodyAnimator->changeAnimation(CHARACTER_STATE::IDLE_RIGHT);
			}
			if (headAnimator->getCurrentState() == CHARACTER_STATE::JUMP_LEFT)
			{
				headAnimator->changeAnimation(CHARACTER_STATE::IDLE_LEFT);
				bodyAnimator->changeAnimation(CHARACTER_STATE::IDLE_LEFT);
			}
			if (headAnimator->getCurrentState() == CHARACTER_STATE::JUMP_TOP)
			{
				headAnimator->changeAnimation(CHARACTER_STATE::IDLE_RIGHT);
				bodyAnimator->changeAnimation(CHARACTER_STATE::IDLE_RIGHT);
			}
			if (headAnimator->getCurrentState() == CHARACTER_STATE::JUMP_BOTTOM)
			{
				headAnimator->changeAnimation(CHARACTER_STATE::IDLE_LEFT);
				bodyAnimator->changeAnimation(CHARACTER_STATE::IDLE_LEFT);
			}
		}
	}

	// get command.
	if (turnCount >= turnInterval * 0.7f && turnCount < turnInterval * 0.8f)
	{ // bad timing.
		if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
			command = DIRECTION::LEFT;
		else if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
			command = DIRECTION::RIGHT;
		else if (KEYMANAGER->isOnceKeyDown(VK_UP))
			command = DIRECTION::TOP;
		else if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
			command = DIRECTION::BOTTOM;
	}
	else if (turnCount >= turnInterval * 0.8f && turnCount < turnInterval)
	{ // perfect timing.
		if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
			command = DIRECTION::LEFT;
		else if(KEYMANAGER->isOnceKeyDown(VK_RIGHT))
			command = DIRECTION::RIGHT;
		else if(KEYMANAGER->isOnceKeyDown(VK_UP))
			command = DIRECTION::TOP;
		else if(KEYMANAGER->isOnceKeyDown(VK_DOWN))
			command = DIRECTION::BOTTOM;
	}
	else if (turnCount >= turnInterval)
	{ // execute command.
		turnCount -= turnInterval;

		// enemy searching area changes by weapon.
		vector<POINT> searchArea;
		vector<Object*> enemyVec;
		Object* forwardObject = NULL; // object excluding enemy.
		POINT forwardPos{ -1, -1 };

		// temporary implementation.
		switch (command)
		{
		case DIRECTION::LEFT:
			searchArea.push_back(POINT{ -1, 0 });
			forwardPos = POINT{ pos.x - 1, pos.y };
			break;
		case DIRECTION::RIGHT:
			searchArea.push_back(POINT{ 1, 0 });
			forwardPos = POINT{ pos.x + 1, pos.y };
			break;
		case DIRECTION::TOP:
			searchArea.push_back(POINT{ 0, -1 });
			forwardPos = POINT{ pos.x, pos.y - 1 };
			break;
		case DIRECTION::BOTTOM:
			searchArea.push_back(POINT{ 0, 1 });
			forwardPos = POINT{ pos.x, pos.y + 1 };
			break;
		}

		// searching.
		for(auto areaIter = searchArea.begin();
			areaIter != searchArea.end(); ++areaIter)
		{
			POINT searchPos = POINT{ pos.x + areaIter->x, pos.y + areaIter->y };
			Object* searchObj = scene->getObject(searchPos);

			// compare object type and push back being enemy.
			if (searchObj)
			{
				switch (searchObj->getType())
				{
				case OBJECT_TYPE::MONSTER_SLIME:
				case OBJECT_TYPE::MONSTER_SLIME_BLUE:
				case OBJECT_TYPE::MONSTER_SKELETON:
				case OBJECT_TYPE::MONSTER_BAT:
				case OBJECT_TYPE::MONSTER_NECRODANCER:
					enemyVec.push_back(searchObj);
					break;
				default:
					break;
				}
			}
		}
		if (enemyVec.empty())
		{
			forwardObject = scene->getObject(forwardPos);
		}

		switch (command) {
		case DIRECTION::LEFT:
			if (!enemyVec.empty())
			{
				for (auto iter = enemyVec.begin(); iter != enemyVec.end(); ++iter)
				(*iter)->interact(this);
				SOUNDMANAGER->play(KEY_VO_CAD_MELLE_1_01, DEFAULT_VOLUME);
			}
			else if (forwardObject)
			{
				if (forwardObject->interact(this))
				{
					Move(POINT{ pos.x - 1, pos.y });
					headAnimator->changeAnimation(CHARACTER_STATE::JUMP_LEFT);
					bodyAnimator->changeAnimation(CHARACTER_STATE::JUMP_LEFT);
				}
			}
			else
			{
				Move(POINT{ pos.x - 1, pos.y });
				headAnimator->changeAnimation(CHARACTER_STATE::JUMP_LEFT);
				bodyAnimator->changeAnimation(CHARACTER_STATE::JUMP_LEFT);
			}
			break;
		case DIRECTION::RIGHT:
			if (!enemyVec.empty())
			{
				for (auto iter = enemyVec.begin(); iter != enemyVec.end(); ++iter)
				{
					(*iter)->interact(this);
				}
				DaggerEffectRightTF = true;
				SOUNDMANAGER->play(KEY_VO_CAD_MELLE_1_01, DEFAULT_VOLUME);
			}
			else if (forwardObject)
			{
				if (forwardObject->interact(this))
				{
					Move(POINT{ pos.x + 1, pos.y });
					headAnimator->changeAnimation(CHARACTER_STATE::JUMP_RIGHT);
					bodyAnimator->changeAnimation(CHARACTER_STATE::JUMP_RIGHT);
				}

			}
			else
			{
				Move(POINT{ pos.x + 1, pos.y });
				headAnimator->changeAnimation(CHARACTER_STATE::JUMP_RIGHT);
				bodyAnimator->changeAnimation(CHARACTER_STATE::JUMP_RIGHT);
			}
			break;
		case DIRECTION::TOP:
			if (!enemyVec.empty())
			{
				for (auto iter = enemyVec.begin(); iter != enemyVec.end(); ++iter)
					(*iter)->interact(this);
				SOUNDMANAGER->play(KEY_VO_CAD_MELLE_1_01, DEFAULT_VOLUME);
			}
			else if (forwardObject)
			{
				if (forwardObject->interact(this))
				{
					Move(POINT{ pos.x, pos.y - 1 });
					headAnimator->changeAnimation(CHARACTER_STATE::JUMP_TOP);
					bodyAnimator->changeAnimation(CHARACTER_STATE::JUMP_TOP);
				}
			}
			else
			{
				Move(POINT{ pos.x, pos.y - 1 });
				headAnimator->changeAnimation(CHARACTER_STATE::JUMP_TOP);
				bodyAnimator->changeAnimation(CHARACTER_STATE::JUMP_TOP);
			}
			break;
		case DIRECTION::BOTTOM:
			if (!enemyVec.empty())
			{
				for (auto iter = enemyVec.begin(); iter != enemyVec.end(); ++iter)
					(*iter)->interact(this);
				SOUNDMANAGER->play(KEY_VO_CAD_MELLE_1_01, DEFAULT_VOLUME);
			}
			else if (forwardObject)
			{
				if (forwardObject->interact(this))
				{
					Move(POINT{ pos.x, pos.y + 1 });
					headAnimator->changeAnimation(CHARACTER_STATE::JUMP_BOTTOM);
					bodyAnimator->changeAnimation(CHARACTER_STATE::JUMP_BOTTOM);
				}
			}
			else
			{
				Move(POINT{ pos.x, pos.y + 1 });
				headAnimator->changeAnimation(CHARACTER_STATE::JUMP_BOTTOM);
				bodyAnimator->changeAnimation(CHARACTER_STATE::JUMP_BOTTOM);
			}
			break;
		}

		command = DIRECTION::DIRECTION_NUM;

		if (PLAYERINFOMANAGER->getBomb().detailType != ITEM_DETAIL::ITEM_DETAIL_NUM)
		{ 
			if (KEYMANAGER->isOnceKeyDown('X'))
			{
				Explosion* explsion = new Explosion;
				explsion->init(scene, pos);
				scene->getObjectVec()->push_back(explsion);
				PLAYERINFOMANAGER->setBomb(EMPTY_ITEM);
			}
		}

		if (PLAYERINFOMANAGER->getHeal().detailType != ITEM_DETAIL::ITEM_DETAIL_NUM)
		{
			if (KEYMANAGER->isOnceKeyDown('Z'))
			{
				PLAYERINFOMANAGER->setHp(PLAYERINFOMANAGER->getHp() + 2);
				PLAYERINFOMANAGER->setHeal(EMPTY_ITEM);
			}
		}
	}

	// animation update.
	headAnimator->update();
	bodyAnimator->update();
}

void Player::render(void)
{
	POINT renderPos = GridPointToPixelPointCenter(pos);
	POINT revision = CAMERAMANAGER->getRevision();
	
	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		Rectangle(getMemDC(),
			GridPointToPixelPointLeftTop(pos).x - revision.x,
			GridPointToPixelPointLeftTop(pos).y - revision.y,
			GridPointToPixelPointLeftTop(pos).x - revision.x + TILE_SIZE,
			GridPointToPixelPointLeftTop(pos).y - revision.y + TILE_SIZE);
	}


	renderPos.x -= revision.x;
	renderPos.y -= revision.y;

	headAnimator->animationRender(getMemDC(), renderPos);
	bodyAnimator->animationRender(getMemDC(), renderPos);

	if (DaggerEffectRightTF)
	{
		cout << "����" << endl;
		IMAGEMANAGER->frameRender(KEY_SWIPE_DAGGER_RIGHT, getMemDC(), 
			GridPointToPixelPointLeftTop(pos).x - revision.x + 50, 
			GridPointToPixelPointLeftTop(pos).y - revision.y - 10, 
			effectCountIndex, 0);

		DaggerEffectRightTF = false; 
	}
}

void Player::renderMinimap(HDC _hdc)
{
	if (minimapStripe)
	{
		POINT renderPos = GridPointToPixelPointLeftTopMiniMap(pos);
		minimapStripe->render(_hdc, renderPos.x, renderPos.y);
	}
}

void Player::Move(POINT _pos)
{
	pos = _pos;
	rc = RectMakeCenter(pos.x * TILE_SIZE + TILE_SIZE / 2,
						pos.y * TILE_SIZE + TILE_SIZE / 2, TILE_SIZE, TILE_SIZE);
}

void Player::setBounce(DIRECTION dir)
{
	bounce = dir;
}

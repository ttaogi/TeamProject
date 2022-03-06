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
	
	{ // animation.
		headAnimator = new Animator();
		bodyAnimator = new Animator();
		bodyArmorAnimator = new Animator();
		atk_animator_Dagger = new Animator;
		atk_animator_Broadsword = new Animator;


		Animation* headIdleRight = new Animation();
		Animation* bodyIdleRight = new Animation();
		Animation* armorIdleRight = new Animation();
		Animation* headJumpRight = new Animation();
		Animation* bodyJumpRight = new Animation();
		Animation* armorJumpRight = new Animation();

		Animation* headIdleLeft = new Animation();
		Animation* bodyIdleLeft = new Animation();
		Animation* armorIdleLeft = new Animation();
		Animation* headJumpLeft = new Animation();
		Animation* bodyJumpLeft = new Animation();
		Animation* armorJumpLeft = new Animation();

		Animation* headJumpTop = new Animation();
		Animation* bodyJumpTop = new Animation();
		Animation* armorJumpTop = new Animation();
		Animation* headJumpBottom = new Animation();
		Animation* bodyJumpBottom = new Animation();
		Animation* armorJumpBottom = new Animation();

		Animation* Attak_left_Animation_Dagger = new Animation();
		Animation* Attak_Right_Animation_Dagger = new Animation();
		Animation* Attak_Top_Animation_Dagger = new Animation();
		Animation* Attak_Bottom_Animation_Dagger = new Animation();
		
		Animation* Attak_left_Animation_Broadsword = new Animation();
		Animation* Attak_Right_Animation_Broadsword = new Animation();
		Animation* Attak_Top_Animation_Broadsword = new Animation();
		Animation* Attak_Bottom_Animation_Broadsword = new Animation();
		Animation* null_animation = new Animation();

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
		armorIdleRight->init(
			KEY_PLAYER_ARMOR_IDLE_RIGHT,
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
		armorJumpRight->init(
			KEY_PLAYER_ARMOR_JUMP_RIGHT,
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
		armorIdleLeft->init(
			KEY_PLAYER_ARMOR_IDLE_LEFT,
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
		armorJumpLeft->init(
			KEY_PLAYER_ARMOR_JUMP_LEFT,
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
		armorJumpTop->init(
			KEY_PLAYER_ARMOR_JUMP_TOP,
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
		armorJumpBottom->init(
			KEY_PLAYER_ARMOR_JUMP_BOTTOM,
			POINT{ -24, -72 }, CHARACTER_STATE::JUMP_BOTTOM,
			false, false, 64
		);

		Attak_left_Animation_Dagger->init(
			KEY_SWIPE_DAGGER_LEFT,
			POINT{ -70, -50 }, CHARACTER_STATE::ATTACK_LEFT,
			false, false, 50
		);
		Attak_Right_Animation_Dagger->init(
			KEY_SWIPE_DAGGER_RIGHT,
			POINT{ 20, -50 }, CHARACTER_STATE::ATTACK_RIGHT,
			false, false, 50
		);
		Attak_Top_Animation_Dagger->init(
			KEY_SWIPE_DAGGER_TOP,
			POINT{ -20, -80 }, CHARACTER_STATE::ATTACK_TOP,
			false, false, 50
		);
		Attak_Bottom_Animation_Dagger->init(
			KEY_SWIPE_DAGGER_BOTTOM,
			POINT{ -20, 10 }, CHARACTER_STATE::ATTACK_BOTTOM,
			false, false, 50
		);
	
		Attak_left_Animation_Broadsword->init(
			KEY_SWIPE_BROADSWORD_LEFT,
			POINT{ -70, -70 }, CHARACTER_STATE::ATTACK_LEFT,
			false, false, 40
		);
		Attak_Right_Animation_Broadsword->init(
			KEY_SWIPE_BROADSWORD_RIGHT,
			POINT{ 20, -70 }, CHARACTER_STATE::ATTACK_RIGHT,
			false, false, 40
		);
		Attak_Top_Animation_Broadsword->init(
			KEY_SWIPE_BROADSWORD_TOP,
			POINT{ -68, -80 }, CHARACTER_STATE::ATTACK_TOP,
			false, false, 40
		);
		Attak_Bottom_Animation_Broadsword->init(
			KEY_SWIPE_BROADSWORD_BOTTOM,
			POINT{ -68, 10 }, CHARACTER_STATE::ATTACK_BOTTOM,
			false, false, 40
		);
		null_animation->init(
			KEY_SWIPE_ENEMY_LEFT,
			POINT{ -54, -48 }, CHARACTER_STATE::IDLE_RIGHT,
			true, false, 16
		);

		headAnimator->addAnimation(CHARACTER_STATE::IDLE_RIGHT, headIdleRight);
		bodyAnimator->addAnimation(CHARACTER_STATE::IDLE_RIGHT, bodyIdleRight);
		bodyArmorAnimator->addAnimation(CHARACTER_STATE::IDLE_RIGHT, armorIdleRight);
		headAnimator->addAnimation(CHARACTER_STATE::IDLE_LEFT, headIdleLeft);
		bodyAnimator->addAnimation(CHARACTER_STATE::IDLE_LEFT, bodyIdleLeft);
		bodyArmorAnimator->addAnimation(CHARACTER_STATE::IDLE_LEFT, armorIdleLeft);

		headAnimator->addAnimation(CHARACTER_STATE::JUMP_RIGHT, headJumpRight);
		bodyAnimator->addAnimation(CHARACTER_STATE::JUMP_RIGHT, bodyJumpRight);
		bodyArmorAnimator->addAnimation(CHARACTER_STATE::JUMP_RIGHT, armorJumpRight);
		headAnimator->addAnimation(CHARACTER_STATE::JUMP_LEFT, headJumpLeft);
		bodyAnimator->addAnimation(CHARACTER_STATE::JUMP_LEFT, bodyJumpLeft);
		bodyArmorAnimator->addAnimation(CHARACTER_STATE::JUMP_LEFT, armorJumpLeft);

		headAnimator->addAnimation(CHARACTER_STATE::JUMP_TOP, headJumpTop);
		bodyAnimator->addAnimation(CHARACTER_STATE::JUMP_TOP, bodyJumpTop);
		bodyArmorAnimator->addAnimation(CHARACTER_STATE::JUMP_TOP, armorJumpTop);
		headAnimator->addAnimation(CHARACTER_STATE::JUMP_BOTTOM, headJumpBottom);
		bodyAnimator->addAnimation(CHARACTER_STATE::JUMP_BOTTOM, bodyJumpBottom);
		bodyArmorAnimator->addAnimation(CHARACTER_STATE::JUMP_BOTTOM, armorJumpBottom);

		atk_animator_Dagger->addAnimation(CHARACTER_STATE::ATTACK_LEFT, Attak_left_Animation_Dagger);
		atk_animator_Dagger->addAnimation(CHARACTER_STATE::ATTACK_RIGHT, Attak_Right_Animation_Dagger);
		atk_animator_Dagger->addAnimation(CHARACTER_STATE::ATTACK_TOP, Attak_Top_Animation_Dagger);
		atk_animator_Dagger->addAnimation(CHARACTER_STATE::ATTACK_BOTTOM, Attak_Bottom_Animation_Dagger);
		atk_animator_Dagger->addAnimation(CHARACTER_STATE::IDLE_RIGHT, null_animation);

		atk_animator_Broadsword->addAnimation(CHARACTER_STATE::ATTACK_LEFT, Attak_left_Animation_Broadsword);
		atk_animator_Broadsword->addAnimation(CHARACTER_STATE::ATTACK_RIGHT, Attak_Right_Animation_Broadsword);
		atk_animator_Broadsword->addAnimation(CHARACTER_STATE::ATTACK_TOP, Attak_Top_Animation_Broadsword);
		atk_animator_Broadsword->addAnimation(CHARACTER_STATE::ATTACK_BOTTOM, Attak_Bottom_Animation_Broadsword);
		atk_animator_Broadsword->addAnimation(CHARACTER_STATE::IDLE_RIGHT, null_animation);
	}

	return S_OK;
}

void Player::release(void)
{
	SAFE_RELEASE(headAnimator);
	SAFE_DELETE(headAnimator);
	SAFE_RELEASE(bodyAnimator);
	SAFE_DELETE(bodyAnimator);
	SAFE_RELEASE(bodyArmorAnimator);
	SAFE_DELETE(bodyArmorAnimator);
	SAFE_RELEASE(atk_animator_Dagger);
	SAFE_DELETE(atk_animator_Dagger);
}

void Player::update(void)
{
	turnCount += TIMEMANAGER->getElapsedTime();

	// non-idle animation -> idle animation.
	if (headAnimator->isEnd() && bodyAnimator->isEnd())
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
					bodyArmorAnimator->changeAnimation(CHARACTER_STATE::JUMP_LEFT);
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
					bodyArmorAnimator->changeAnimation(CHARACTER_STATE::JUMP_TOP);
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
					bodyArmorAnimator->changeAnimation(CHARACTER_STATE::JUMP_RIGHT);
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
					bodyArmorAnimator->changeAnimation(CHARACTER_STATE::JUMP_BOTTOM);
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
				bodyArmorAnimator->changeAnimation(CHARACTER_STATE::IDLE_RIGHT);
			}
			else if (headAnimator->getCurrentState() == CHARACTER_STATE::JUMP_LEFT)
			{
				headAnimator->changeAnimation(CHARACTER_STATE::IDLE_LEFT);
				bodyAnimator->changeAnimation(CHARACTER_STATE::IDLE_LEFT);
				bodyArmorAnimator->changeAnimation(CHARACTER_STATE::IDLE_LEFT);
			}
			else if (headAnimator->getCurrentState() == CHARACTER_STATE::JUMP_TOP)
			{
				headAnimator->changeAnimation(CHARACTER_STATE::IDLE_RIGHT);
				bodyAnimator->changeAnimation(CHARACTER_STATE::IDLE_RIGHT);
				bodyArmorAnimator->changeAnimation(CHARACTER_STATE::IDLE_RIGHT);
			}
			else if (headAnimator->getCurrentState() == CHARACTER_STATE::JUMP_BOTTOM)
			{
				headAnimator->changeAnimation(CHARACTER_STATE::IDLE_LEFT);
				bodyAnimator->changeAnimation(CHARACTER_STATE::IDLE_LEFT);
				bodyArmorAnimator->changeAnimation(CHARACTER_STATE::IDLE_LEFT);
			}
		}

	// weapon animation -> idle
	if (atk_animator_Dagger->isEnd())
	{
		atk_animator_Dagger->changeAnimation(CHARACTER_STATE::IDLE_RIGHT);
	}

	if (atk_animator_Broadsword->isEnd())
	{
		atk_animator_Broadsword->changeAnimation(CHARACTER_STATE::IDLE_RIGHT);
	}

	// get command.
	if (turnCount >= turnInterval * 0.7f && turnCount < turnInterval)
	{
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
			if (PLAYERINFOMANAGER->getAttack().detailType == ITEM_DETAIL::ATTACK_BROADSWORD)
			{
				searchArea.push_back(POINT{ -1, -1 });
				searchArea.push_back(POINT{ -1, 0 });
				searchArea.push_back(POINT{ -1, 1 });
			}
			else
				searchArea.push_back(POINT{ -1, 0 });

			forwardPos = POINT{ pos.x - 1, pos.y };
			break;
		case DIRECTION::RIGHT:
			if (PLAYERINFOMANAGER->getAttack().detailType == ITEM_DETAIL::ATTACK_BROADSWORD)
			{
				searchArea.push_back(POINT{  1, -1});
				searchArea.push_back(POINT{	 1, 0 });
				searchArea.push_back(POINT{  1, 1 });
			}
			else
				searchArea.push_back(POINT{ 1, 0 });

			forwardPos = POINT{ pos.x + 1, pos.y };
			break;
		case DIRECTION::TOP:
			if (PLAYERINFOMANAGER->getAttack().detailType == ITEM_DETAIL::ATTACK_BROADSWORD)
			{
				searchArea.push_back(POINT{ -1, -1 });
				searchArea.push_back(POINT{ 0, -1 });
				searchArea.push_back(POINT{ 1, -1 });
			}
			else
				searchArea.push_back(POINT{ 0, -1 });

			forwardPos = POINT{ pos.x, pos.y - 1 };
			break;
		case DIRECTION::BOTTOM:
			if (PLAYERINFOMANAGER->getAttack().detailType == ITEM_DETAIL::ATTACK_BROADSWORD)
			{
				searchArea.push_back(POINT{ -1, 1 });
				searchArea.push_back(POINT{ 0, 1 });
				searchArea.push_back(POINT{ 1, 1 });
			}
			else
				searchArea.push_back(POINT{ 0, 1 });

			forwardPos = POINT{ pos.x, pos.y + 1 };
			break;
		}

		// searching.
		for(auto areaIter = searchArea.begin(); areaIter != searchArea.end(); ++areaIter)
		{
			POINT searchPos = POINT{ pos.x + areaIter->x, pos.y + areaIter->y };
			Object* searchObj = scene->getObject(searchPos);

			// compare object type and push back being enemy.
			if (searchObj)
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

		if (enemyVec.empty()) forwardObject = scene->getObject(forwardPos);

		switch (command) {
		case DIRECTION::LEFT:
			if (!enemyVec.empty())
			{
				for (auto iter = enemyVec.begin(); iter != enemyVec.end(); ++iter)
					(*iter)->interact(this);
				SOUNDMANAGER->play(KEY_VO_CAD_MELLE_1_01, DEFAULT_VOLUME);

				if (PLAYERINFOMANAGER->getAttack().detailType == ITEM_DETAIL::ATTACK_DAGGER)
				{
					atk_animator_Dagger->changeAnimation(CHARACTER_STATE::ATTACK_LEFT);
				}

				else if (PLAYERINFOMANAGER->getAttack().detailType == ITEM_DETAIL::ATTACK_BROADSWORD)
				{
					atk_animator_Broadsword->changeAnimation(CHARACTER_STATE::ATTACK_LEFT);
				}
			}

			else if (forwardObject)
			{
				if (forwardObject->interact(this))
				{
					Move(POINT{ pos.x - 1, pos.y });
					headAnimator->changeAnimation(CHARACTER_STATE::JUMP_LEFT);
					bodyAnimator->changeAnimation(CHARACTER_STATE::JUMP_LEFT);
					bodyArmorAnimator->changeAnimation(CHARACTER_STATE::JUMP_LEFT);
				}
			}

			else
			{
				Move(POINT{ pos.x - 1, pos.y });
				headAnimator->changeAnimation(CHARACTER_STATE::JUMP_LEFT);
				bodyAnimator->changeAnimation(CHARACTER_STATE::JUMP_LEFT);
				bodyArmorAnimator->changeAnimation(CHARACTER_STATE::JUMP_LEFT);
			}

			break;
		case DIRECTION::RIGHT:
			if (!enemyVec.empty())
			{
				for (auto iter = enemyVec.begin(); iter != enemyVec.end(); ++iter)
					(*iter)->interact(this);
				SOUNDMANAGER->play(KEY_VO_CAD_MELLE_1_01, DEFAULT_VOLUME);

				if (PLAYERINFOMANAGER->getAttack().detailType == ITEM_DETAIL::ATTACK_DAGGER)
				{
					atk_animator_Dagger->changeAnimation(CHARACTER_STATE::ATTACK_RIGHT);
				}

				else if (PLAYERINFOMANAGER->getAttack().detailType == ITEM_DETAIL::ATTACK_BROADSWORD)
				{
					atk_animator_Broadsword->changeAnimation(CHARACTER_STATE::ATTACK_RIGHT);
				}
			}
			else if (forwardObject)
			{
				if (forwardObject->interact(this))
				{
					Move(POINT{ pos.x + 1, pos.y });
					headAnimator->changeAnimation(CHARACTER_STATE::JUMP_RIGHT);
					bodyAnimator->changeAnimation(CHARACTER_STATE::JUMP_RIGHT);
					bodyArmorAnimator->changeAnimation(CHARACTER_STATE::JUMP_RIGHT);
				}
			}
			else
			{
				Move(POINT{ pos.x + 1, pos.y });
				headAnimator->changeAnimation(CHARACTER_STATE::JUMP_RIGHT);
				bodyAnimator->changeAnimation(CHARACTER_STATE::JUMP_RIGHT);
				bodyArmorAnimator->changeAnimation(CHARACTER_STATE::JUMP_RIGHT);
			}
			break;
		case DIRECTION::TOP:
			if (!enemyVec.empty())
			{
				for (auto iter = enemyVec.begin(); iter != enemyVec.end(); ++iter)
					(*iter)->interact(this);
				SOUNDMANAGER->play(KEY_VO_CAD_MELLE_1_01, DEFAULT_VOLUME);

				if (PLAYERINFOMANAGER->getAttack().detailType == ITEM_DETAIL::ATTACK_DAGGER)
				{
					atk_animator_Dagger->changeAnimation(CHARACTER_STATE::ATTACK_TOP);
				}

				else if (PLAYERINFOMANAGER->getAttack().detailType == ITEM_DETAIL::ATTACK_BROADSWORD)
				{
					atk_animator_Broadsword->changeAnimation(CHARACTER_STATE::ATTACK_TOP);
				}
			}
			else if (forwardObject)
			{
				if (forwardObject->interact(this))
				{
					Move(POINT{ pos.x, pos.y - 1 });
					headAnimator->changeAnimation(CHARACTER_STATE::JUMP_TOP);
					bodyAnimator->changeAnimation(CHARACTER_STATE::JUMP_TOP);
					bodyArmorAnimator->changeAnimation(CHARACTER_STATE::JUMP_TOP);
				}
			}
			else
			{
				Move(POINT{ pos.x, pos.y - 1 });
				headAnimator->changeAnimation(CHARACTER_STATE::JUMP_TOP);
				bodyAnimator->changeAnimation(CHARACTER_STATE::JUMP_TOP);
				bodyArmorAnimator->changeAnimation(CHARACTER_STATE::JUMP_TOP);
			}
			break;
		case DIRECTION::BOTTOM:
			if (!enemyVec.empty())
			{
				for (auto iter = enemyVec.begin(); iter != enemyVec.end(); ++iter)
					(*iter)->interact(this);
				SOUNDMANAGER->play(KEY_VO_CAD_MELLE_1_01, DEFAULT_VOLUME);

				if (PLAYERINFOMANAGER->getAttack().detailType == ITEM_DETAIL::ATTACK_DAGGER)
				{
					atk_animator_Dagger->changeAnimation(CHARACTER_STATE::ATTACK_BOTTOM);
				}

				else if (PLAYERINFOMANAGER->getAttack().detailType == ITEM_DETAIL::ATTACK_BROADSWORD)
				{
					atk_animator_Broadsword->changeAnimation(CHARACTER_STATE::ATTACK_BOTTOM);
				}
			}
			else if (forwardObject)
			{
				if (forwardObject->interact(this))
				{
					Move(POINT{ pos.x, pos.y + 1 });
					headAnimator->changeAnimation(CHARACTER_STATE::JUMP_BOTTOM);
					bodyAnimator->changeAnimation(CHARACTER_STATE::JUMP_BOTTOM);
					bodyArmorAnimator->changeAnimation(CHARACTER_STATE::JUMP_BOTTOM);
				}
			}
			else
			{
				Move(POINT{ pos.x, pos.y + 1 });
				headAnimator->changeAnimation(CHARACTER_STATE::JUMP_BOTTOM);
				bodyAnimator->changeAnimation(CHARACTER_STATE::JUMP_BOTTOM);
				bodyArmorAnimator->changeAnimation(CHARACTER_STATE::JUMP_BOTTOM);
			}
			break;
		}

		command = DIRECTION::DIRECTION_NUM;

		if (PLAYERINFOMANAGER->getBomb().detailType != ITEM_DETAIL::ITEM_DETAIL_NUM)
			if (KEYMANAGER->isOnceKeyDown('X'))
			{
				Explosion* explsion = new Explosion;
				explsion->init(scene, pos);
				scene->getObjectVec()->push_back(explsion);
				PLAYERINFOMANAGER->setBomb(EMPTY_ITEM);
			}

		if (PLAYERINFOMANAGER->getHeal().detailType != ITEM_DETAIL::ITEM_DETAIL_NUM)
			if (KEYMANAGER->isOnceKeyDown('Z'))
			{
				PLAYERINFOMANAGER->setHp(PLAYERINFOMANAGER->getHp() + 2);
				PLAYERINFOMANAGER->setHeal(EMPTY_ITEM);
			}
	}

	// animation update.
	headAnimator->update();
	bodyAnimator->update();
	bodyArmorAnimator->update();
	atk_animator_Dagger->update();
	atk_animator_Broadsword->update();
}

void Player::render(void)
{
	POINT renderPos = GridPointToPixelPointCenter(pos);
	POINT ltPos = GridPointToPixelPointLeftTop(pos);
	POINT revision = CAMERAMANAGER->getRevision();
	
	renderPos.x -= revision.x;
	renderPos.y -= revision.y;

	headAnimator->animationRender(getMemDC(), renderPos);
	if(PLAYERINFOMANAGER->getBody().type == ITEM_TYPE::ITEM_TYPE_NUM)
		bodyAnimator->animationRender(getMemDC(), renderPos);
	else
		bodyArmorAnimator->animationRender(getMemDC(), renderPos);

	if (atk_animator_Dagger->getCurrentState() != CHARACTER_STATE::IDLE_RIGHT)
		atk_animator_Dagger->animationRender(getMemDC(), renderPos);
	
	if (atk_animator_Broadsword->getCurrentState() != CHARACTER_STATE::IDLE_RIGHT)
		atk_animator_Broadsword->animationRender(getMemDC(), renderPos);
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
	POINT rcCenter = GridPointToPixelPointCenter(_pos);
	pos = _pos;
	rc = RectMakeCenter(rcCenter.x, rcCenter.y, TILE_SIZE, TILE_SIZE);
}

void Player::setBounce(DIRECTION dir) { bounce = dir; }

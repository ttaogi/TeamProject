#include "Stdafx.h"

#include "PlayerInfoManager.h"

HRESULT PlayerInfoManager::init()
{
	money = 99;
	shovel = ITEMINFOMANAGER->getItemInfo(ITEM_DETAIL::SHOVEL);
	attack = ITEMINFOMANAGER->getItemInfo(ITEM_DETAIL::ATTACK_DAGGER);
	body = head = torch = heal 
		= ITEMINFOMANAGER->getItemInfo(ITEM_DETAIL::ITEM_DETAIL_NUM);
	bomb = ITEMINFOMANAGER->getItemInfo(ITEM_DETAIL::BOMB);
	hpMax = hp = PLAYER_HP_MAX;

	cout << "####################" << endl;
	cout << "PlayerInfo Init." << endl;
	cout << "player money : " << to_string(money) << endl;
	cout << "shovel : " << shovel.name << endl;
	cout << "attack : " << attack.name << endl;
	cout << "body : " << body.name << endl;
	cout << "head : " << head.name << endl;
	cout << "torch : " << torch.name << endl;
	cout << "heal : " << heal.name << endl;
	cout << "bomb : " << bomb.name << endl;
	cout << "####################" << endl << endl;

	return S_OK;
}

void PlayerInfoManager::release() { }

int PlayerInfoManager::getMoney() const { return money; }
void PlayerInfoManager::setMoney(int _money) { money = _money; }

Item PlayerInfoManager::getShovel() const { return shovel; }
void PlayerInfoManager::setShovel(Item _shovel)
{
	if (_shovel.type == ITEM_TYPE::SHOVEL || _shovel.type == ITEM_TYPE::ITEM_TYPE_NUM)
		shovel = _shovel;
}

Item PlayerInfoManager::getAttack() const { return attack; }
void PlayerInfoManager::setAttack(Item _attack)
{
	if (_attack.type == ITEM_TYPE::ATTACK || _attack.type == ITEM_TYPE::ITEM_TYPE_NUM)
		attack = _attack;
}

Item PlayerInfoManager::getBody() const { return body; }
void PlayerInfoManager::setBody(Item _body)
{
	if (_body.type == ITEM_TYPE::BODY || _body.type == ITEM_TYPE::ITEM_TYPE_NUM)
		body = _body;
}

Item PlayerInfoManager::getHead() const { return head; }
void PlayerInfoManager::setHead(Item _head)
{
	if (_head.type == ITEM_TYPE::HEAD || _head.type == ITEM_TYPE::ITEM_TYPE_NUM)
		head = _head;
}

Item PlayerInfoManager::getTorch() const { return torch; }
void PlayerInfoManager::setTorch(Item _torch)
{
	if (_torch.type == ITEM_TYPE::TORCH || _torch.type == ITEM_TYPE::ITEM_TYPE_NUM)
		torch = _torch;
}

Item PlayerInfoManager::getHeal() const { return heal; }
void PlayerInfoManager::setHeal(Item _heal)
{
	if (_heal.type == ITEM_TYPE::HEAL || _heal.type == ITEM_TYPE::ITEM_TYPE_NUM)
		heal = _heal;
}

Item PlayerInfoManager::getBomb() const { return bomb; }
void PlayerInfoManager::setBomb(Item _bomb)
{
	if (_bomb.type == ITEM_TYPE::BOMB || _bomb.type == ITEM_TYPE::ITEM_TYPE_NUM)
		bomb = _bomb;
}

int PlayerInfoManager::getHp() const
{
	return hp;
}

void PlayerInfoManager::setHp(int _hp)
{
	hp = _hp;

	if (hp > hpMax) hp = hpMax;
}

int PlayerInfoManager::getHpMax() const
{
	return hpMax;
}

int PlayerInfoManager::getViewDistance()
{
	return DEFAULT_VIEW_DISTANCE + torch.range;
}

#include "Stdafx.h"

#include "PlayerInfoManager.h"

HRESULT PlayerInfoManager::init()
{
	money = 999;

	cout << "####################" << endl;
	cout << "PlayerInfo Init." << endl;
	cout << "player money : " << to_string(money) << endl;
	cout << "####################" << endl << endl;

	return S_OK;
}

void PlayerInfoManager::release() { }

int PlayerInfoManager::getMoney() const { return money; }

void PlayerInfoManager::setMoney(int _money) { money = _money; }

std::vector<Item> PlayerInfoManager::getInventory() const
{
	return inventory;
}

void PlayerInfoManager::addItem(Item _item)
{
	inventory.push_back(_item);
}

bool PlayerInfoManager::removeItem(Item _item)
{
	for (auto iter = inventory.begin(); iter != inventory.end(); ++iter)
	{
		if (iter->name == _item.name)
		{
			inventory.erase(iter);
			return true;
		}
	}
	return false;
}

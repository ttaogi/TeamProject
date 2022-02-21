#include "Stdafx/stdafx.h"

#include "Manager/PlayerInfoManager/PlayerInfoManager.h"

HRESULT PlayerInfoManager::Init()
{
	money = 10000;

	wcout << L"####################" << endl;
	wcout << L"PlayerInfo Init." << endl;
	wcout << L"player money : " << to_wstring(money) << endl;
	wcout << L"####################" << endl << endl;

	return S_OK;
}

void PlayerInfoManager::Release() { }

int PlayerInfoManager::GetMoney() const { return money; }

void PlayerInfoManager::SetMoney(int _money) { money = _money; }

std::vector<Item> PlayerInfoManager::GetInventory() const
{
	return inventory;
}

void PlayerInfoManager::AddItem(Item _item)
{
	inventory.push_back(_item);
}

bool PlayerInfoManager::RemoveItem(Item _item)
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

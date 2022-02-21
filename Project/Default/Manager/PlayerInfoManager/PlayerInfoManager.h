#pragma once

#include "DesignPattern/SingletonBase/SingletonBase.h"

class PlayerInfoManager : public SingletonBase<PlayerInfoManager> {
private:
	int money;
	std::vector<Item> inventory;
public:
	PlayerInfoManager() { }
	~PlayerInfoManager() { }

	HRESULT Init();
	void Release();

	int GetMoney() const;
	void SetMoney(int _money);
	std::vector<Item> GetInventory() const;

	void AddItem(Item _item);
	bool RemoveItem(Item _item);
};
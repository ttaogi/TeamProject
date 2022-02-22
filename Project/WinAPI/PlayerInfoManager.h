#pragma once

#include "SingletonBase.h"

class PlayerInfoManager : public SingletonBase<PlayerInfoManager> {
private:
	int money;
	std::vector<Item> inventory;
public:
	PlayerInfoManager() { }
	~PlayerInfoManager() { }

	HRESULT init();
	void release();

	int getMoney() const;
	void setMoney(int _money);
	std::vector<Item> getInventory() const;

	void addItem(Item _item);
	bool removeItem(Item _item);
};
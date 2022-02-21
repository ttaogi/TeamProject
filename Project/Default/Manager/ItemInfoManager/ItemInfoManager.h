#pragma once

#include "DesignPattern/SingletonBase/SingletonBase.h"

struct Item {
	std::wstring name;
	int value;
};

class ItemInfoManager : public SingletonBase<ItemInfoManager> {
private:
	std::vector<Item> itemVec;
public:
	ItemInfoManager() { }
	~ItemInfoManager() { }

	HRESULT Init();
	void Release();

	int GetItemNum() const;
	Item GetItemInfo(int _id) const;
	Item GetItemInfo(std::wstring _name) const;
};
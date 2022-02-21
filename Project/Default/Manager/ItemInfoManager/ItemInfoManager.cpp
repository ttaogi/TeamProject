#include "Stdafx/stdafx.h"

#include "Manager/ItemInfoManager/ItemInfoManager.h"

HRESULT ItemInfoManager::Init()
{
	TiXmlDocument doc;

	if (XmlManager::LoadFile(doc, XML_DOC_ITEM_LIST))
	{
		TiXmlElement* root = XmlManager::FirstChildElement(doc, L"ROOT");
		TiXmlElement* list = XmlManager::FirstChildElement(root, L"list");
		int listSize = 0;

		XmlManager::GetAttributeValueInt(list, L"num", &listSize);

		for (int i = 0; i < listSize; ++i) {
			TiXmlElement* itemInfo = XmlManager::FirstChildElement(list, L"item_" + to_wstring(i));

			if (itemInfo == NULL) continue;

			Item item;
			wstring name;
			int value;

			XmlManager::GetAttributeValue(itemInfo, L"name", name);

			XmlManager::GetAttributeValueInt(itemInfo, L"value", &value);

			item.name = name;
			item.value = value;

			itemVec.push_back(item);
		}

		wcout << L"####################" << endl;
		wcout << L"ItemInfo Init." << endl;
		wcout << L"item list" << endl;
		for (auto iter = itemVec.begin(); iter != itemVec.end(); ++iter)
		{
			wcout << iter->name << L" : " << iter->value << endl;
		}
		wcout << L"item list" << endl;
		wcout << L"####################" << endl;
	}
	else return E_FAIL;

	return S_OK;
}

void ItemInfoManager::Release() { }

int ItemInfoManager::GetItemNum() const
{
	return (int)itemVec.size();
}

Item ItemInfoManager::GetItemInfo(int _id) const
{
	if (_id >= itemVec.size())
		return Item{ L"", 0 };
	else
		return itemVec[_id];
}

Item ItemInfoManager::GetItemInfo(std::wstring _name) const
{
	Item item{ L"", 0 };
	for (auto iter = itemVec.begin(); iter != itemVec.end(); ++iter)
	{
		if (iter->name == _name)
		{
			item = *iter;
			break;
		}
	}
	return item;
}

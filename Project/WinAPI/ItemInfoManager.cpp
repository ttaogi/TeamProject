#include "Stdafx.h"

#include "ItemInfoManager.h"

HRESULT ItemInfoManager::init()
{
	TiXmlDocument doc;

	if (XmlManager::loadFile(doc, XML_DOC_ITEM_LIST))
	{
		TiXmlElement* root = XmlManager::firstChildElement(doc, "ROOT");
		TiXmlElement* list = XmlManager::firstChildElement(root, "list");
		int listSize = 0;

		XmlManager::getAttributeValueInt(list, "num", &listSize);

		for (int i = 0; i < listSize; ++i) {
			TiXmlElement* itemInfo = XmlManager::firstChildElement(list, "item_" + to_string(i));

			if (itemInfo == NULL) continue;

			Item item;
			string name;
			int value;

			XmlManager::getAttributeValue(itemInfo, "name", name);

			XmlManager::getAttributeValueInt(itemInfo, "value", &value);

			item.name = name;
			item.value = value;

			itemVec.push_back(item);
		}

		cout << "####################" << endl;
		cout << "ItemInfo Init." << endl;
		cout << "item list" << endl;
		for (auto iter = itemVec.begin(); iter != itemVec.end(); ++iter)
		{
			cout << iter->name << " : " << iter->value << endl;
		}
		cout << "item list" << endl;
		cout << "####################" << endl;
	}
	else return E_FAIL;

	return S_OK;
}

void ItemInfoManager::release() { }

int ItemInfoManager::getItemNum() const
{
	return (int)itemVec.size();
}

Item ItemInfoManager::getItemInfo(int _id) const
{
	if (_id >= itemVec.size())
		return Item{ ITEM_TYPE::ITEM_TYPE_NUM, "", 0 };
	else
		return itemVec[_id];
}

Item ItemInfoManager::getItemInfo(string _name) const
{
	Item item{ ITEM_TYPE::ITEM_TYPE_NUM, "", 0 };
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

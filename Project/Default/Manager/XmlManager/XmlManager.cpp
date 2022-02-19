#include "Stdafx/stdafx.h"

#include "Manager/XmlManager/XmlManager.h"

#include "Manager/XmlManager/TinyXml/tinyxml.h"

XmlManager::XmlManager() { }

XmlManager::~XmlManager() { }

HRESULT XmlManager::Init()
{
	LoadXml();

	return S_OK;
}

void XmlManager::Release() { SaveXml(); }

void XmlManager::LoadXml()
{
	TiXmlDocument exDoc;

	wcout << L"=========== XmlManager ex ===========" << endl;

	if (exDoc.LoadFile(WcsToMbsUtf8(XML_DOC_EXAMPLE).c_str()))
	{
		TiXmlElement* exDocRoot = exDoc.FirstChildElement("ROOT");
		TiXmlElement* element1 = exDocRoot->FirstChildElement("element1");
		TiXmlElement* element2 = exDocRoot->FirstChildElement("element2");
		TiXmlElement* element2_1 = element2->FirstChildElement("element2_1");
		TiXmlHandle handle(NULL);
		TiXmlAttribute* attribute = NULL;

		wcout << exDocRoot->Value() << endl;

		wcout << L"\t" << element1->Value() << endl;
		attribute = element1->FirstAttribute();
		while (attribute)
		{
			wcout << L"\t\t" << attribute->Name()
				<< L" : " << MbsUtf8ToWcs(attribute->Value()) << endl;
			attribute = attribute->Next();
		}

		wcout << L"\t" << element2->Value() << endl;
		attribute = element2->FirstAttribute();
		while (attribute)
		{
			wcout << L"\t\t" << attribute->Name()
				<< L" : " << MbsUtf8ToWcs(attribute->Value()) << endl;
			attribute = attribute->Next();
		}

		wcout << L"\t\t" << element2_1->Value() << endl;
		attribute = element2_1->FirstAttribute();
		while (attribute)
		{
			wcout << L"\t\t\t" << attribute->Name()
				<< L" : " << MbsUtf8ToWcs(attribute->Value()) << endl;
			attribute = attribute->Next();
		}
	}
	else
	{ // There is no XML_DOC_EXAMPLE file.
		wcout << L"There is no xml file." << endl;
	}

	wcout << L"+++++++++++ XmlManager ex +++++++++++" << endl;
}

void XmlManager::SaveXml()
{
	// declaration XML.
	TiXmlDocument exDoc;
	TiXmlDeclaration* exDocDeclaration =
		new TiXmlDeclaration("1.0", "UTF-8", "");
	exDoc.LinkEndChild(exDocDeclaration);

	// root node.
	TiXmlElement* exDocRoot = new TiXmlElement("ROOT");
	exDoc.LinkEndChild(exDocRoot);

	// comment.
	TiXmlComment* exDocComment = new TiXmlComment();
	wstring comment = L"This is a comment.";
	exDocComment->SetValue(WcsToMbsUtf8(comment).c_str());

	// sub node and data.
	TiXmlElement* element1 = new TiXmlElement("element1");
	exDocRoot->LinkEndChild(element1);
	TiXmlElement* element2 = new TiXmlElement("element2");
	exDocRoot->LinkEndChild(element2);
	TiXmlElement* element2_1 = new TiXmlElement("element2_1");
	element2->LinkEndChild(element2_1);
	/*
	root	- element1
			- element2
				-element2_1
	*/

	// attribute.
	element1->SetAttribute("attr1", "int");
	element1->SetAttribute("attr2", 123);
	element2->SetAttribute("attr1", "float");
	element2->SetAttribute("attr2", 45.6f);
	element2_1->SetAttribute("attr1", "string");
	element2_1->SetAttribute("attr2", "ansi");
	element2_1->SetAttribute("attr3", WcsToMbsUtf8(L"unicode").c_str());
	element2_1->SetAttribute("attr4", WcsToMbsUtf8(L"utf8").c_str());
	element2_1->SetAttribute("attr5", WcsToMbsUtf8(L"ÇÑ±ÛÊ«").c_str());

	exDoc.SaveFile(WcsToMbsUtf8(XML_DOC_EXAMPLE).c_str());

	wcout << L"save XML." << endl;
}

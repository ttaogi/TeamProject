#include "Stdafx/stdafx.h"

#include "Manager/XmlManager/XmlManager.h"

///////////////////////////////////////////
/*
	xml file is encoded by UTF-8.
	wstring conversion functions.
		int					: stoi
		long				: stol
		unsigned long		: stoul
		long long			: stoll
		unsigned long long	: stoull

		float				: stof
		double				: stod
		long double			: stold

		* to wstring		: to_wstring
*/
///////////////////////////////////////////

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

	if (XmlManager::LoadFile(exDoc, XML_DOC_EXAMPLE))
	{
		TiXmlElement* exDocRoot =
			XmlManager::FirstChildElement(exDoc, L"ROOT");
		TiXmlElement* element1 =
			XmlManager::FirstChildElement(exDocRoot, L"element1");
		TiXmlElement* element2 =
			XmlManager::FirstChildElement(exDocRoot, L"element2");
		TiXmlElement* element2_1 =
			XmlManager::FirstChildElement(element2, L"element2_1");
		TiXmlAttribute* attribute = NULL;

		wcout << XmlManager::Value(exDocRoot) << endl;

		wcout << L"\t" << XmlManager::Value(element1) << endl;
		attribute = element1->FirstAttribute();
		while (attribute)
		{
			wcout << L"\t\t" << XmlManager::Name(attribute)
				<< L" : " << XmlManager::Value(attribute) << endl;
			attribute = attribute->Next();
		}

		wcout << L"\t" << XmlManager::Value(element2) << endl;
		attribute = element2->FirstAttribute();
		while (attribute)
		{
			wcout << L"\t\t" << XmlManager::Name(attribute)
				<< L" : " << XmlManager::Value(attribute) << endl;
			attribute = attribute->Next();
		}

		wcout << L"\t\t" << XmlManager::Value(element2_1) << endl;
		attribute = element2_1->FirstAttribute();
		while (attribute)
		{
			wcout << L"\t\t\t" << XmlManager::Name(attribute)
				<< L" : " << XmlManager::Value(attribute) << endl;
			attribute = attribute->Next();
		}

		wcout << L"---------------------------------" << endl;

		wstring wStrVal;
		int intVal;
		float floatVal;

		wcout << L"\t" << XmlManager::Value(element1) << endl;
		XmlManager::GetAttributeValue(element1, L"attr1", wStrVal);
		XmlManager::GetAttributeValueInt(element1, L"attr2", &intVal);
		wcout << L"\t\t" << wStrVal << endl;
		wcout << L"\t\t" << intVal << endl;

		wcout << L"\t" << XmlManager::Value(element2) << endl;
		XmlManager::GetAttributeValue(element2, L"attr1", wStrVal);
		XmlManager::GetAttributeValueFloat(element2, L"attr2", &floatVal);
		wcout << L"\t\t" << wStrVal << endl;
		wcout << L"\t\t" << floatVal << endl;

		wcout << L"\t\t" << XmlManager::Value(element2_1) << endl;
		XmlManager::GetAttributeValue(element2_1, L"attr1", wStrVal);
		wcout << L"\t\t\t" << wStrVal << endl;
		XmlManager::GetAttributeValue(element2_1, L"attr2", wStrVal);
		wcout << L"\t\t\t" << wStrVal << endl;
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
	AddDeclaration(exDoc, L"1.0", L"UTF-8", L"");

	// root node.
	//TiXmlElement* exDocRoot = new TiXmlElement("ROOT");
	TiXmlElement* exDocRoot = XmlManager::CreateElement(L"ROOT");
	exDoc.LinkEndChild(exDocRoot);

	// comment.
	TiXmlComment* exDocComment = new TiXmlComment();
	wstring comment = L"This is a comment.";
	exDocComment->SetValue(WcsToMbsUtf8(comment).c_str());
	exDocRoot->LinkEndChild(exDocComment);

	// sub node and data.
	/*
	root	- element1
			- element2
				-element2_1
	*/
	TiXmlElement* element1 = XmlManager::CreateElement(L"element1");
	exDocRoot->LinkEndChild(element1);
	TiXmlElement* element2 = XmlManager::CreateElement(L"element2");
	exDocRoot->LinkEndChild(element2);
	TiXmlElement* element2_1 = XmlManager::CreateElement(L"element2_1");
	element2->LinkEndChild(element2_1);

	// attribute.
	XmlManager::SetAttribute(element1, L"attr1", L"int");
	XmlManager::SetAttribute(element1, L"attr2", 123);
	XmlManager::SetAttribute(element2, L"attr1", L"float");
	XmlManager::SetAttribute(element2, L"attr2", 45.6f);
	XmlManager::SetAttribute(element2_1, L"attr1", L"string");
	XmlManager::SetAttribute(element2_1, L"attr2", L"ÇÑ±ÛÊ«");

	exDoc.SaveFile(WcsToMbsUtf8(XML_DOC_EXAMPLE).c_str());

	wcout << L"save XML." << endl;
}

bool XmlManager::LoadFile(
	TiXmlDocument& _doc, const wstring& _fileName)
{
	return _doc.LoadFile(WcsToMbsUtf8(_fileName).c_str());
}

bool XmlManager::SaveFile(
	TiXmlDocument& _doc, const wstring& _fileName)
{
	return _doc.SaveFile(WcsToMbsUtf8(_fileName).c_str());
}

void XmlManager::AddDeclaration(
	TiXmlDocument& _doc, wstring _version,
	wstring _encoding, wstring _standAlone)
{
	TiXmlDeclaration* declaration =
		new TiXmlDeclaration(
			WcsToMbsUtf8(_version).c_str(),
			WcsToMbsUtf8(_encoding).c_str(),
			WcsToMbsUtf8(_standAlone).c_str()
		);
	_doc.LinkEndChild(declaration);
}

void XmlManager::AddComment(
	TiXmlDocument& _doc, wstring _comment)
{
	TiXmlComment* comment = new TiXmlComment();
	comment->SetValue(WcsToMbsUtf8(_comment).c_str());
	_doc.LinkEndChild(comment);
}

TiXmlElement* XmlManager::CreateElement(wstring _value)
{
	TiXmlElement* element =
		new TiXmlElement(WcsToMbsUtf8(_value).c_str());
	return element;
}

void XmlManager::AddComment(
	TiXmlElement* _element, wstring _comment)
{
	TiXmlComment* comment = new TiXmlComment();
	comment->SetValue(WcsToMbsUtf8(_comment).c_str());
	_element->LinkEndChild(comment);
}

TiXmlElement* XmlManager::FirstChildElement(
	TiXmlDocument& _doc, const wstring& _value)
{
	return _doc.FirstChildElement(WcsToMbsUtf8(_value).c_str());
}

TiXmlElement* XmlManager::FirstChildElement(
	TiXmlElement* _element, const wstring& _value)
{
	return _element->FirstChildElement(WcsToMbsUtf8(_value).c_str());
}

wstring XmlManager::Value(TiXmlElement* _element)
{
	return MbsUtf8ToWcs(_element->Value());
}

wstring XmlManager::Name(TiXmlAttribute* _attribute)
{
	return MbsUtf8ToWcs(_attribute->Name());
}

wstring XmlManager::Value(TiXmlAttribute* _attribute)
{
	return MbsUtf8ToWcs(_attribute->Value());
}

int XmlManager::ValueInt(TiXmlAttribute * _attribute)
{
	return stoi(MbsUtf8ToWcs(_attribute->Value()));
}

float XmlManager::ValueFloat(TiXmlAttribute * _attribute)
{
	return stof(MbsUtf8ToWcs(_attribute->Value()));
}

void XmlManager::SetAttribute(
	TiXmlElement* _element, wstring _name, wstring _value)
{
	_element->SetAttribute(
		WcsToMbsUtf8(_name).c_str(),
		WcsToMbsUtf8(_value).c_str()
	);
}

void XmlManager::SetAttribute(
	TiXmlElement* _element, wstring _name, int _value)
{
	_element->SetAttribute(
		WcsToMbsUtf8(_name).c_str(),
		WcsToMbsUtf8(to_wstring(_value)).c_str()
	);
}

void XmlManager::SetAttribute(
	TiXmlElement* _element, wstring _name, float _value)
{
	_element->SetAttribute(
		WcsToMbsUtf8(_name).c_str(),
		WcsToMbsUtf8(to_wstring(_value)).c_str()
	);
}

bool XmlManager::GetAttributeValue(
	TiXmlElement* _element, std::wstring _attribute, wstring& _value)
{
	const char* result = _element->Attribute(
		WcsToMbsUtf8(_attribute).c_str());

	if (result != NULL) _value = MbsUtf8ToWcs(result);

	return (result != NULL);
}

bool XmlManager::GetAttributeValueInt(
	TiXmlElement* _element, std::wstring _attribute, int* _value)
{
	const char* result = _element->Attribute(
		WcsToMbsUtf8(_attribute).c_str(), _value);

	return (result != NULL);
}

bool XmlManager::GetAttributeValueFloat(
	TiXmlElement* _element, std::wstring _attribute, float* _value)
{
	double value;
	const char* result = _element->Attribute(
		WcsToMbsUtf8(_attribute).c_str(), &value);

	if (result != NULL) *_value = (float)value;

	return (result != NULL);
}

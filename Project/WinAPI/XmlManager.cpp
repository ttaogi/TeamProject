#include "Stdafx.h"

#include "XmlManager.h"

XmlManager::XmlManager() { }

XmlManager::~XmlManager() { }

HRESULT XmlManager::init()
{
	//loadXml();
	return S_OK;
}

void XmlManager::release() { /*saveXml();*/ }

void XmlManager::loadXml()
{
	TiXmlDocument exDoc;

	cout << "=========== XmlManager ex ===========" << endl;

	if (XmlManager::loadFile(exDoc, XML_DOC_EXAMPLE))
	{
		TiXmlElement* exDocRoot =
			XmlManager::firstChildElement(exDoc, "ROOT");
		TiXmlElement* element1 =
			XmlManager::firstChildElement(exDocRoot, "element1");
		TiXmlElement* element2 =
			XmlManager::firstChildElement(exDocRoot, "element2");
		TiXmlElement* element2_1 =
			XmlManager::firstChildElement(element2, "element2_1");
		TiXmlAttribute* attribute = NULL;

		cout << XmlManager::value(exDocRoot) << endl;

		cout << "\t" << XmlManager::value(element1) << endl;
		attribute = element1->FirstAttribute();
		while (attribute)
		{
			cout << "\t\t" << XmlManager::name(attribute)
				<< " : " << XmlManager::value(attribute) << endl;
			attribute = attribute->Next();
		}

		cout << "\t" << XmlManager::value(element2) << endl;
		attribute = element2->FirstAttribute();
		while (attribute)
		{
			cout << "\t\t" << XmlManager::name(attribute)
				<< " : " << XmlManager::value(attribute) << endl;
			attribute = attribute->Next();
		}

		cout << "\t\t" << XmlManager::value(element2_1) << endl;
		attribute = element2_1->FirstAttribute();
		while (attribute)
		{
			cout << "\t\t\t" << XmlManager::name(attribute)
				<< " : " << XmlManager::value(attribute) << endl;
			attribute = attribute->Next();
		}

		cout << "---------------------------------" << endl;

		string strVal;
		int intVal;
		float floatVal;

		cout << "\t" << XmlManager::value(element1) << endl;
		XmlManager::getAttributeValue(element1, "attr1", strVal);
		XmlManager::getAttributeValueInt(element1, "attr2", &intVal);
		cout << "\t\t" << strVal << endl;
		cout << "\t\t" << intVal << endl;

		cout << "\t" << XmlManager::value(element2) << endl;
		XmlManager::getAttributeValue(element2, "attr1", strVal);
		XmlManager::getAttributeValueFloat(element2, "attr2", &floatVal);
		cout << "\t\t" << strVal << endl;
		cout << "\t\t" << floatVal << endl;

		cout << "\t\t" << XmlManager::value(element2_1) << endl;
		XmlManager::getAttributeValue(element2_1, "attr1", strVal);
		cout << "\t\t\t" << strVal << endl;
		XmlManager::getAttributeValue(element2_1, "attr2", strVal);
		cout << "\t\t\t" << strVal << endl;
	}
	else
	{ // There is no XML_DOC_EXAMPLE file.
		cout << "There is no xml file." << endl;
	}

	cout << "+++++++++++ XmlManager ex +++++++++++" << endl;
}

void XmlManager::saveXml()
{
	// declaration XML.
	TiXmlDocument exDoc;
	XmlManager::addDeclaration(exDoc, "1.0", "ANSI", "");

	// root node.
	TiXmlElement* exDocRoot = XmlManager::createElement("ROOT");
	exDoc.LinkEndChild(exDocRoot);

	// comment.
	TiXmlComment* exDocComment = new TiXmlComment();
	string comment = "This is a comment.";
	exDocComment->SetValue(comment.c_str());
	exDocRoot->LinkEndChild(exDocComment);

	// sub node and data.
	/*
	root	- element1
			- element2
				-element2_1
	*/
	TiXmlElement* element1 = XmlManager::createElement("element1");
	exDocRoot->LinkEndChild(element1);
	TiXmlElement* element2 = XmlManager::createElement("element2");
	exDocRoot->LinkEndChild(element2);
	TiXmlElement* element2_1 = XmlManager::createElement("element2_1");
	element2->LinkEndChild(element2_1);

	// attribute.
	XmlManager::setAttribute(element1, "attr1", "int");
	XmlManager::setAttribute(element1, "attr2", 123);
	XmlManager::setAttribute(element2, "attr1", "float");
	XmlManager::setAttribute(element2, "attr2", 45.6f);
	XmlManager::setAttribute(element2_1, "attr1", "string");
	XmlManager::setAttribute(element2_1, "attr2", "ÇÑ±ÛÊ«");

	exDoc.SaveFile(XML_DOC_EXAMPLE.c_str());

	cout << "save XML." << endl;
}

bool XmlManager::loadFile(
	TiXmlDocument& _doc, const string& _fileName)
{
	return _doc.LoadFile(_fileName.c_str());
}

bool XmlManager::saveFile(
	TiXmlDocument& _doc, const string& _fileName)
{
	return _doc.SaveFile(_fileName.c_str());
}

void XmlManager::addDeclaration(
	TiXmlDocument& _doc, string _version,
	string _encoding, string _standAlone)
{
	TiXmlDeclaration* declaration =
		new TiXmlDeclaration(
			_version.c_str(), _encoding.c_str(), _standAlone.c_str());
	_doc.LinkEndChild(declaration);
}

void XmlManager::addComment(
	TiXmlDocument& _doc, string _comment)
{
	TiXmlComment* comment = new TiXmlComment();
	comment->SetValue(_comment.c_str());
	_doc.LinkEndChild(comment);
}

TiXmlElement* XmlManager::createElement(string _value)
{
	TiXmlElement* element = new TiXmlElement(_value.c_str());
	return element;
}

void XmlManager::addComment(
	TiXmlElement* _element, string _comment)
{
	TiXmlComment* comment = new TiXmlComment();
	comment->SetValue(_comment.c_str());
	_element->LinkEndChild(comment);
}

TiXmlElement* XmlManager::firstChildElement(
	TiXmlDocument& _doc, const string& _value)
{
	return _doc.FirstChildElement(_value.c_str());
}

TiXmlElement* XmlManager::firstChildElement(
	TiXmlElement* _element, const string& _value)
{
	return _element->FirstChildElement(_value.c_str());
}

string XmlManager::value(TiXmlElement* _element)
{
	return _element->Value();
}

string XmlManager::name(TiXmlAttribute* _attribute)
{
	return _attribute->Name();
}

string XmlManager::value(TiXmlAttribute* _attribute)
{
	return _attribute->Value();
}

int XmlManager::valueInt(TiXmlAttribute * _attribute)
{
	return stoi(_attribute->Value());
}

float XmlManager::valueFloat(TiXmlAttribute * _attribute)
{
	return stof(_attribute->Value());
}

double XmlManager::valueDouble(TiXmlAttribute * _attribute)
{
	return stod(_attribute->Value());
}

void XmlManager::setAttribute(
	TiXmlElement* _element, string _name, string _value)
{
	_element->SetAttribute(_name.c_str(), _value.c_str());
}

void XmlManager::setAttribute(
	TiXmlElement* _element, string _name, int _value)
{
	_element->SetAttribute(_name.c_str(), to_string(_value).c_str());
}

void XmlManager::setAttribute(
	TiXmlElement* _element, string _name, float _value)
{
	_element->SetAttribute(_name.c_str(), to_string(_value).c_str());
}

bool XmlManager::getAttributeValue(
	TiXmlElement* _element, string _attribute, string& _value)
{
	const char* result = _element->Attribute(_attribute.c_str());

	if (result != NULL) _value = result;

	return (result != NULL);
}

bool XmlManager::getAttributeValueInt(
	TiXmlElement* _element, string _attribute, int* _value)
{
	const char* result = _element->Attribute(_attribute.c_str(), _value);

	return (result != NULL);
}

bool XmlManager::getAttributeValueFloat(
	TiXmlElement* _element, string _attribute, float* _value)
{
	double value;
	const char* result = _element->Attribute(_attribute.c_str(), &value);

	if (result != NULL) *_value = (float)value;

	return (result != NULL);
}

bool XmlManager::getAttributeValueDouble(
	TiXmlElement* _element, std::string _attribute, double* _value)
{
	double value;
	const char* result = _element->Attribute(_attribute.c_str(), &value);

	if (result != NULL) *_value = value;

	return (result != NULL);
}

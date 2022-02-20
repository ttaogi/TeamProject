#pragma once

#include "DesignPattern/SingletonBase/SingletonBase.h"

#include "Manager/XmlManager/TinyXml/tinyxml.h"

class XmlManager : public SingletonBase<XmlManager> {
private:
public:
	XmlManager();
	~XmlManager();

	HRESULT Init();
	void Release();

	void LoadXml();
	void SaveXml();

	static bool LoadFile(
		TiXmlDocument& _doc, const std::wstring& _fileName);
	static bool SaveFile(
		TiXmlDocument& _doc, const std::wstring& _fileName);
	static void AddDeclaration(
		TiXmlDocument& _doc, std::wstring _version,
		std::wstring _encoding, std::wstring _standAlone);
	static void AddComment(
		TiXmlDocument& _doc, std::wstring _comment);

	static TiXmlElement* CreateElement(std::wstring _value);
	static void AddComment(
		TiXmlElement* _element, std::wstring _comment);
	static TiXmlElement* FirstChildElement(
		TiXmlDocument& _doc, const std::wstring& _value);
	static TiXmlElement* FirstChildElement(
		TiXmlElement* _element, const std::wstring& _value);
	static std::wstring Value(TiXmlElement* _element);

	static std::wstring Name(TiXmlAttribute* _attribute);
	static std::wstring Value(TiXmlAttribute* _attribute);
	static int ValueInt(TiXmlAttribute* _attribute);
	static float ValueFloat(TiXmlAttribute* _attribute);
	static void SetAttribute(
		TiXmlElement* _element, std::wstring _name, std::wstring _value);
	static void SetAttribute(
		TiXmlElement* _element, std::wstring _name, int _value);
	static void SetAttribute(
		TiXmlElement* _element, std::wstring _name, float _value);
	static bool GetAttributeValue(
		TiXmlElement* _element, std::wstring _attribute, std::wstring& _value);
	static bool GetAttributeValueInt(
		TiXmlElement* _element, std::wstring _attribute, int* _value);
	static bool GetAttributeValueFloat(
		TiXmlElement* _element, std::wstring _attribute, float* _value);
};
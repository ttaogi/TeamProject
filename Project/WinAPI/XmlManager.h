#pragma once

#include "SingletonBase.h"
#include "tinyxml.h"

class XmlManager : public SingletonBase<XmlManager> {
private:
public:
	XmlManager();
	~XmlManager();

	HRESULT init();
	void release();

	void loadXml();
	void saveXml();

	static bool loadFile(
		TiXmlDocument& _doc, const std::string& _fileName);
	static bool saveFile(
		TiXmlDocument& _doc, const std::string& _fileName);
	static void addDeclaration(
		TiXmlDocument& _doc, std::string _version,
		std::string _encoding, std::string _standAlone);
	static void addComment(
		TiXmlDocument& _doc, std::string _comment);

	static TiXmlElement* createElement(std::string _value);
	static void addComment(
		TiXmlElement* _element, std::string _comment);
	static TiXmlElement* firstChildElement(
		TiXmlDocument& _doc, const std::string& _value);
	static TiXmlElement* firstChildElement(
		TiXmlElement* _element, const std::string& _value);
	static std::string value(TiXmlElement* _element);

	static std::string name(TiXmlAttribute* _attribute);
	static std::string value(TiXmlAttribute* _attribute);
	static int valueInt(TiXmlAttribute* _attribute);
	static float valueFloat(TiXmlAttribute* _attribute);
	static double valueDouble(TiXmlAttribute* _attribute);
	static void setAttribute(
		TiXmlElement* _element, std::string _name, std::string _value);
	static void setAttribute(
		TiXmlElement* _element, std::string _name, int _value);
	static void setAttribute(
		TiXmlElement* _element, std::string _name, float _value);
	static bool getAttributeValue(
		TiXmlElement* _element, std::string _attribute, std::string& _value);
	static bool getAttributeValueInt(
		TiXmlElement* _element, std::string _attribute, int* _value);
	static bool getAttributeValueFloat(
		TiXmlElement* _element, std::string _attribute, float* _value);
	static bool getAttributeValueDouble(
		TiXmlElement* _element, std::string _attribute, double* _value);
};
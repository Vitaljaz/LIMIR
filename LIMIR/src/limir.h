#pragma once
#include <iostream>
#include <vector>

#include "../tinyXML/tinyxml2.h"

#define SAVE(x) t_obj->saveField((x), #x)
#define XMLCheckResult(a_eResult) if (a_eResult != XML_SUCCESS) { printf("Error: %i\n", a_eResult);}

using namespace tinyxml2;

class LiMir 
{
private:
	XMLDocument doc;
	XMLElement* parent;
	bool isChild = false;
	const char* filename;

	void createNewFile();
	void openFile();
	void saveFile();

public:
	LiMir() = delete;

	LiMir(const char* t_filename) : filename(t_filename) {}

	template<class T>
	void serialize(T& obj)
	{
		createNewFile();
		openFile();
		obj.save(this);
		saveFile();
	}

	template<class T>
	void saveField(T& obj, const char* name)
	{
		XMLNode* pRoot = doc.FirstChild();

		XMLElement* pObject = doc.NewElement(name);
		pObject->SetAttribute("Object", 0);
		pRoot->InsertEndChild(pObject);

		isChild = true;
		parent = pObject;
		obj.save(this);
		pObject->SetAttribute("class_id", 1);
		pRoot->InsertEndChild(pObject);
		isChild = false;
	}

	template <>
	void saveField<int>(int& x, const char* name)
	{
		std::cout << "[LOG]: Request save field: " << name << " " << x << std::endl;
		XMLElement* pElement = doc.NewElement(name);
		pElement->SetText(x);

		if (isChild)
		{
			parent->InsertEndChild(pElement);
		}
		else
		{
			XMLNode *pRoot = doc.FirstChild();
			pRoot->InsertEndChild(pElement);
		}
	}

	template <>
	void saveField<double>(double& x, const char* name)
	{
		std::cout << "[LOG]: Request save field: " << name << " " << x << std::endl;
		XMLElement* pElement = doc.NewElement(name);
		pElement->SetText(x);

		if (isChild)
		{
			parent->InsertEndChild(pElement);
		}
		else
		{
			XMLNode *pRoot = doc.FirstChild();
			pRoot->InsertEndChild(pElement);
		}
	}

	template <>
	void saveField<float>(float& x, const char* name)
	{
		std::cout << "[LOG]: Request save field: " << name << " " << x << std::endl;
		XMLElement* pElement = doc.NewElement(name);
		pElement->SetText(x);

		if (isChild)
		{
			parent->InsertEndChild(pElement);
		}
		else
		{
			XMLNode *pRoot = doc.FirstChild();
			pRoot->InsertEndChild(pElement);
		}
	}

	template <>
	void saveField<char>(char& x, const char* name)
	{
		std::cout << "[LOG]: Request save field: " << name << " " << x << std::endl;
		XMLElement* pElement = doc.NewElement(name);
		pElement->SetText(x);

		if (isChild)
		{
			parent->InsertEndChild(pElement);
		}
		else
		{
			XMLNode *pRoot = doc.FirstChild();
			pRoot->InsertEndChild(pElement);
		}
	}

	void saveField(std::vector<int> v, const char* name);

	~LiMir() = default;
};
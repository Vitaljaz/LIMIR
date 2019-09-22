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

public:
	LiMir() = delete;

	LiMir(const char* t_filename) : filename(t_filename) {}

	template<class T>
	void serialize(T& obj)
	{
		createNewFile();
		obj.save(this);
	}

	template<class T>
	void saveField(T& obj, const char* name)
	{
		std::cout << "FIELD: " << name;
		XMLError eResult = doc.LoadFile(filename);
		XMLCheckResult(eResult);
		XMLNode *pRoot = doc.FirstChild();

		XMLElement * pElement = doc.NewElement(name);
		pElement->SetAttribute("Object", 0);
		pRoot->InsertEndChild(pElement);
		doc.SaveFile(filename);

		isChild = true;

		obj.save(this);

		isChild = false;
		std::cout << "doshel";
	}

	template <>
	void saveField<int>(int& x, const char* name)
	{
		std::cout << "[LOG]: Request save field: " << name << " " << x << std::endl;
		XMLError eResult = doc.LoadFile(filename);
		XMLCheckResult(eResult);

		XMLElement * pElement = doc.NewElement(name);
		pElement->SetText(x);


		// need fix
		if (isChild)
		{
			XMLNode *pRoot = doc.FirstChildElement();
			XMLElement* old = pRoot->FirstChildElement();
			old->InsertEndChild(pElement);
		}
		else
		{
			XMLNode *pRoot = doc.FirstChild();
			pRoot->InsertEndChild(pElement);
		}

		doc.SaveFile(filename);
	}

	template <>
	void saveField<double>(double& x, const char* name)
	{
		std::cout << "[LOG]: Request save field: " << name << " " << x << std::endl;
		XMLError eResult = doc.LoadFile(filename);
		XMLCheckResult(eResult);
		XMLNode* pRoot = doc.FirstChild();

		XMLElement* pElement = doc.NewElement(name);
		pElement->SetText(x);
		pRoot->InsertEndChild(pElement);

		doc.SaveFile(filename);
	}

	template <>
	void saveField<float>(float& x, const char* name)
	{
		std::cout << "[LOG]: Request save field: " << name << " " << x << std::endl;
		XMLError eResult = doc.LoadFile(filename);
		XMLCheckResult(eResult);
		XMLNode* pRoot = doc.FirstChild();

		XMLElement* pElement = doc.NewElement(name);
		pElement->SetText(x);
		pRoot->InsertEndChild(pElement);

		doc.SaveFile(filename);
	}

	template <>
	void saveField<char>(char& x, const char* name)
	{
		std::cout << "[LOG]: Request save field: " << name << " " << x << std::endl;
		XMLError eResult = doc.LoadFile(filename);
		XMLCheckResult(eResult);
		XMLNode* pRoot = doc.FirstChild();

		XMLElement* pElement = doc.NewElement(name);
		pElement->SetText(x);
		pRoot->InsertEndChild(pElement);

		doc.SaveFile(filename);
	}

	void saveField(std::vector<int> v, const char* name);


	~LiMir() {}
};
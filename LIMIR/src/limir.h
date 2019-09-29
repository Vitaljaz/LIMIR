#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <typeinfo>

#include "../tinyXML/tinyxml2.h"

#define MASTER(x) t_obj->masterField((x), #x)
#define MASTER_OBJ(x) t_obj->masterObject((x), #x)
#define MASTER_OBJ_PTR(x) t_obj->masterObjectPointer((x), #x)
#define MASTER_OBJ_REF(x) t_obj->masterObjectReference((x), #x)
#define MASTER_INT_PTR(x) t_obj->masterIntPointer((x), #x)

#define XMLCheckResult(a_eResult) if (a_eResult != XML_SUCCESS) { printf("Error: %i\n", a_eResult);}

using namespace tinyxml2;

struct classInformation
{
	std::string className;
	int uniqID;
};

class LiMir 
{
private:
	XMLDocument doc;
	XMLElement* parent;
	bool isChild = false;
	const char* filename;
	const int SAVE_MODE = 0;
	const int LOAD_MODE = 1;
	int liMirMode = 0;

	std::vector<classInformation> classList;

	int findClassInList(const char* name);
	int addToClassList(const char* name);

	void createNewFile();
	void openFile();
	void saveFile();

	void saveField(int& x, const char* name);
	void saveField(double& x, const char* name);
	void saveField(float& x, const char* name);
	void saveField(std::vector<int>& v, const char* name);
	void savePointer(int*& x, const char* name);
	void loadField(int& x, const char* name);
	void loadField(double& x, const char* name);
	void loadField(float& x, const char* name);
	void loadField(std::vector<int>& v, const char* name);
	void loadPointer(int*& x, const char* name);

	XMLElement* findByName(const char* name);

	template <class T>
	void saveObject(T& obj, const char* name)
	{
		int ID = findClassInList(typeid(obj).name());
		if (ID == -1)
		{
			ID = addToClassList(typeid(obj).name());
		}
		XMLElement* pElement = doc.NewElement(name);
		pElement->SetAttribute("class_object", 0);
		pElement->SetAttribute("class_id", ID);

		XMLNode *pRoot = doc.FirstChild();
		pRoot->InsertEndChild(pElement);
	}


	template <class T>
	void saveObjectReference(T& x, const char* name)
	{
		int ID = findClassInList(typeid(x).name());
		if (ID == -1)
		{
			ID = addToClassList(typeid(x).name());
		}
		XMLElement* pElement = doc.NewElement(name);
		pElement->SetAttribute("class_object_reference", 0);
		pElement->SetAttribute("class_id", ID);

		XMLNode *pRoot = doc.FirstChild();
		pRoot->InsertEndChild(pElement);
	}

	template <class T>
	void saveObjectPointer(T*& x, const char* name)
	{
		//std::cout << typeid(x).name();
		int ID = findClassInList(typeid(x).name());
		if (ID == -1)
		{
			ID = addToClassList(typeid(x).name());
		}
		XMLElement* pElement = doc.NewElement(name);
		pElement->SetAttribute("class_object_pointer", 0);
		pElement->SetAttribute("class_id", ID);

		XMLNode *pRoot = doc.FirstChild();
		pRoot->InsertEndChild(pElement);
	}

public:
	LiMir() = delete;

	LiMir(const char* t_filename) : filename(t_filename) {}

	template <class T>
	void serialize(T& obj)
	{
		addToClassList(typeid(obj).name());
		liMirMode = SAVE_MODE;
		createNewFile();
		openFile();
		obj.master(this);
		saveFile();
	}

	template <class T>
	void deserialize(T& obj)
	{
		liMirMode = LOAD_MODE;
		openFile();
		obj.master(this);
		saveFile();
	}

	template <class T>
	void masterField(T& x, const char* name)
	{
		if (liMirMode == SAVE_MODE)
			saveField(x, name);
		else
			loadField(x, name);
	}

	template <class T>
	void masterObject(T& x, const char* name)
	{
		if (liMirMode == SAVE_MODE)
			saveObject(x, name);
	}

	template <class T>
	void masterObjectPointer(T*& x, const char* name)
	{
		if (liMirMode == SAVE_MODE)
			saveObjectPointer(x, name);
	}

	template <class T>
	void masterObjectReference(T& x, const char* name)
	{
		if (liMirMode == SAVE_MODE)
			saveObjectReference(x, name);
	}

	void masterIntPointer(int*& x, const char* name);
	~LiMir() = default;
};
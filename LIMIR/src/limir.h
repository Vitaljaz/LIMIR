#pragma once
#include <iostream>
#include <vector>

#include "../tinyXML/tinyxml2.h"

#define SAVE(x) t_obj->saveField((x), #x)
#define SAVE_OBJ(x) t_obj->saveObject((x), #x)
#define SAVE_PTR(x) t_obj->savePointer((x), #x)

#define LOAD(x) t_obj->loadField((x), #x)
#define LOAD_PTR(x) t_obj->loadPointer((x), #x)

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

	XMLElement* findByName(const char* name);

public:
	LiMir() = delete;

	LiMir(const char* t_filename) : filename(t_filename) {}

	template <class T>
	void serialize(T& obj)
	{
		createNewFile();
		openFile();
		obj.save(this);
		saveFile();
	}

	template <class T>
	void deserialize(T& obj)
	{
		openFile();
		obj.load(this);
		saveFile();
	}

	template <class T>
	void saveObject(T& obj, const char* name)
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

	~LiMir() = default;
};
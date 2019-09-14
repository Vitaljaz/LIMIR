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

	void saveField(const int& x, const char* name);
	void saveField(const double& x, const char* name);
	void saveField(const float& x, const char* name);
	void saveField(const char& x, const char* name);
	void saveField(std::vector<int> v, const char* name);


	~LiMir() {}
};
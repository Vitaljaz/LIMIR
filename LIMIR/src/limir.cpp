#include "limir.h"

int LiMir::findClassInList(const char * name)
{
	for (auto i : classList)
	{
		if (i.className == name)
			return i.uniqID;
	}
	return -1;
}

int LiMir::addToClassList(const char * name)
{
	if (findClassInList(name) == -1)
	{
		classInformation t;
		t.className = name;
		t.uniqID = classList.size();
		classList.push_back(t);
		return t.uniqID;
	}
	return -1;
}

void LiMir::createNewFile()
{
	std::cout << "[LOG]: Request create new file with name " << filename << std::endl;
	XMLNode* pRoot = doc.NewElement("Object");
	doc.InsertFirstChild(pRoot);
	XMLError eResult = doc.SaveFile(filename);
	XMLCheckResult(eResult);
}

void LiMir::openFile()
{
	XMLError eResult = doc.LoadFile(filename);
	XMLCheckResult(eResult);
}

void LiMir::saveFile()
{
	doc.SaveFile(filename);
}

XMLElement * LiMir::findByName(const char * name)
{
	XMLNode* pRoot = doc.FirstChild();
	if (pRoot == nullptr)
	{
		std::cout << "ERROR: " << XML_ERROR_FILE_READ_ERROR << std::endl;
		return nullptr;
	}

	XMLElement* pElement = pRoot->FirstChildElement(name);
	if (pElement == nullptr)
	{
		std::cout << "ERROR: " << XML_ERROR_PARSING_ELEMENT << std::endl;
		return nullptr;
	}

	return pElement;
}

void LiMir::masterIntPointer(int *& x, const char * name)
{
	if (liMirMode == SAVE_MODE)
		savePointer(x, name);
	else
		loadPointer(x, name);
}

void LiMir::saveField(int & x, const char * name)
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

void LiMir::saveField(double & x, const char * name)
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

void LiMir::saveField(float & x, const char * name)
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

void LiMir::savePointer(int *& x, const char * name)
{
	std::cout << "[LOG]: Request save pointer: " << name << " " << x << std::endl;
	XMLElement* pElement = doc.NewElement(name);
	pElement->SetText(*x);

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

void LiMir::saveField(std::vector<int>& v, const char* name)
{
	std::cout << "[LOG]: Request save field: " << name << " " << "Vector " << std::endl;
	XMLElement* pVector = doc.NewElement(name);
	XMLNode* pRoot = doc.FirstChild();

	if (isChild)
	{
		parent->InsertEndChild(pVector);
	}
	else
	{
		pRoot->InsertEndChild(pVector);
	}

	for (const auto & item : v)
	{
		XMLElement* pVectorElement = doc.NewElement("Item");
		pVectorElement->SetText(item);

		pVector->InsertEndChild(pVectorElement);
	}

	pVector->SetAttribute("itemCount", v.size());

	if (isChild)
	{
		parent->InsertEndChild(pVector);
	}
	else
	{
		pRoot->InsertEndChild(pVector);
	}
}

void LiMir::loadField(int& x, const char* name)
{
	XMLElement* pElement = findByName(name);
	if (pElement == nullptr)
	{
		std::cout << "ERROR: " << XML_ERROR_PARSING << std::endl;
		return;
	}
	XMLError eResult = pElement->QueryIntText(&x);
	XMLCheckResult(eResult);
}

void LiMir::loadField(double & x, const char * name)
{
	XMLElement* pElement = findByName(name);
	if (pElement == nullptr)
	{
		std::cout << "ERROR: " << XML_ERROR_PARSING << std::endl;
		return;
	}
	XMLError eResult = pElement->QueryDoubleText(&x);
	XMLCheckResult(eResult);
}

void LiMir::loadField(float & x, const char * name)
{
	XMLElement* pElement = findByName(name);
	if (pElement == nullptr)
	{
		std::cout << "ERROR: " << XML_ERROR_PARSING << std::endl;
		return;
	}
	XMLError eResult = pElement->QueryFloatText(&x);
	XMLCheckResult(eResult);
}

void LiMir::loadField(std::vector<int>& v, const char * name)
{
	XMLElement* pElement = findByName(name);
	if (pElement == nullptr)
	{
		std::cout << "ERROR: " << XML_ERROR_PARSING << std::endl;
		return;
	}

	XMLElement* pListElement = pElement->FirstChildElement("Item");
	std::vector<int> vecList;

	while (pListElement != nullptr)
	{
		int iOutListValue;
		XMLError eResult = pListElement->QueryIntText(&iOutListValue);
		XMLCheckResult(eResult);

		vecList.push_back(iOutListValue);
		pListElement = pListElement->NextSiblingElement("Item");
	}

	v = vecList;
}

void LiMir::loadPointer(int *& x, const char * name)
{
	XMLElement* pElement = findByName(name);
	if (pElement == nullptr)
	{
		std::cout << "ERROR: " << XML_ERROR_PARSING << std::endl;
		return;
	}
	XMLError eResult = pElement->QueryIntText(x);
	XMLCheckResult(eResult);
}

#include "limir.h"

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

void LiMir::saveField(std::vector<int> v, const char* name)
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

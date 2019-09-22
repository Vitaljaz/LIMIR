#include "limir.h"

void LiMir::createNewFile()
{
	std::cout << "[LOG]: Request create new file with name " << filename << std::endl;
	XMLNode *pRoot = doc.NewElement("Object");
	doc.InsertFirstChild(pRoot);
	XMLError eResult = doc.SaveFile(filename);
	XMLCheckResult(eResult);
}

void LiMir::saveField(std::vector<int> v, const char* name)
{
	std::cout << "[LOG]: Request save field: " << name << " " << "Vector " << std::endl;
	XMLError eResult = doc.LoadFile(filename);
	XMLCheckResult(eResult);
	XMLNode* pRoot = doc.FirstChild();

	XMLElement* pElement = doc.NewElement(name);
	pRoot->InsertEndChild(pElement);

	for (const auto & item : v)
	{
		XMLElement* pVectorElement = doc.NewElement("Item");
		pVectorElement->SetText(item);

		pElement->InsertEndChild(pVectorElement);
	}

	pElement->SetAttribute("itemCount", v.size());
	pRoot->InsertEndChild(pElement);
	
	doc.SaveFile(filename);
}

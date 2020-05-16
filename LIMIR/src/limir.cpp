#include "limir.h"

int LiMir::FindClassInList(const char* name) {
  for (auto& i : class_list_) {
	if (i.class_name == name)
      return i.uniq_id;
  }
  return -1;
}

int LiMir::AddToClassList(const char* name) {
  if (FindClassInList(name) == -1) {
	ClassInformation t;
	t.class_name = name;
	t.uniq_id = class_list_.size();
	class_list_.push_back(t);
	return t.uniq_id;
  }
  return -1;
}

void LiMir::CreateNewFile() {
  XMLElement* pElement = doc_.NewElement(object_name_);
  pElement->SetAttribute("class_id", 0);
  XMLNode* pRoot = pElement;
  doc_.InsertFirstChild(pRoot);
  XMLError eResult = doc_.SaveFile(filename_);
  XMLCheckResult(eResult);
}

void LiMir::OpenFile() {
  XMLError eResult = doc_.LoadFile(filename_);
  XMLCheckResult(eResult);
}

void LiMir::SaveFile() {
  doc_.SaveFile(filename_);
}

XMLElement * LiMir::FindByName(const char* name) {
  XMLNode* pRoot = doc_.FirstChild();
  if (pRoot == nullptr) {
    std::cout << "ERROR[NAME]: " << XML_ERROR_FILE_READ_ERROR << std::endl;
	return nullptr;
  }

  if (!class_names_.empty()) {
    XMLElement* pElement = pRoot->FirstChildElement(class_names_.back());
    XMLElement* pChild = pElement->FirstChildElement(name);
    if (pChild == nullptr) {
	  std::cout << "ERROR[NAME]: " << XML_ERROR_PARSING_ELEMENT << std::endl;
	  return nullptr;
    }
	return pChild;
	} else {
	  XMLElement* pElement = pRoot->FirstChildElement(name);
	  if (pElement == nullptr) {
	    std::cout << "ERROR[NAME]: " << XML_ERROR_PARSING_ELEMENT << std::endl;
	    return nullptr;
	  }
    return pElement;
	}
}

void LiMir::MasterIntPointer(int *& x, const char* name) {
  if (limir_mode_ == kSaveMode)
	SavePointer(x, name);
  else
	LoadPointer(x, name);
}

void LiMir::SaveField(const int x, const char* name) {
  XMLElement* pElement = doc_.NewElement(name);
  pElement->SetText(x);

  if (!parents_.empty()) {
    parents_.back()->InsertEndChild(pElement);
  } else {
    XMLNode *pRoot = doc_.FirstChild();
    pRoot->InsertEndChild(pElement);
  }
}

void LiMir::SaveField(const double x, const char* name) {
  XMLElement* pElement = doc_.NewElement(name);
  pElement->SetText(x);

  if (!parents_.empty()) {
     parents_.back()->InsertEndChild(pElement);
  } else {
    XMLNode *pRoot = doc_.FirstChild();
	pRoot->InsertEndChild(pElement);
  }
}

void LiMir::SaveField(const float x, const char* name) {
  XMLElement* pElement = doc_.NewElement(name);
  pElement->SetText(x);

  if (!parents_.empty()) {
	parents_.back()->InsertEndChild(pElement);
  } else {
	XMLNode *pRoot = doc_.FirstChild();
	pRoot->InsertEndChild(pElement);
  }
}

void LiMir::SavePointer(int *& x, const char* name) {
  XMLElement* pElement = doc_.NewElement(name);
  pElement->SetText(*x);

  if (!parents_.empty()) {
	parents_.back()->InsertEndChild(pElement);
  } else {
    XMLNode *pRoot = doc_.FirstChild();
    pRoot->InsertEndChild(pElement);
  }
}

void LiMir::SaveField(const std::vector<int>& v, const char* name) {
  XMLElement* pVector = doc_.NewElement(name);
  XMLNode* pRoot = doc_.FirstChild();

  if (!parents_.empty()) {
	parents_.back()->InsertEndChild(pVector);
  } else {
    pRoot->InsertEndChild(pVector);
  }

  for (const auto& item : v) {
	XMLElement* pVectorElement = doc_.NewElement("Item");
	pVectorElement->SetText(item);
	pVector->InsertEndChild(pVectorElement);
  }

  pVector->SetAttribute("itemCount", v.size());

  if (!parents_.empty()) {
	parents_.back()->InsertEndChild(pVector);
  } else {
    pRoot->InsertEndChild(pVector);
  }
}

void LiMir::LoadField(int& x, const char* name) {
  XMLElement* pElement = FindByName(name);
  if (pElement == nullptr) {
	std::cout << "ERROR[INT]: " << XML_ERROR_PARSING << std::endl;
	return;
  }
  XMLError eResult = pElement->QueryIntText(&x);
  XMLCheckResult(eResult);
}

void LiMir::LoadField(double& x, const char* name) {
  XMLElement* pElement = FindByName(name);
  if (pElement == nullptr) {
    std::cout << "ERROR[DOUBLE]: " << XML_ERROR_PARSING << std::endl;
    return;
  }
  XMLError eResult = pElement->QueryDoubleText(&x);
  XMLCheckResult(eResult);
}

void LiMir::LoadField(float& x, const char* name) {
  XMLElement* pElement = FindByName(name);
  if (pElement == nullptr) {
    std::cout << "ERROR[FLOAT]: " << XML_ERROR_PARSING << std::endl;
    return;
  }
  XMLError eResult = pElement->QueryFloatText(&x);
  XMLCheckResult(eResult);
}

void LiMir::LoadField(std::vector<int>& v, const char* name) {
  XMLElement* pElement = FindByName(name);
  if (pElement == nullptr) {
    std::cout << "ERROR[VECTOR]: " << XML_ERROR_PARSING << std::endl;
    return;
  }

  XMLElement* pListElement = pElement->FirstChildElement("Item");
  std::vector<int> vec_list;

  while (pListElement != nullptr) {
    int out_list_value = 0;
    XMLError eResult = pListElement->QueryIntText(&out_list_value);
    XMLCheckResult(eResult);
    vec_list.push_back(out_list_value);
    pListElement = pListElement->NextSiblingElement("Item");
  }
  v = vec_list;
}

void LiMir::LoadPointer(int *& x, const char* name) {
  XMLElement* pElement = FindByName(name);
  if (pElement == nullptr) {
    std::cout << "ERROR[INT_PTR]: " << XML_ERROR_PARSING << std::endl;
    return;
  }
  XMLError eResult = pElement->QueryIntText(x);
  XMLCheckResult(eResult);
}

#ifndef LIMIR_SRC_LIMIR_H_
#define LIMIR_SRC_LIMIR_H_

#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <typeinfo>
#include <type_traits>

#include "../tinyXML/tinyxml2.h"

#define NAME_OBJECT(x) (#x)
#define MASTER(x) obj->MasterField((x), #x)
#define MASTER_OBJ(x) obj->MasterObject((x), #x)
#define MASTER_OBJ_PTR(x) obj->MasterObjectPointer((x), #x)
#define MASTER_OBJ_REF(x) obj->MasterObjectReference((x), #x)
#define MASTER_INT_PTR(x) obj->MasterIntPointer((x), #x)
#define MASTER_BASE_OBJ(x) obj->MasterBaseObject((dynamic_cast<x *>(this)), #x)

#define XMLCheckResult(a_eResult) if (a_eResult != XML_SUCCESS) { printf("Error: %i\n", a_eResult);}

using namespace tinyxml2;

struct ClassInformation {
  std::string class_name;
  int uniq_id;
};

class LiMir {
 public:
  LiMir() {}
  explicit LiMir(const char* filename) : filename_(filename) {}
  ~LiMir() {}

  template<class T>
  void Serialize(T& object, const char* name) {
    AddToClassList(typeid(object).name());
    object_name_ = name;
    limir_mode_ = kSaveMode;
    CreateNewFile();
    OpenFile();
    object.Master(this);
    SaveFile();
  }

  template<class T>
  void Deserialize(T& object) {
    limir_mode_ = kLoadMode;
    OpenFile();
    object.Master(this);
    SaveFile();
  }

  template<class T>
  void MasterField(T& x, const char* name) {
    if (limir_mode_ == kSaveMode)
      SaveField(x, name);
    else
      LoadField(x, name);
  }

  template<class T>
  void MasterObject(T& object, const char* name) {
    if (limir_mode_ == kSaveMode)
      SaveObject(object, name);
  }

  template<class T>
  void MasterObjectPointer(T*& object_ptr, const char* name) {
    if (object_ptr == nullptr)
      return;

    if (limir_mode_ == kSaveMode)
      SaveObjectPointer(object_ptr, name);
  }

  template <class T>
  void MasterObjectReference(T& object_ref, const char* name) {
    if (limir_mode_ == kSaveMode)
      SaveObjectReference(object_ref, name);
  }

  template<class T>
  void MasterBaseObject(T* base_object, const char* name) {
    if (base_object == nullptr)
      return;

    if (limir_mode_ == kSaveMode)
      SaveBaseObject(base_object, name);
    else
      LoadBaseObject(base_object, name);
  }

  void MasterIntPointer(int*& x, const char* name);
    
 private:
  int FindClassInList(const char* name);
  int AddToClassList(const char* name);
  void CreateNewFile();
  void OpenFile();
  void SaveFile();
  void SaveField(const std::vector<int>& v, const char* name);
  void SavePointer(int*& x, const char* name);
  void LoadField(int& x, const char* name);
	void LoadField(double& x, const char* name);
	void LoadField(float& x, const char* name);
  void LoadField(std::vector<int>& v, const char* name);
  void LoadPointer(int*& x, const char* name);

  XMLElement* FindByName(const char* name);

	template<class T>
	void SaveField(const T& x, const char* name) {
		XMLElement* pElement = doc_.NewElement(name);
		pElement->SetText(x);

		if (!parents_.empty()) {
			parents_.back()->InsertEndChild(pElement);
		} else {
			XMLNode* pRoot = doc_.LastChild()->FirstChild();
			pRoot->InsertEndChild(pElement);
		}
	}

  template<class T>
  void SaveObject(T& object, const char* name) {
    int id = FindClassInList(typeid(object).name());

    if (id == -1)
      id = AddToClassList(typeid(object).name());

    XMLElement* pElement = doc_.NewElement(name);
    pElement->SetAttribute("class_object", 0);
    pElement->SetAttribute("class_id", id);

    if (!parents_.empty()) {
      parents_.back()->InsertEndChild(pElement);
    } else {
			XMLNode* pRoot = doc_.LastChild()->FirstChild();
      pRoot->InsertEndChild(pElement);
    }
  }

  template<class T>
  void SaveObjectReference(T& object_ref, const char* name) {
    int id = FindClassInList(typeid(object_ref).name());

    if (id == -1)
      id = AddToClassList(typeid(object_ref).name());

    XMLElement* pElement = doc_.NewElement(name);
    pElement->SetAttribute("class_object_reference", 0);
    pElement->SetAttribute("class_id", id);

    if (!parents_.empty()) {
      parents_.back()->InsertEndChild(pElement); 
    } else {
			XMLNode* pRoot = doc_.LastChild()->FirstChild();
      pRoot->InsertEndChild(pElement);
    }
  }

  template<class T>
  void SaveObjectPointer(T*& object_ptr, const char* name) {
    int id = FindClassInList(typeid(object_ptr).name());

    if (id == -1)
      id = AddToClassList(typeid(object_ptr).name());

    XMLElement* pElement = doc_.NewElement(name);
    pElement->SetAttribute("class_object_pointer", 0);
    pElement->SetAttribute("class_id", id);

    if (!parents_.empty()) {
      parents_.back()->InsertEndChild(pElement);
    } else {
			XMLNode* pRoot = doc_.LastChild()->FirstChild();
			pRoot->InsertEndChild(pElement);
    }
  }

  template<class T>
  void SaveBaseObject(T* base_object, const char* name) {
    int id = FindClassInList(typeid(base_object).name());

		if (id == -1)
			id = AddToClassList(typeid(base_object).name());
		else
			return;

		XMLNode* pRoot = doc_.LastChild()->FirstChild();
    XMLElement* pElement = doc_.NewElement(name);
    pElement->SetAttribute("class_id", id);

    parents_.push_back(pElement);
    base_object->Master(this);
    parents_.pop_back();
    pRoot->InsertEndChild(pElement);
  }

  template<class T>
  void LoadBaseObject(T* base_object, const char* name) {
    class_names_.push_back(name);
    base_object->Master(this);
    class_names_.pop_back();
  }

  XMLDocument doc_;
  const char* filename_;
  const char* object_name_;
  const int kSaveMode = 0;
  const int kLoadMode = 1;
  int limir_mode_ = 0;
  std::vector<ClassInformation> class_list_;
  std::vector<const char*> class_names_;
  std::vector<XMLElement*> parents_;
};

#endif // LIMIR_SRC_LIMIR_H_
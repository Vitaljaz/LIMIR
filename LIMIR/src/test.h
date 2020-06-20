#pragma once
#include "limir.h"
#include <memory>

class Test {
 public:
	Test(const std::string& filename);
	~Test() = default;

	template<class T>
	void Run(T& object, const char* object_name) {
		limir_ = std::make_unique<LiMir>(serialization_filename_.c_str());
		limir_->Serialize(object, object_name);
		object.ClearFields();
		limir_->Deserialize(object);
		limir_.reset();
		limir_ = std::make_unique<LiMir>(deserialization_filename_.c_str());
		limir_->Serialize(object, object_name);
		limir_.reset();
	}

	void SetFilename(const std::string& filename);

private:
	void CreateFilenames();

	std::unique_ptr<LiMir> limir_;
	std::string filename_;
	std::string serialization_filename_;
	std::string deserialization_filename_;
};
#include "test.h"

Test::Test(const std::string & filename) : filename_(filename) {
	CreateFilenames();
}

void Test::SetFilename(const std::string & filename) {
	filename_ = filename;
	CreateFilenames();
}

void Test::CreateFilenames() {
	serialization_filename_ = "serialize_" + filename_;
	deserialization_filename_ = "deserialize_" + filename_;
}

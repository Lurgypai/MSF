#include "stdafx.h"
#include "DataObject.h"

namespace msf {

	DataObject::DataObject() : input{ nullptr }, tag(tagCounter++) {}

	msf::DataObject::DataObject(std::unique_ptr<DInputComponent>& in) : input{ in->clone() }, tag{tagCounter++} {}

	void DataObject::update(std::vector<Action>& actions) {
		input->update(actions);
	}

bool DataObject::hasInput() {
	return (input.get() != nullptr);
}

Scene * DataObject::getScene() {
	return scene;
}

DataObject::~DataObject() {}

//finish
bool DataObject::operator==(const DataObject & other) {
	return scene == other.scene;
}

bool DataObject::operator!=(const DataObject & other) {
	return !(*this == other);
}

uint64_t DataObject::tagCounter = 0;

}
#include "stdafx.h"
#include "DataObject.h"

namespace msf {

DataObject::DataObject() : input{ nullptr }, tag(tagCounter++) {}

DataObject::~DataObject() {}

void DataObject::update() {
	input->update();
}

bool DataObject::hasInput() {
	return (input.get() != nullptr);
}

Scene * DataObject::getScene() {
	return scene;
}

bool DataObject::operator==(const DataObject & other) {
	return tag == other.tag;
}

bool DataObject::operator!=(const DataObject & other) {
	return tag != other.tag;
}

uint64_t DataObject::tagCounter = 0;
}
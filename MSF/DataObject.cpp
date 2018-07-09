#include "stdafx.h"
#include "DataObject.h"

namespace msf {

	DataObject::DataObject() : logic{ nullptr }, tag(tagCounter++), scene{nullptr} {}

DataObject::~DataObject() {}

void DataObject::update() {
	logic->update();
}

bool DataObject::hasInput() {
	return (logic.get() != nullptr);
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
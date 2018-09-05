#include "stdafx.h"
#include "DataObject.h"

namespace msf {

	DataObject::DataObject() : logic{ nullptr }, tag(tagCounter++), scene{ nullptr }, deleted{false} {}

DataObject::~DataObject() {}

void DataObject::update() {
	logic->update();
}

void DataObject::destroy() {
	deleted = true;
}

bool DataObject::hasInput() {
	return (logic.get() != nullptr);
}

bool DataObject::destroyed() {
	return deleted;
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
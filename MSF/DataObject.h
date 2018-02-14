#pragma once

#include <cstdint>

#include "Components.h"
#include "ActionQueue.h"

namespace msf {

class Scene;
class DInputComponent;

class DataObject
{
public:

	DataObject();
	~DataObject();

	void update();
	bool hasInput();
	Scene* getScene();

	template<typename T, typename... Args>
	void setInput(Args... args) {
		input = std::make_unique<T>(args...);
		input->owner = this;
	}

	bool operator==(const DataObject& other);
	bool operator!=(const DataObject& other);
private:
	friend class Scene;

	std::unique_ptr<DInputComponent> input;
	Scene* scene;
	uint64_t tag;
	static uint64_t tagCounter;
};

}
#pragma once

#include <cstdint>

#include "Components.h"
#include "ActionQueue.h"

namespace msf {

class Scene;
class DLogicComponent;

class DataObject
{
public:

	DataObject();
	~DataObject();

	void update();
	bool hasInput();
	Scene* getScene();

	template<typename T, typename... Args>
	void setLogic(Args... args) {
		logic = std::make_unique<T>(args...);
		logic->owner = this;
	}

	bool operator==(const DataObject& other);
	bool operator!=(const DataObject& other);
private:
	friend class Scene;

	std::unique_ptr<DLogicComponent> logic;
	Scene* scene;
	uint64_t tag;
	static uint64_t tagCounter;
};

}
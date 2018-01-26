#pragma once

#include <cstdint>

#include "Components.h"

namespace msf {

class Scene;
struct Action;
class DInputComponent;

class DataObject
{
public:

	DataObject();
	DataObject(std::unique_ptr<DInputComponent>& in);

	void update(std::vector<Action>& actions);

	bool hasInput();

	template<typename T, typename... Args>
	void setInput(Args... args) {
		input = std::make_unique<T>(args...);
		input->owner = this;
	}

	Scene* getScene();
	~DataObject();

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
#pragma once
#include <vector>
#include <memory>
#include "GameObject.h"

namespace msf {

class GameObjectManager {
public:
	GameObjectManager();
	~GameObjectManager();
	void update();

	addRegisterObject()
private:
	std::vector<std::unique_ptr<GameObject>> objects;
};

}
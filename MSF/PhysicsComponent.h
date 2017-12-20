#pragma once
#include "GameObject.h"

namespace msf {
class GameObject;
class PhysicsComponent {
public:
	virtual void update(GameObject& obj) = 0;
};
}
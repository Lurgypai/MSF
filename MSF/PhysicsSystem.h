#pragma once
#include "PhysicsComponent.h"
#include <vector>
#include <memory>

namespace msf {
class PhysicsSystem {
public:
	PhysicsSystem();
	~PhysicsSystem();
	void update();
	void registerComponent(PhysicsComponent& component_);
	void removeComponent(PhysicsComponent& component_);
private:
	std::vector<std::unique_ptr<PhysicsComponent>> components;
};
}
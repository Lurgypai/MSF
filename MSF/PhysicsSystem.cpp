#include "stdafx.h"
#include "PhysicsSystem.h"
namespace msf {
msf::PhysicsSystem::PhysicsSystem() : components{} {}

msf::PhysicsSystem::~PhysicsSystem() {}

void PhysicsSystem::update() {
	for (auto component : components) {
		component->ud
	}
}



}
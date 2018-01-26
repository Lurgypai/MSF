#include "stdafx.h"
#include "TestPhysicsComponent.h"
#include <sstream>
#include <cmath>
TestPhysicsComponent::TestPhysicsComponent(sf::RenderWindow* window) : velocity{}, maxVelocity{18}, rect{ 0, 0, 25, 25 }, isHeld{false}, window(window) {
}

void TestPhysicsComponent::update(const msf::Action & action) {
	rect.top = owner->y();
	rect.left = owner->x();

	if (!action.isNothing) {
		handleAction(action);
	}

	if (!isHeld) {
		if (velocity.magn > maxVelocity) {
			velocity.magn = maxVelocity;
		}

		if (rect.top + rect.height != 720) {
			if (rect.top + rect.height > 720) {
				owner->setPos(sf::Vector2f{ owner->getPos().x, 720.0f - (float)rect.height });
				rect.top = 720 - rect.height;
				velocity.magn = 0;
				velocity.angle = 90;
			}
			else if (rect.top + rect.height != 720) {
				velocity += msf::MVector(90, 1);
				owner->move(velocity.xComp(), velocity.yComp());
			}
		}
	}

	else {
		owner->setPos(sf::Vector2f(sf::Mouse::getPosition(*window)));
	}
}

std::unique_ptr<msf::PhysicsComponent> TestPhysicsComponent::clone() {
	return std::make_unique<TestPhysicsComponent>(*this);
}

bool TestPhysicsComponent::pollAction(msf::Action & action) {
	return false;
}

void TestPhysicsComponent::handleAction(const msf::Action & act) {
	std::stringstream actionStream{};
	actionStream.str(act.id);
	std::string id;
	std::string x;
	std::string y;
	std::getline(actionStream, id, '_');
	if (id == "click") {
		std::getline(actionStream, x, '_');
		std::getline(actionStream, y, '_');
		float x_ = stof(x);
		float y_ = stof(y);
		if (rect.contains(x_, y_)) {
			isHeld = true;
			if (isHeld) {
				velocity.angle = -90;
				velocity.magn = 0;
			}
		}
	}
	if (act.id == "drop") {
		isHeld = false;
	}
}

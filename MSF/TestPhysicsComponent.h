#pragma once
#include "Components.h"
#include "MVector.h"

class TestPhysicsComponent : public msf::PhysicsComponent {
public:
	TestPhysicsComponent(sf::RenderWindow* window);
	void update(const msf::Action& act);
	std::unique_ptr<msf::PhysicsComponent> clone();
	sf::RenderWindow* window;
	bool pollAction(msf::Action& action);
private:
	inline void handleAction(const msf::Action& act);
	sf::Rect<double> rect;
	bool isHeld;
	double maxVelocity;
	msf::MVector velocity;
};
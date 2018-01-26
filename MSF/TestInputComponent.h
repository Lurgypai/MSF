#pragma once
#include "Components.h"

class TestInputComponent : public msf::InputComponent {
public:
	TestInputComponent(sf::RenderWindow* window);
	void update(std::vector<msf::Action>& actions);
	std::unique_ptr<msf::InputComponent> clone();
	sf::RenderWindow* window;
	bool pollAction(msf::Action& action);
private:
	msf::Action act;
};
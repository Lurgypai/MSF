#include "stdafx.h"
#include "TestInputComponent.h"
#include <iostream>

TestInputComponent::TestInputComponent(sf::RenderWindow* window) : window{window} {}

void TestInputComponent::update(std::vector<msf::Action>& actions) {
	for (auto iter = actions.begin(); iter != actions.end(); iter++) {
		if (iter->id == "left_d") {
			sf::Vector2i pos = sf::Mouse::getPosition(*window);
			act.id = "click_" + std::to_string(pos.x) + "_" + std::to_string(pos.y);
			act.isNothing = false;
		}
		if (iter->id == "left_u") {
			act.id = "drop";
			act.isNothing = false;
		}
	}
}

std::unique_ptr<msf::InputComponent> TestInputComponent::clone() {
	return std::make_unique<TestInputComponent>(*this);
}

bool TestInputComponent::pollAction(msf::Action & action) {
	if (!act.isNothing) {
		action = act;
		act.isNothing = true;
		act.id = "";
		return true;
	}
	return false;
}

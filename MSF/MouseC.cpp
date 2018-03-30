#include "stdafx.h"
#include "MouseC.h"
#include "SFML/Window.hpp"

MouseC::MouseC(sf::RenderWindow* window) : window{ window } {}


MouseC::~MouseC()
{
}

void MouseC::readInputs() {
	sf::Vector2f pos{ sf::Mouse::getPosition(*window) };
	if (!lDown) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			lDown = true;
			buffer.push_back(std::make_shared<ClickAction>(Click::LDown, pos));
		}
	}
	else {
		if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			lDown = false;
			buffer.push_back(std::make_shared<ClickAction>(Click::LUp, pos));
		}
	}

	if (!rDown) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
			rDown = true;
			buffer.push_back(std::make_shared<ClickAction>(Click::RDown, pos));
		}
	}
	else {
		if (!sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
			rDown = false;
			buffer.push_back(std::make_shared<ClickAction>(Click::RUp, pos));
		}
	}
}

bool MouseC::pollInputs(std::shared_ptr<msf::Action>& action) {
	if (buffer.size() != 0) {
		action = buffer[buffer.size() - 1];
		buffer.pop_back();
		return true;
	}
	return false;
}

sf::Vector2f MouseC::getPos() {
	return sf::Vector2f{sf::Mouse::getPosition(*window)};
}

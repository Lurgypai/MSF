#include "stdafx.h"
#include "SimpleController.h"
#include "SFML\Window.hpp"
#include <iostream>

SimpleController::SimpleController() : LDown{ false }, RDown{false}
{
}

SimpleController::~SimpleController()
{
}

void SimpleController::readInputs() {
	msf::Action action{"", true};

	//rightclick
	if (!RDown) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
			action.id = "right_d";
			RDown = true;
			action.isNothing = false;
		}
	}
	else if (RDown) {

		if (!sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
			action.id = "right_u";
			RDown = false;
			action.isNothing = false;
		}
	}

	//leftclick
	if (!LDown) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			action.id = "left_d";
			LDown = true;
			action.isNothing = false;
		}
	}
	else if (LDown) {
		if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			action.id = "left_u";
			LDown = false;
			action.isNothing = false;
		}
	}
	actionBuffer.push_back(action);
}

bool SimpleController::pollInputs(msf::Action & action) {
	if (actionBuffer.size() > 0) {	
	action = actionBuffer.back();
	actionBuffer.pop_back();
	}
	return !action.isNothing;
}

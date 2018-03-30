#pragma once
#include "Controller.h"
#include "SFML\Graphics.hpp"

class ClickAction;

class MouseC : public msf::Controller {
public:
	enum Click {
		RDown,
		RUp,
		LDown,
		LUp
	};

	void readInputs() override;
	bool pollInputs(std::shared_ptr<msf::Action>& action) override;
	sf::Vector2f getPos();
	MouseC(sf::RenderWindow* window);
	~MouseC();
private:
	bool lDown;
	bool rDown;
	sf::RenderWindow* window;
	std::vector<std::shared_ptr<ClickAction>> buffer;
};

class ClickAction : public msf::Action
{
public:
	ClickAction(const MouseC::Click& click_, const sf::Vector2f& pos_) : Action{ 1, false }, click(click_), pos{ pos_ } {};
	~ClickAction() {};
	MouseC::Click click;
	sf::Vector2f pos;
};
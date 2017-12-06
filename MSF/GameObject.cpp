#include "stdafx.h"
#include "GameObject.h"

msf::GameObject::GameObject(void) :
	pos(0.0F, 0.0F)
	{}

msf::GameObject::GameObject(const sf::Vector2f & pos_) :
	pos(pos_)
{}

msf::GameObject::GameObject(const double & y_, const double & x_) :
	pos(x_, y_)
{}

msf::GameObject::~GameObject()
{
}

void msf::GameObject::update(void) {
	//update components, perhaps not though
}

double msf::GameObject::x() const {
	return pos.x;
}

sf::Vector2f msf::GameObject::getPos() const
{
	return pos;
}

double msf::GameObject::y() const
{
	return pos.y;
}

#include "stdafx.h"
#include "TestGraphicsComponent.h"
#include <iostream>

TestGraphicsComponent::TestGraphicsComponent(std::string filePath) : line{ sf::Vector2f(150, 1) }, line2{} {
	line.rotate(32);
	texture.loadFromFile(filePath);
	sprite.setTexture(texture);
}

TestGraphicsComponent::TestGraphicsComponent(TestGraphicsComponent & comp) {

}


void TestGraphicsComponent::update(const msf::Action & act, sf::RenderWindow & window) {
	line.setPosition(owner->getPos());
	window.draw(line);
}

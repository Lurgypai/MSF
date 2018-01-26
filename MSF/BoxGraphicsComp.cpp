#include "stdafx.h"
#include "BoxGraphicsComp.h"
#include <iostream>

BoxGraphicsComp::BoxGraphicsComp(std::string filePath) {
	texture.loadFromFile(filePath);
	sprite.setTexture(texture);
}

BoxGraphicsComp::BoxGraphicsComp(BoxGraphicsComp & comp) {
	texture = comp.texture;
	sprite.setTexture(texture);
}


void BoxGraphicsComp::update(const msf::Action & act, sf::RenderWindow & window) {
	sprite.setPosition(owner->getPos());
	window.draw(sprite);
}

std::unique_ptr<msf::GraphicsComponent> BoxGraphicsComp::clone() {
	return std::make_unique<BoxGraphicsComp>(*this);
}

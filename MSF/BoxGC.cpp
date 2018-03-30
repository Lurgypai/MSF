#include "stdafx.h"
#include "BoxGC.h"

BoxGC::BoxGC(const std::string & filePath) {
	texture.loadFromFile(filePath);
	sprite.setTexture(texture);
}

BoxGC::BoxGC(const BoxGC & other) {
	texture = other.texture;
	sprite.setTexture(texture);
}

BoxGC::~BoxGC()
{
}

void BoxGC::update(std::vector<msf::Action*>& act, sf::RenderWindow & window) {
	sprite.setPosition(owner->getPos());
	window.draw(sprite);
}

std::unique_ptr<msf::GraphicsComponent> BoxGC::clone()
{
	return std::make_unique<BoxGC>(*this);
}

#pragma once
#include "Components.h"

class BoxGraphicsComp : public msf::GraphicsComponent {
public:
	BoxGraphicsComp(std::string filePath);
	BoxGraphicsComp(BoxGraphicsComp& comp);
	void update(const msf::Action& act, sf::RenderWindow& window);
	std::unique_ptr<msf::GraphicsComponent> clone();
private:
	sf::Sprite sprite;
	sf::Texture texture;
};

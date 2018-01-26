#pragma once
#include "Components.h"

class TestGraphicsComponent : public msf::GraphicsComponent {
public:
	TestGraphicsComponent(std::string filePath);
	TestGraphicsComponent(TestGraphicsComponent& comp);
	void update(const msf::Action& act, sf::RenderWindow& window);
private:
	sf::Sprite sprite;
	sf::Texture texture;
	sf::RectangleShape line;
	sf::Vertex line2[2];
};

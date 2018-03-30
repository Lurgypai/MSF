#pragma once
#include "Components.h"
class BoxGC : public msf::GraphicsComponent
{
public:
	BoxGC(const std::string& filePath);
	BoxGC(const BoxGC& other);
	~BoxGC();

	void update(std::vector<msf::Action*>& act, sf::RenderWindow & window) override;
	std::unique_ptr<msf::GraphicsComponent> clone() override;
private:
	sf::Sprite sprite;
	sf::Texture texture;
};


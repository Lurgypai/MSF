#pragma once
#include "Components.h"
#include "GameObjectFactory.h"

class DataInComponent : public msf::DInputComponent {
public:
	DataInComponent(sf::RenderWindow* window, msf::Scene* scene);
	DataInComponent(const DataInComponent& other);
	void operator=(const DataInComponent& other);
	~DataInComponent();

	std::unique_ptr<msf::DInputComponent> clone();
	void update(std::vector<msf::Action>& actions);
private:
	sf::RenderWindow* window;
	msf::GameObjectFactory fact;
};


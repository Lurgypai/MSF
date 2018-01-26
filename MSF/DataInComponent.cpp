#include "stdafx.h"
#include "DataInComponent.h"
#include "BoxGraphicsComp.h"
#include "TestPhysicsComponent.h"
#include "TestInputComponent.h"
#include <sstream>

DataInComponent::DataInComponent(sf::RenderWindow* window, msf::Scene* scene) : window{ window }, fact{scene} {

	fact.setGraphics<BoxGraphicsComp>("images/box.png");
	fact.setPhysics<TestPhysicsComponent>(window);
	fact.setInput<TestInputComponent>(window);
}
//make the copy ctors
DataInComponent::DataInComponent(const DataInComponent & other) : window{ other.window }, fact{ other.owner->getScene() } {
	fact.setGraphics<BoxGraphicsComp>("images/box.png");
	fact.setPhysics<TestPhysicsComponent>(window);
	fact.setInput<TestInputComponent>(window);
}


DataInComponent::~DataInComponent()
{
}

std::unique_ptr<msf::DInputComponent> DataInComponent::clone() {
	return std::make_unique<DataInComponent>(*this);
}


void DataInComponent::update(std::vector<msf::Action>& actions) {
	for (auto& act : actions) {
		if (act.id == "right_d") {
 			fact.generate()->setPos(sf::Vector2f(sf::Mouse::getPosition(*window)));
		}
	}
}

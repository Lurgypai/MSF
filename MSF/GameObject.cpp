#include "stdafx.h"
#include "GameObject.h"
#include <memory>
namespace msf {

GameObject::GameObject(void) :
	pos(0.0F, 0.0F), scene(nullptr)
{}

GameObject::GameObject(const sf::Vector2f & pos_) :
	pos(pos_), scene(nullptr)
{}

GameObject::GameObject(const double & y_, const double & x_) :
	pos(x_, y_), scene(nullptr)
{}

GameObject::~GameObject()
{
}

void GameObject::update(void) {
	//update components, perhaps not though
}

double GameObject::x() const {
	return pos.x;
}

sf::Vector2f GameObject::getPos() const {
	return pos;
}

std::shared_ptr<Scene> GameObject::getScene(void) {
	return scene;
}

void GameObject::setScene(Scene & scene_) {
	if (scene != nullptr) {
		for (auto string : scene->getGroupIds()) {
			for (auto objectIterator = scene->getGroup(string)->begin(); objectIterator != scene->getGroup(string)->end(); objectIterator++) {
				if (*this == ** objectIterator) {
					scene->getGroup(string)->erase(objectIterator);
					/* add if you want to remove the group when it is empty
					if (scene->getGroup(string)->size() == 0) {

					}
					*/
				}
			}
		}
	}
	scene = std::make_shared<Scene>(scene_);

}

double GameObject::y() const
{
	return pos.y;
}

bool GameObject::operator==(const GameObject & obj2_) const {
	return (pos == obj2_.pos);
}

bool GameObject::operator!=(const GameObject & obj2_) const {
	return (pos != obj2_.pos);
}

}
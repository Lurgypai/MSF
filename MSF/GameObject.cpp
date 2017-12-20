#include "stdafx.h"
#include "GameObject.h"
#include <memory>
#include <iostream>
namespace msf {

GameObject::GameObject(unsigned char componentTag_,
	std::unique_ptr<PhysicsComponent> physics_,
	std::unique_ptr<GraphicsComponent> graphics_,
	std::unique_ptr<InputComponent> input_,
	std::unique_ptr<AudioComponent> audio_) :
	pos(0.0F, 0.0F), scene(),

	physics{std::move(physics_)},
	graphics{ std::move(graphics_) },
	input{ std::move(input_) },
	audio{ std::move(audio_) }
{}

GameObject::GameObject(const sf::Vector2f & pos_,
	unsigned char componentTag_,
	std::unique_ptr<PhysicsComponent> physics_,
	std::unique_ptr<GraphicsComponent> graphics_,
	std::unique_ptr<InputComponent> input_,
	std::unique_ptr<AudioComponent> audio_) :
	pos(pos_), scene(),

	physics{ std::move(physics_) },
	graphics{ std::move(graphics_) },
	input{ std::move(input_) },
	audio{ std::move(audio_) }
{}

GameObject::GameObject(const double & y_, const double & x_,
	unsigned char componentTag_,
	std::unique_ptr<PhysicsComponent> physics_,
	std::unique_ptr<GraphicsComponent> graphics_,
	std::unique_ptr<InputComponent> input_,
	std::unique_ptr<AudioComponent> audio_) :
	pos(x_, y_), scene(),

	physics{ std::move(physics_) },
	graphics{ std::move(graphics_) },
	input{ std::move(input_) },
	audio{ std::move(audio_) }
{}

GameObject::GameObject(const GameObject & gobj) {
	pos = gobj.pos;
	*scene = *(gobj.scene);
	componentTag = gobj.componentTag;
	*physics = *(gobj.physics);
	*graphics = *(gobj.graphics);
	*input = *(gobj.input);
	*audio = *(gobj.audio);
}

GameObject::~GameObject()
{
}

void GameObject::update(void) {

	if (componentTag & Physics) {
		std::cout << "HasPhysics" << std::endl;
		if (physics != nullptr) {
			physics->update(*this);
		}
	}
	if (componentTag & Graphics) {
		std::cout << "gfx" << std::endl;
		if (graphics != nullptr) {
			graphics->update(*this);
		}
	}
	if (componentTag & Input) {
		std::cout << "in" << std::endl;
		if (input != nullptr) {
			input->update(*this);
		}
	}
	if (componentTag & Audio) {
		std::cout << "sfx" << std::endl;
		if (audio != nullptr) {
			audio->update(*this);
		}
	}
	std::cout << (componentTag & Physics) << std::endl;
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
	scene = std::shared_ptr<Scene>(&scene_);

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
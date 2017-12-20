#include "stdafx.h"
#include "GameObject.h"
#include <memory>
#include <iostream>
namespace msf {

GameObject::GameObject(Scene& scene_, unsigned char componentTag_,
	std::unique_ptr<PhysicsComponent> physics_,
	std::unique_ptr<GraphicsComponent> graphics_,
	std::unique_ptr<InputComponent> input_,
	std::unique_ptr<AudioComponent> audio_) :
	scene(scene_), pos(0.0F, 0.0F), componentTag{componentTag_},

	physics{std::move(physics_)},
	graphics{ std::move(graphics_) },
	input{ std::move(input_) },
	audio{ std::move(audio_) }
{
	scene.addObject(*this);
}

GameObject::GameObject(Scene& scene_, const sf::Vector2f & pos_,
	unsigned char componentTag_,
	std::unique_ptr<PhysicsComponent> physics_,
	std::unique_ptr<GraphicsComponent> graphics_,
	std::unique_ptr<InputComponent> input_,
	std::unique_ptr<AudioComponent> audio_) :
	scene(scene_), pos(pos_), componentTag{ componentTag_ },

	physics{ std::move(physics_) },
	graphics{ std::move(graphics_) },
	input{ std::move(input_) },
	audio{ std::move(audio_) }
{
	scene.addObject(*this);
}

GameObject::GameObject(Scene& scene_, const double & x_, const double & y_,
	unsigned char componentTag_,
	std::unique_ptr<PhysicsComponent> physics_,
	std::unique_ptr<GraphicsComponent> graphics_,
	std::unique_ptr<InputComponent> input_,
	std::unique_ptr<AudioComponent> audio_) :
	scene(scene_), pos(x_, y_), componentTag{ componentTag_ },

	physics{ std::move(physics_) },
	graphics{ std::move(graphics_) },
	input{ std::move(input_) },
	audio{ std::move(audio_) }
{
	scene.addObject(*this);
}

GameObject::GameObject(const GameObject & gobj) : 
	pos{ gobj.pos }, scene(gobj.scene), componentTag{gobj.componentTag} {
	scene.addObject(*this);
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
		if (physics != nullptr) {
			physics->update(*this);
		}
	}
	if (componentTag & Graphics) {
		if (graphics != nullptr) {
			graphics->update(*this);
		}
	}
	if (componentTag & Input) {
		if (input != nullptr) {
			input->update(*this);
		}
	}
	if (componentTag & Audio) {
		if (audio != nullptr) {
			audio->update(*this);
		}
	}
}

double GameObject::x() const {
	return pos.x;
}

sf::Vector2f GameObject::getPos() const {
	return pos;
}

Scene& GameObject::getScene(void) {
	return scene;
}

void GameObject::setScene(Scene & scene_) {
		for (auto& string : scene.getGroupIds()) {
			for (auto& objectIterator = scene.getGroup(string).begin(); objectIterator != scene.getGroup(string).end(); objectIterator++) {
				if (*this == **objectIterator) {
					scene.getGroup(string).erase(objectIterator);
					/* add if you want to remove the group when it is empty
					if (scene->getGroup(string)->size() == 0) {

					}
					*/
				}
			}
		}
	scene = scene_;
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
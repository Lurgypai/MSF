
#include "stdafx.h"
#include "GameObject.h"
#include <memory>
#include <iostream>
namespace msf {
	GameObject::GameObject(const sf::Vector2f pos_) : pos{ pos_ }, componentTag{}, tag{ tagCounter++ }, queue{}, scene{nullptr} {}

	GameObject::GameObject(float x, float y) : pos{ x, y }, componentTag{}, tag{ tagCounter++ }, queue{}, scene{ nullptr } {}

	GameObject::GameObject(const GameObject & gobj) : pos{ gobj.pos }, componentTag{ gobj.componentTag }, tag{ tagCounter++ }, queue{}, scene{ nullptr } {
		if (componentTag & Physics) {
			physics = gobj.physics->clone();
		}
		if (componentTag & Graphics) {
			graphics = gobj.graphics->clone();
		}
		if (componentTag & Input) {
			input = gobj.input->clone();
		}
		if (componentTag & Audio) {
			audio = gobj.audio->clone();
		}
	}

	GameObject::~GameObject() {}

	float GameObject::x() const {
		return pos.x;
	}
	
	float GameObject::y() const {
		return pos.y;
	}

	uint64_t GameObject::getTag() const {
		return tag;
	}

	const sf::Vector2f& GameObject::getPos() const {
		return pos;
	}

	Scene * GameObject::getScene() {
		return scene;
	}

	void GameObject::move(float x, float y) {
		pos.x += x;
		pos.y += y;
	}

	void GameObject::move(const sf::Vector2f& moveBy) {
		pos.x += moveBy.x;
		pos.y += moveBy.y;
	}

	void GameObject::setPos(float x, float y) {
		pos.x = x;
		pos.y = y;
	}

	void GameObject::setPos(const sf::Vector2f & pos_) {
		pos = pos_;
	}

	void GameObject::updateInput() {
		if (componentTag & Input) {
			input->update();
			for (auto& act : input->getBuffer()) {
				queue.storeAction(act);
			}
		}

		if (componentTag & Physics) {
			physics->update(input->getBuffer());
			for (auto& act : physics->getBuffer()) {
				queue.storeAction(act);
			}
			if(!physics->getBuffer().empty())
			physics->getBuffer().clear();
		}

		if (componentTag & Input) {
			if (!input->getBuffer().empty())
				input->getBuffer().clear();
		}
	}

	void GameObject::updateSensuals(sf::RenderWindow& window) {
		if (componentTag & Audio) {
			audio->update(queue.getBuffer());
		}
		if (componentTag & Graphics) {
			graphics->update(queue.getBuffer(), window);
		}
		if (!queue.isEmpty()) {
			queue.clearActions();
		}
	}

	//incomplete
	bool GameObject::operator==(const GameObject & obj2_) const {
		return (tag == tag);
	}
	//incomplete
	bool GameObject::operator!=(const GameObject & obj2_) const {
		return (tag != tag);
	}

	void GameObject::operator=(const GameObject & gobj) {
		pos = gobj.pos;
		componentTag = gobj.componentTag;

		if (componentTag & Physics) {
			physics = gobj.physics->clone();
		}
		if (componentTag & Graphics) {
			graphics = gobj.graphics->clone();
		}
		if (componentTag & Input) {
			input = gobj.input->clone();
		}
		if (componentTag & Audio) {
			audio = gobj.audio->clone();
		}
	}

	uint64_t GameObject::tagCounter = 0;
}

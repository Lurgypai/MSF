
#include "stdafx.h"
#include "GameObject.h"
#include <memory>
#include <iostream>
namespace msf {
	GameObject::GameObject(const sf::Vector2f pos_) : pos{ pos_ }, componentTag{}, tag{ tagCounter++ }, queue{} {}

	GameObject::GameObject(float x, float y) : pos{ x, y }, componentTag{}, tag{ tagCounter++ }, queue{} {}

	GameObject::GameObject(const GameObject & gobj) : pos{ gobj.pos }, componentTag{ gobj.componentTag }, tag{ tagCounter++ }, queue{} {
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

	void GameObject::updateInput(std::vector<Action>& action) {
		std::vector<Action> actions{};
		if (componentTag & Input) {
			input->update(action);
			Action act{ "", true };
			while (input->pollAction(act)) {
				queue.storeAction(act);
				actions.push_back(act);
			}
		}

		if (componentTag & Physics) {
			if (!actions.empty()) {
				for (auto& action : actions) {
					physics->update(action);
				}
			}
			else {
				physics->update(Action{"", true});
			}
			Action act{ "", true };
			while (physics->pollAction(act))
				queue.storeAction(act);
		}
	}

	void GameObject::updateSensuals(sf::RenderWindow& window) {
		Action act{ "", true };
		if (!queue.isEmpty()) {
			while (queue.pollAction(act)) {
				if (componentTag & Audio) {
					audio->update(act);
				}
				if (componentTag & Graphics) {
					graphics->update(act, window);
				}
			}
			return;
		}
		else {
			if (componentTag & Audio) {
				audio->update(act);
			}
			if (componentTag & Graphics) {
				graphics->update(act, window);
			}
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

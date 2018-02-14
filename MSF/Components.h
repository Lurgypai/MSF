#pragma once
#include "GameObject.h"
#include "DataObject.h"
#include "ActionQueue.h"
#include "SFML\Graphics.hpp"

namespace msf {
	class GameObject;
	class DataObject;

	class Component {
	public:
		Component() : owner{ nullptr } {}
		GameObject* owner;
	};
	class InputsComponents : public Component {
	public:
		std::vector<Action*> buffer;
		std::vector<Action*>& getBuffer() { return buffer; }
	};
	//physics
	class PhysicsComponent : public InputsComponents {
	public:
		virtual void update(std::vector<Action*>& act) = 0;
		virtual std::unique_ptr<PhysicsComponent> clone() = 0;
	};
	//gfx
	class GraphicsComponent : public Component {
	public:
		virtual void update(std::vector<Action*>& act, sf::RenderWindow& window) = 0;
		virtual std::unique_ptr<GraphicsComponent> clone() = 0;
	};
	//input
	class InputComponent : public InputsComponents {
	public:
		virtual void update() = 0;
		virtual std::unique_ptr<InputComponent> clone() = 0;
	};

	//audio
	class AudioComponent : public Component {
	public:
		virtual void update(std::vector<Action*>& act) = 0;
		virtual std::unique_ptr<AudioComponent> clone() = 0;
	};

	class DInputComponent {
	public:
		DInputComponent() : owner{ nullptr } {}
		virtual void update() = 0;
		virtual std::unique_ptr<DInputComponent> clone() = 0;
		DataObject* owner;
	};
}
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
	class LogicComponent : public Component {
	public:
		virtual void update() = 0;
		virtual std::unique_ptr<LogicComponent> clone() = 0;
		std::vector<Action*>& getBuffer() { return buffer; }
	protected:
		std::vector<Action*> buffer;
	};
	//gfx
	class GraphicsComponent : public Component {
	public:
		virtual void update(std::vector<Action*>& act, sf::RenderWindow& window) = 0;
		virtual std::unique_ptr<GraphicsComponent> clone() = 0;
	};

	//audio
	class AudioComponent : public Component {
	public:
		virtual void update(std::vector<Action*>& act) = 0;
		virtual std::unique_ptr<AudioComponent> clone() = 0;
	};

	class DLogicComponent {
	public:
		DLogicComponent() : owner{ nullptr } {}
		virtual void update() = 0;
		virtual std::unique_ptr<DLogicComponent> clone() = 0;
	protected:
		DataObject* owner;
	};
}
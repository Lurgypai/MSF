#pragma once
#include "GameObject.h"
#include "DataObject.h"
#include "ActionQueue.h"
#include "Collider.h"
#include "SFML\Graphics.hpp"

namespace msf {
	class GameObject;
	class DataObject;

	class Component {
	public:
		Component() : owner{ nullptr } {}
		virtual ~Component() {};
		GameObject* owner;
	};
	class LogicComponent : public Component {
	public:
		LogicComponent() : collide{ nullptr }, colliderFlag{false} {}
		virtual ~LogicComponent() {};
		virtual void update() = 0;
		virtual std::unique_ptr<LogicComponent> clone() = 0;

		Collider* getCollider() { return collide.get(); }
		bool hasCollider() {
			return colliderFlag;
		}

		std::vector<Action*>& getBuffer() { return buffer; }

		template<typename T, typename... Args>
		void setCollider(Args... args) {
			collide = std::make_unique<T>(args...);
			colliderFlag = true;
		}
		//getter
	protected:
		std::vector<Action*> buffer;
		bool colliderFlag;
		std::unique_ptr<Collider> collide;

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
		virtual ~DLogicComponent() {}
		virtual void update() = 0;
		virtual std::unique_ptr<DLogicComponent> clone() = 0;
		DataObject* owner;
	};
}
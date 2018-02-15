#pragma once

#include <memory>
#include <cstdint>
#include <iostream>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "Scene.h"
#include "Components.h"
#include "ActionQueue.h"

//A game object is anything that exists with position
//created and managed by Scenes

namespace msf {

	class Scene;
	class LogicComponent;
	class GraphicsComponent;
	class AudioComponent;

	//may not want those to be references (x, y)
	class GameObject {
	public:
		enum ComponentFlags : char {
			Logic = 1 << 0,
			Graphics = 1 << 1,
			Audio = 1 << 2
		};

		GameObject(const sf::Vector2f pos_);
		GameObject(float x, float y);
		GameObject(const GameObject& gobj);

		~GameObject();

		//getters
		float x() const;
		float y() const;
		uint64_t getTag() const;
		const sf::Vector2f& getPos() const;
		Scene* getScene();

		void move(float x, float y);
		void move(const sf::Vector2f& moveBy);
		void setPos(float x, float y);
		void setPos(const sf::Vector2f& pos_);
		void updateInput();
		void updateSensuals(sf::RenderWindow& window);

		template<typename T, typename... Args>
		void setLogic(Args... args) {
			logic = std::make_unique<T>(args...);
			logic->owner = this;
			componentTag |= Logic;
		}
		template<typename T, typename... Args>
		void setGraphics(Args... args) {
			graphics = std::make_unique<T>(args...);
			graphics->owner = this;
			componentTag |= Graphics;
		}
		template<typename T, typename... Args>
		void setAudio(Args... args) {
			audio = std::make_unique<T>(args...);
			audio->owner = this;
			componentTag |= Audio;
		}

		bool operator==(const GameObject& obj2_) const;
		bool operator!=(const GameObject& obj2_) const;
		void operator=(const GameObject& gobj);
	private:
		friend class Scene;
		friend class GameObjectFactory;

		uint64_t tag;
		unsigned char componentTag;
		sf::Vector2f pos;
		ActionQueue queue;
		Scene* scene;
		std::unique_ptr<GraphicsComponent> graphics;
		std::unique_ptr<LogicComponent> logic;
		std::unique_ptr<AudioComponent> audio;

		static uint64_t tagCounter;
	};
}
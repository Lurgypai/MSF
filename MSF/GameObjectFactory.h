#pragma once
#include "GameObject.h"
//set each component
namespace msf {
	class PhysicsComponent;
	class GraphicsComponent;
	class InputComponent;
	class AudioComponent;
	class Scene;
	class GameObject;

class GameObjectFactory {
public:
	GameObjectFactory(Scene* scene_);
	GameObjectFactory(Scene* scene_, const sf::Vector2f pos_);

	std::vector<std::shared_ptr<GameObject>> generate(int num);
	std::vector<std::shared_ptr<GameObject>> generate(const std::string& groupId, int num);
	std::shared_ptr<GameObject> generate();
	std::shared_ptr<GameObject> generate(const std::string& groupId);
	const Scene& getScene() const;
	template<typename T, typename... Args>
	GameObjectFactory* setPhysics(Args... args) {
		physics = std::make_unique<T>(args...);
		componentTag |= GameObject::Physics;
		return this;
	}

	template<typename T, typename... Args>
	GameObjectFactory* setGraphics(Args... args) {
		graphics = std::make_unique<T>(args...);
		componentTag |= GameObject::Graphics;
		return this;
	}

	template<typename T, typename... Args>
	GameObjectFactory* setInput(Args... args) {
		input = std::make_unique<T>(args...);
		componentTag |= GameObject::Input;
		return this;
	}

	template<typename T, typename... Args>
	GameObjectFactory* setAudio(Args... args) {
		audio = std::make_unique<T>(args...);
		componentTag |= GameObject::Audio;
		return this;
	}

private:
	inline void fillComponents(const std::shared_ptr<GameObject>& gobjectPtr);

	Scene* scene;
	sf::Vector2f pos;
	std::unique_ptr<PhysicsComponent> physics;
	std::unique_ptr<GraphicsComponent> graphics;
	std::unique_ptr<InputComponent> input;
	std::unique_ptr<AudioComponent> audio;
	unsigned char componentTag;
};
}
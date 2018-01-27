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
	~GameObjectFactory();

	Scene* getScene();
	std::shared_ptr<GameObject> generate(const std::string& groupId = Scene::default_groupid);
	void generate(std::vector<std::shared_ptr<GameObject>>& objs, int num, const std::string& groupid = Scene::default_groupid);

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

	Scene* scene;
	sf::Vector2f pos;
	std::unique_ptr<PhysicsComponent> physics;
	std::unique_ptr<GraphicsComponent> graphics;
	std::unique_ptr<InputComponent> input;
	std::unique_ptr<AudioComponent> audio;
	unsigned char componentTag;
};
}
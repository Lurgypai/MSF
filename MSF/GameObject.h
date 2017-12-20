#pragma once
#include <SFML/System.hpp>
#include <memory>
#include "Scene.h"
#include "PhysicsComponent.h"
#include "GraphicsComponent.h"
#include "InputComponent.h"
#include "AudioComponent.h"
//A game object is anything that exists with position

namespace msf {

class Scene;
class PhysicsComponent;
class GraphicsComponent;
class InputComponent;
class AudioComponent;


class GameObject {
public:
	GameObject(unsigned char componentTag_,
		std::unique_ptr<PhysicsComponent> physics_ = nullptr,
		std::unique_ptr<GraphicsComponent> graphics_ = nullptr,
		std::unique_ptr<InputComponent> input_ = nullptr,
		std::unique_ptr<AudioComponent> audio_ = nullptr);

	GameObject(const sf::Vector2f& pos_,
		unsigned char componentTag_,
		std::unique_ptr<PhysicsComponent> physics_ = nullptr,
		std::unique_ptr<GraphicsComponent> graphics_ = nullptr,
		std::unique_ptr<InputComponent> input_ = nullptr,
		std::unique_ptr<AudioComponent> audio_ = nullptr);

	GameObject(const double& y_, const double& x_,
		unsigned char componentTag_,
		std::unique_ptr<PhysicsComponent> physics_ = nullptr,
		std::unique_ptr<GraphicsComponent> graphics_ = nullptr,
		std::unique_ptr<InputComponent> input_ = nullptr,
		std::unique_ptr<AudioComponent> audio_ = nullptr);
	GameObject(const GameObject& gobj);
	~GameObject();
	double x() const;
	double y() const;
	sf::Vector2f getPos() const;

	std::shared_ptr<Scene> getScene(void);
	void setScene(Scene& scene_);
	
	bool operator==(const GameObject& obj2_) const;
	bool operator!=(const GameObject& obj2_) const;
	//add obtaining scene
	//add vector of components
	enum ComponentFlags {
		Physics = 1 << 0,
		Graphics = 1 << 1,
		Input = 1 << 2,
		Audio = 1 << 3
	};
private:
	friend class Scene;
	void update(void);

	sf::Vector2f pos;
	//reference to scene
	std::shared_ptr<Scene> scene;
	unsigned char componentTag;

	//these are owned, no need to reference
	std::unique_ptr<PhysicsComponent> physics;
	std::unique_ptr<GraphicsComponent> graphics;
	std::unique_ptr<InputComponent> input;
	std::unique_ptr<AudioComponent> audio;
	//add reference to ownning scene
};

}
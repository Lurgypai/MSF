#pragma once
#include <SFML/System.hpp>
#include <memory>
#include "Scene.h"
//A game object is anything that exists with position

namespace msf {

	class Scene;

class GameObject {
public:
	GameObject(void);
	GameObject(const sf::Vector2f& pos_);
	GameObject(const double& y_, const double& x_);
	~GameObject();
	void update(void);
	double x() const;
	double y() const;
	sf::Vector2f getPos() const;

	std::shared_ptr<Scene> getScene(void);
	void setScene(Scene& scene_);
	
	bool operator==(const GameObject& obj2_) const;
	bool operator!=(const GameObject& obj2_) const;
	//add obtaining scene
	//add vector of components
private:
	sf::Vector2f pos;
	std::shared_ptr<Scene> scene;
	//add reference to ownning scene
};

}
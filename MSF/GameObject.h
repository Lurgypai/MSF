#pragma once
#include <SFML/System.hpp>
//A game object is anything that exists with position

namespace msf {

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
	//add obtaining scene
	//add vector of components
private:
	sf::Vector2f pos;
	//add reference to ownning scene
};

}
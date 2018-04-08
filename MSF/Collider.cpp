#include "stdafx.h"
#include "Collider.h"

namespace msf {
	Collider::Collider() : shape{nullptr} {}
	Collider::Collider(const Collider & other) : shape{ other.shape->clone() } {}
	Collider::~Collider() {}

	void Collider::setOrigin(float x, float y) {
		shape->setOrigin(x, y);
	}

	void Collider::setOrigin(const sf::Vector2f & pos) {
		shape->setOrigin(pos);
	}

	Shape * Collider::getShape() {
	return shape.get();
}
}
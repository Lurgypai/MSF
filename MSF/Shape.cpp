#include "stdafx.h"
#include "Shape.h"

namespace msf {
	Shape::Shape(const sf::Vector2f & origin_, int type) : origin{ origin_ }, type{ type } {}

	Shape::Shape(const Shape & other) : origin{ other.origin } {}

	void Shape::setOrigin(float x, float y) {
		origin.x = x;
		origin.y = y;
	}

	void Shape::setOrigin(const sf::Vector2f & pos) {
		origin = pos;
	}

	const sf::Vector2f& Shape::getOrigin() const {
		return origin;
	}

	int Shape::getType() {
		return type;
	}

}
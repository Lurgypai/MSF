#pragma once
#include "SFML/Graphics.hpp"
#include <memory>

namespace msf {
	class Shape {
	public:
		Shape(const sf::Vector2f& origin_, int type);
		Shape(const Shape& other);
		virtual ~Shape() {};


		virtual sf::FloatRect getBoundingBox() const = 0;
		virtual std::unique_ptr<Shape> clone() = 0;

		void setOrigin(float x, float y);
		const sf::Vector2f& getOrigin() const;
		int getType();
	protected:
		int type;
		sf::Vector2f origin;
	};
}
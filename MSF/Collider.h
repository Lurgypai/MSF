#pragma once
#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"
#include "Shape.h"
#include <memory>
namespace msf {
	class Collider {
	public:
		Collider();
		Collider(const Collider& other);
		virtual ~Collider();

		template<typename T, typename... Args>
		void setShape(Args... args) {
			shape = std::make_unique<T>(args...);
		}

		Shape* getShape();

		virtual bool intersects(Collider& other) = 0;
		virtual bool contains(const sf::Vector2f& point) = 0;
	protected:
		std::unique_ptr<Shape> shape;
	};
}
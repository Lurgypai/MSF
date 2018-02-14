#pragma once
#include "SFML\Graphics.hpp"
#include <memory>
namespace msf {
	class Camera {
	public:
		Camera(const sf::View& view);
		Camera(const Camera& other);
		virtual ~Camera();
		virtual void update();
		const sf::View& getView();
		void setView(const sf::View& view_);
	private:
		sf::View view;
	};
}
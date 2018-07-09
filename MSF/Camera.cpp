#include "stdafx.h"
#include "Camera.h"

namespace msf {
	Camera::Camera(const sf::View & view) : view{view} {
	}
	Camera::Camera(const Camera & other) : view{other.view} {
	}
	Camera::~Camera() {}
	void Camera::update() {}
	const sf::View & Camera::getView() const {
		return view;
	}
	void Camera::setView(const sf::View & view_) {
		view = view_;
	}
}
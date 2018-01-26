#include "stdafx.h"
#include "Camera.h"

namespace msf {

	Camera::Camera() : View{}, universalShaders {} {}

	Camera::Camera(const sf::FloatRect & rectangle) : View{ rectangle }, universalShaders{} {}

	Camera::Camera(const sf::Vector2f & center, const sf::Vector2f & size) : View{ center, size }, universalShaders{} {}

Camera::~Camera()
{
}

void Camera::removeShader(const std::string & id) {
	if (universalShaders.find(id) != universalShaders.end()) {
		universalShaders.erase(universalShaders.find(id));
	}
}

std::vector<std::shared_ptr<sf::Shader>> Camera::getUniversalShaders() {
	std::vector<std::shared_ptr<sf::Shader>> shaders;
	for (const auto& pair : universalShaders) {
		shaders.push_back(pair.second);
	}
	return shaders;
}

std::shared_ptr<sf::Shader> Camera::getShader(const std::string & id) {
	return universalShaders[id];
}

}
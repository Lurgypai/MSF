#pragma once
#include "SFML\Graphics.hpp"
#include <unordered_map>
#include <memory>

namespace msf {

class Camera : public sf::View {
public:
	Camera();
	Camera(const sf::FloatRect& rectangle);
	Camera(const sf::Vector2f& center, const sf::Vector2f& size);
	~Camera();

	template<typename... Args>
	void addShader(const std::string& id, Args... args) {
		universalShaders[id] = std::make_shared<sf::Shader>{args...};
	}
	void removeShader(const std::string& id);
	std::vector<std::shared_ptr<sf::Shader>> getUniversalShaders();
	std::shared_ptr<sf::Shader> getShader(const std::string& id);
private:
	std::unordered_map<std::string, std::shared_ptr<sf::Shader>> universalShaders;
};

}

#pragma once
#include <unordered_map>
#include <memory>
#include <string>
#include "Scene.h"
#include "Settings.h"
#include <SFML/Graphics.hpp>
/*
--THE GAME CLASS HOLDS:
-the scenes
-the settings
-the windows?
-the services (if used)
-the systems (if used)
-may need message system so that objects and whatnot can communicate properly with the window and other game owned things
--AND MANAGES:
-the settings
-the windows (with help?)
-the scenes
-the services (if used)
-the systems (if used)
-updating individual GameObject componenets
*/

namespace msf {

class Game {
public:
	Game(const std::string& name_);
	Game(const std::string& name_, std::initializer_list<std::pair<const std::string&, Scene&>> scenes);
	Game(const std::string& name_, std::initializer_list<std::pair<const std::string&, Scene&>> scenes, const Settings& settings_);
	Game(const std::string& name_, const Settings& settings_);
	~Game();

	void start(const std::string& startScene);

	std::shared_ptr<Scene> getScene(const std::string& id);
	std::unique_ptr<Settings> getSettings();
	void addScene(Scene& scene_, const std::string& id);
	void setScene(const std::string& id);
	void openWindow();
private:
	const std::string name;
	std::unordered_map<std::string, std::shared_ptr<Scene>> scenes;
	std::shared_ptr<sf::RenderWindow> window;
	std::shared_ptr<Scene> currentScene;
	Settings settings;
	//settings
	//services
	//systems

};

}
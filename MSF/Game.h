#pragma once
#include <unordered_map>
#include <memory>
#include <string>
#include <thread>
#include <atomic>
#include "Scene.h"
#include "Settings.h"
#include "Updater.h"
#include "Camera.h"
#include "Controller.h"
#include <chrono>
#include <SFML/Graphics.hpp>
#define DEFAULT_RENDER_SPEED 60.0
#define DEFAULT_PHYSICS_SPEED 120.0
/*
--THE GAME CLASS HOLDS:
-the scenes
-the settings
-the windows
-the updater
--AND MANAGES:
-the settings
-the windows
-the scenes
-the updater
*/

namespace msf {

class Game {
public:
	Game(const std::string& name_);
	Game(const std::string& name_, std::initializer_list<std::pair<const std::string, Scene&>> scenes);
	Game(const std::string& name_, std::initializer_list<std::pair<const std::string, Scene&>> scenes, const Settings& settings_);
	Game(const std::string& name_, float physicsSpeed_, float updateSpeed);
	Game(const std::string& name_, std::initializer_list<std::pair<const std::string, Scene&>> scenes, float physicsSpeed_, float updateSpeed);
	Game(const std::string& name_, std::initializer_list<std::pair<const std::string, Scene&>> scenes, const Settings& settings_, float physicsSpeed_, float updateSpeed);

	Game(const std::string& name_, std::initializer_list<std::pair<const std::string, Scene&&>> scenes) = delete;
	Game(const std::string& name_, std::initializer_list<std::pair<const std::string, Scene&&>> scenes, const Settings& settings_) = delete;
	Game(const std::string& name_, std::initializer_list<std::pair<const std::string, Scene&&>> scenes, int physicsSpeed_, int updateSpeed) = delete;
	Game(const std::string& name_, std::initializer_list<std::pair<const std::string, Scene&&>> scenes, const Settings& settings_, int physicsSpeed_, int updateSpeed) = delete;
	Game(const std::string& name_, const Settings& settings_);
	~Game();

	void start(const std::string& startScene);

	Scene* getScene(const std::string& id);
	Settings& getSettings();
	Scene* getCurrentScene();
	sf::RenderWindow* getWindow();
	Updater* getUpdater();

	void setSettings(const Settings& set_);
	void setSettings(const std::initializer_list<std::pair<std::string, int>>);
	void addScene(Scene& scene_, const std::string& id);
	void setScene(const std::string& id);
	
	template<typename... Args>
	std::shared_ptr<Camera> addCamera(const std::string& id, Args... args) {
		std::shared_ptr<Camera> cam = std::make_shared(args...);
		cameras[id] = cam;
		return cam;
	}

	template<typename T, typename... Args>
	std::shared_ptr<Controller> addController(Args... args) {
		std::shared_ptr<Controller> controller = std::make_shared<T>(args...);
		controllers.push_back(controller);
		return controller;
	}

	std::shared_ptr<Camera> getCamera(const std::string& id);
	void setCamera(const std::string& id);

	void openWindow();
	void startLoop();
	void stopLoop();
private:
	const std::string name;
	//references or raw pointers
	std::unordered_map<std::string, Scene*> scenes;
	sf::RenderWindow window;
	//reference or raw pointer
	Scene* currentScene;
	Settings settings;
	Updater updater;
	float physicsSpeed;
	float renderSpeed;

	std::unordered_map<std::string, std::shared_ptr<Camera>> cameras;
	std::shared_ptr<Camera> currentCamera;

	std::vector<std::shared_ptr<Controller>> controllers;

	//settings
	//services
	//systems

	std::atomic_bool isLooping;
	std::thread gameLoop;
	//enable render altering
};

}
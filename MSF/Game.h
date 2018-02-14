#pragma once
#include <unordered_map>
#include <memory>
#include <string>
#include <thread>
#include <atomic>
#include "Scene.h"
#include "Settings.h"
#include "Updater.h"
#include "Controller.h"
#include "Camera.h"
#include <chrono>
#include <SFML/Graphics.hpp>
#define DEFAULT_RENDER_SPEED 60.0
#define DEFAULT_PHYSICS_SPEED 120.0
#define DEFAULT_WINDOW_WIDTH 1080
#define DEFAULT_WINDOW_HEIGHT 720

namespace msf {

class Game {
public:
	Game(const std::string& name_, float physicsSpeed_ = DEFAULT_PHYSICS_SPEED, float renderSpeed_ = DEFAULT_RENDER_SPEED);
	Game(const std::string& name_, const std::unordered_map<std::string, Scene*>& scenes, float physicsSpeed_ = DEFAULT_PHYSICS_SPEED, float updateSpeed = DEFAULT_RENDER_SPEED);
	Game(const std::string& name_, const std::unordered_map<std::string, Scene*>& scenes, const Settings& settings_, float physicsSpeed_ = DEFAULT_PHYSICS_SPEED, float updateSpeed = DEFAULT_RENDER_SPEED);
	~Game();

	void prepareWindow(int width = DEFAULT_WINDOW_WIDTH, int height = DEFAULT_WINDOW_HEIGHT, sf::Uint32 style = sf::Style::Default);
	void openWindow();
	void threadLoop();
	void stopLoop();
	void start(const std::string& startScene, const std::string& startGroup);
	void setCamera(int id);
	void setSettings(const Settings& set_);
	void setSettings(const std::initializer_list<std::pair<std::string, int>>);
	void addCamera(int id, const Camera& cam);
	void setScene(const std::string& id);
	void addScene(Scene& scene_, const std::string& id);

	bool getLooping() const;
	const std::string& getName() const;
	Scene* getScene(const std::string& id);
	Settings& getSettings();
	Scene* getCurrentScene();
	sf::RenderWindow* getWindow();
	Updater* getUpdater();
	std::shared_ptr<Camera> getCamera(int id);

private:
	float physicsSpeed;
	float renderSpeed;
	const std::string name;
	unsigned int windowWidth;
	unsigned int windowHeight;
	sf::Uint32 windowStyle;
	std::atomic_bool isLooping;
	Settings settings;
	Updater updater;
	sf::RenderWindow window;
	Scene* currentScene;
	std::shared_ptr<Camera> currentCamera;
	std::thread gameLoop;
	std::unordered_map<std::string, Scene*> scenes;
	std::unordered_map<int, std::shared_ptr<Camera>> cameras;

	void startLoop();
};

}
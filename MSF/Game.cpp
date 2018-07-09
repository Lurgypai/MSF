#include "stdafx.h"
#include "Game.h"
#include <iostream>

namespace msf {

	Game::Game(const std::string & name_, float physicsSpeed_, float renderSpeed_) : name{ name_ }, scenes{}, window{}, updater{}, physicsSpeed{ physicsSpeed_ }, renderSpeed{ renderSpeed_ }, cameras{}, windowWidth{ DEFAULT_WINDOW_WIDTH }, windowHeight{ DEFAULT_WINDOW_HEIGHT }, windowStyle{sf::Style::Default} {}

	Game::Game(const std::string & name_, const std::unordered_map<std::string, Scene*>& scenes_, float physicsSpeed_, float renderSpeed_) : name{ name_ }, window{}, physicsSpeed{ physicsSpeed_ }, renderSpeed{ renderSpeed_ }, updater{}, scenes{ scenes_ }, cameras{}, windowWidth{ DEFAULT_WINDOW_WIDTH }, windowHeight{ DEFAULT_WINDOW_HEIGHT }, windowStyle{ sf::Style::Default } {}

	Game::Game(const std::string & name_, const std::unordered_map<std::string, Scene*>& scenes_, const Settings & settings_, float physicsSpeed_, float renderSpeed_) : name{ name_ }, settings{ settings_ }, window{}, physicsSpeed{ physicsSpeed_ }, renderSpeed{ renderSpeed_ }, updater{}, cameras{}, windowWidth{ DEFAULT_WINDOW_WIDTH }, windowHeight{ DEFAULT_WINDOW_HEIGHT }, windowStyle{ sf::Style::Default } {}

Game::~Game() {
	stopLoop();
}

void Game::prepareWindow(int width, int height, sf::Uint32 style) {
	windowWidth = width;
	windowHeight = height;
	windowStyle = style;
}

void Game::openWindow() {
	if (window.isOpen())
		window.close();

	window.create({ windowWidth, windowHeight }, name, windowStyle);
	window.setActive(false);

	if (cameras.size() == 0) {
		addCamera<Camera>(0, window.getView());
		setCamera(0);
	}
}

void Game::startLoop() {
	//isLooping set here so we can check it after immediately after starting the game
	isLooping = true;
	gameLoop = std::thread(&Game::threadLoop, this);
}

void Game::start(const std::string& startScene, const std::string& startGroup) {
	currentScene = scenes[startScene];
	updater.registerScene(currentScene);
	updater.addCurrentGroup(startGroup);
	startLoop();
}

void Game::start(const std::string & startScene, const std::initializer_list<std::string>& startGroup) {
	currentScene = scenes[startScene];
	updater.registerScene(currentScene);
	for (auto& group : startGroup) {
		updater.addCurrentGroup(group);
	}
	startLoop();
}

void Game::stopLoop() {
	isLooping = false;
	if(gameLoop.joinable())
	gameLoop.join();
}

void Game::setCamera(int id) {
	currentCamera = cameras[id];
}

void Game::setSettings(const Settings & set_) {
	settings = set_;
}

void Game::setSettings(const std::initializer_list<std::pair<std::string, int>> set_) {
	for (auto pair : set_) {
		settings.setField(pair.first, pair.second);
	}
}

void Game::setScene(const std::string & id) {
	currentScene = scenes[id];
	updater.registerScene(currentScene);

}

void Game::addScene(Scene & scene_, const std::string& id) {
	scenes.insert({ id, &scene_ });
}

void Game::unPause() {
	std::unique_lock<std::mutex> lck{ pauseMx };
	isPaused = false;
	pauseCv.notify_one();
}

void Game::waitFor() {
	if(gameLoop.joinable())
	gameLoop.join();
}

void Game::pause() {
	std::unique_lock<std::mutex> lck{ pauseMx };
	isPaused = true;
}

bool Game::getLooping() const {
	return isLooping.load();
}

const std::string & Game::getName() const {
	return name;
}

Scene* Game::getScene(const std::string& id) {
	return scenes[id];
}

Settings& Game::getSettings() {
	return settings;
}

Scene* Game::getCurrentScene() {
	return currentScene;
}

sf::RenderWindow* Game::getWindow() {
	return &window;
}

Updater * Game::getUpdater() {
	return &updater;
}
std::shared_ptr<Camera> Game::getCamera(int id) {
	return cameras[id];
}



void Game::threadLoop() {
	openWindow();
	sf::Clock clock;
	float inputsTime{};
	float sensualsTime{};
	while (isLooping) {

		//check if we're paused
		std::unique_lock<std::mutex> lck{ pauseMx };
		pauseCv.wait(lck, [this] {return !this->isPaused; });

		float delta = clock.restart().asSeconds();
		inputsTime += delta;
		sensualsTime += delta;
		if (inputsTime >= 1.0 / physicsSpeed) {
			updater.updateInputs();
		}
		if (sensualsTime >= 1.0 / renderSpeed) {
			currentCamera->update();
			window.setView(currentCamera->getView());

			window.setActive(true);
			window.clear(sf::Color::Black);
			updater.updateSensuals(window);
			window.display();
			window.setActive(false);
		}
		if (inputsTime >= 1.0 / physicsSpeed)
			inputsTime = 0;
		if (sensualsTime >= 1.0 / renderSpeed)
			sensualsTime = 0;

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
				isLooping = false;
			}
		}
	}
	return;
}
}
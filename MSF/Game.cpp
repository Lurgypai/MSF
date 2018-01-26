#include "stdafx.h"
#include "Game.h"
#include <iostream>

namespace msf {

	Game::Game(const std::string & name_) : name{ name_ }, scenes{}, window{}, physicsSpeed { DEFAULT_PHYSICS_SPEED }, renderSpeed{ DEFAULT_RENDER_SPEED }, updater{} {}

	Game::Game(const std::string& name_, std::initializer_list<std::pair<const std::string, Scene&>> scenes_) : name{ name_ }, window{}, physicsSpeed{ DEFAULT_PHYSICS_SPEED }, renderSpeed{ DEFAULT_RENDER_SPEED }, updater{} {
		for (auto& pair_ : scenes_) {
			scenes.insert({ pair_.first, &(pair_.second) });
		}
	}

Game::Game(const std::string & name_, std::initializer_list<std::pair<const std::string, Scene&>> scenes_, const Settings& settings_) : name{ name_ }, settings{settings_}, window{}, physicsSpeed{ DEFAULT_PHYSICS_SPEED }, renderSpeed{ DEFAULT_RENDER_SPEED }, updater{} {
	for (auto& pair_ : scenes_) {
		scenes.insert({ pair_.first, &(pair_.second) });
	}
}

Game::Game(const std::string & name_, float physicsSpeed_, float updateSpeed) : name{ name_ }, scenes{}, window{}, updater{} {
}

Game::Game(const std::string & name_, std::initializer_list<std::pair<const std::string, Scene&>> scenes_, float physicsSpeed_, float renderSpeed_) : name{ name_ }, window{}, physicsSpeed{ physicsSpeed_ }, renderSpeed{renderSpeed_}, updater{} {
	for (auto& pair_ : scenes_) {
		scenes.insert({ pair_.first, &(pair_.second) });
	}
}

Game::Game(const std::string & name_, std::initializer_list<std::pair<const std::string, Scene&>> scenes_, const Settings & settings_, float physicsSpeed_, float renderSpeed_) : name{ name_ }, settings{ settings_ }, window{}, physicsSpeed{ physicsSpeed_ }, renderSpeed{ renderSpeed_ }, updater{} {
	for (auto& pair_ : scenes_) {
		scenes.insert({ pair_.first, &(pair_.second) });
	}
}

Game::Game(const std::string & name_, const Settings & settings_) : name{ name_ }, scenes{}, settings { settings_ }, window{} {}

Game::~Game() {}

void Game::start(const std::string& startScene) {
	currentScene = scenes[startScene];
	updater.registerScene(*currentScene);
	openWindow();
	gameLoop = std::thread(&Game::startLoop, this);
	//begin the gameloop
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

void Game::setSettings(const Settings & set_) {
	settings = set_;
}

void Game::setSettings(const std::initializer_list<std::pair<std::string, int>> set_) {
	for (auto pair : set_) {
		settings.setField(pair.first, pair.second);
	}
}


void Game::addScene(Scene & scene_, const std::string& id) {
	scenes.insert({id, &scene_});
}

void Game::setScene(const std::string & id) {
	currentScene = scenes[id];
	updater.registerScene(*currentScene);

}


std::shared_ptr<Camera> Game::getCamera(const std::string & id) {
	return cameras[id];
}

void Game::setCamera(const std::string & id) {
	currentCamera = cameras[id];
}

void Game::openWindow() {
	if (window.isOpen())
		window.close();
	sf::ContextSettings contSettings{};
	contSettings.antialiasingLevel = 0;

	window.create(sf::VideoMode(settings.getField("width"), settings.getField("height")), name, sf::Style::Default, contSettings);
	window.setActive(false);
}

//currently doesn't deal with the camera, waiting till theres something too look at.
void Game::startLoop() {
	isLooping = true;

	double inputCalls{};
	double sensualsCalls{};
	sf::Clock timer;
	sf::Clock clock;
	float inputsTime{};
	float sensualsTime{};
	while (isLooping.load()) {
		float delta = clock.restart().asSeconds();
		inputsTime += delta;
		sensualsTime += delta;
		if (inputsTime >= 1.0/physicsSpeed) {
			std::vector<Action> actions;
			
			for (auto& controller : controllers) {
				controller->readInputs();
				for (Action action{ "", true }; controller->pollInputs(action);) {
					actions.push_back(action);
					action = Action{ "", true };
				}
			}
			
			updater.updateInputs(actions);
			inputCalls++;
		}
		if (sensualsTime >= 1.0/renderSpeed) {
			window.setActive(true);
			//window.setView(*currentCamera);
			window.clear(sf::Color::Black);
			updater.updateSensuals(window);
			sensualsCalls++;
			window.display();
			window.setActive(false);

			sf::Event event;
			while (window.pollEvent(event)) {
				if (event.type == sf::Event::Closed) {
					window.close();
					isLooping = false;
				}
			}
		}
		if (timer.getElapsedTime().asSeconds() >= 1) {
			std::cout << inputCalls / 1.0 << std::endl;
			std::cout << sensualsCalls / 1.0 << std::endl;
			inputCalls = 0;
			sensualsCalls = 0;
			timer.restart();
		}
		if (inputsTime >= 1 / physicsSpeed)
			inputsTime = 0;
		if (sensualsTime >= 1 / renderSpeed)
			sensualsTime = 0;
	}
}

void Game::stopLoop() {
	isLooping = false;
	gameLoop.join();
}

}
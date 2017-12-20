#include "stdafx.h"
#include "Game.h"

namespace msf {

	Game::Game(const std::string & name_) : name{ name_ }, scenes{}, window{ new sf::RenderWindow{} } {}

	Game::Game(const std::string& name_, std::initializer_list<std::pair<const std::string&, Scene&>> scenes_) : name{ name_ }, window{ new sf::RenderWindow{} } {
	for (auto& pair_ : scenes_) {
		scenes.insert({ pair_.first, std::shared_ptr<Scene>(&(pair_.second)) });
	}
}

Game::Game(const std::string & name_, std::initializer_list<std::pair<const std::string&, Scene&>> scenes_, const Settings & settings_) : name{ name_ }, settings{settings_}, window{ new sf::RenderWindow{} } {
	for (auto& pair_ : scenes_) {
		scenes.insert({ pair_.first, std::shared_ptr<Scene>(&(pair_.second)) });
	}
}

Game::Game(const std::string & name_, const Settings & settings_) : name{ name_ }, scenes{}, settings { settings_ }, window{ new sf::RenderWindow } {
}

Game::~Game() {}

void Game::start(const std::string& startScene) {
	currentScene = scenes[startScene];

	openWindow();
}

std::shared_ptr<Scene> Game::getScene(const std::string& id) {
	return scenes[id];
}

std::unique_ptr<Settings> Game::getSettings() {
	return std::unique_ptr<Settings>(&settings);
}

std::shared_ptr<Scene> Game::getCurrentScene() {
	return currentScene;
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
	scenes.insert({id, std::shared_ptr<Scene>(&scene_)});
}

void Game::setScene(const std::string & id) {
	currentScene = scenes[id];
}

void Game::openWindow() {
	if (window->isOpen())
		window->close();
	window->create(sf::VideoMode(settings.getField("width"), settings.getField("height")), name);\
}

}
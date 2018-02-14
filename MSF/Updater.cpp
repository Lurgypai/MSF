#include "stdafx.h"
#include "Updater.h"
#include <iostream>

namespace msf {

	Updater::Updater() : currentScene{ nullptr }, currentGroups{} {}

	Updater::Updater(Scene*& scene) : currentScene{ scene }, currentGroups{currentGroups} {}

	void Updater::registerScene(Scene*& scene_) {
		currentGroups.clear();
		currentScene = scene_;
	}

	void Updater::setCurrentGroups(std::vector<std::string> ids) {
		currentGroups.clear();
		for (auto& id : ids) {
			currentGroups.push_back(id);
		}
	}

	void Updater::addCurrentGroup(const std::string id) {
		currentGroups.push_back(id);
	}

	void Updater::removeCurrentGroup(const std::string id) {
		auto i = std::find(currentGroups.begin(), currentGroups.end(), id);
		if (i != currentGroups.end()) {
			currentGroups.erase(i);
		}
	}

	const std::vector<std::string>& Updater::getCurrentGroups() const {
		return currentGroups;
	}
}
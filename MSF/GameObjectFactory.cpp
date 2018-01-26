#include "stdafx.h"
#include "GameObjectFactory.h"

namespace msf {
	GameObjectFactory::GameObjectFactory(Scene * scene_) : scene{ scene_ }, pos{}, componentTag{} {
	}

	GameObjectFactory::GameObjectFactory(Scene * scene_, const sf::Vector2f pos_) : scene{ scene_ }, pos{ pos_ }, componentTag{} {
	}

std::vector<std::shared_ptr<GameObject>> GameObjectFactory::generate(int num) {
	std::vector<std::shared_ptr<GameObject>> gobjects;
	while (num--) {
		gobjects.push_back(generate());
	}
	return gobjects;
}

std::vector<std::shared_ptr<GameObject>> GameObjectFactory::generate(const std::string & groupId, int num)	{

	std::vector<std::shared_ptr<GameObject>> gobjects;
	while(num--) {
		gobjects.push_back(generate(groupId));
	}
	return gobjects;
}

std::shared_ptr<GameObject> GameObjectFactory::generate() {
	std::shared_ptr<GameObject> gobjectPtr = scene->addGObject(pos);
	fillComponents(gobjectPtr);
	gobjectPtr->componentTag = componentTag;
	return gobjectPtr;
}

std::shared_ptr<GameObject> GameObjectFactory::generate(const std::string & groupId) {
	std::shared_ptr<GameObject> gobjectPtr = scene->addGObject(pos, groupId);
	fillComponents(gobjectPtr);
	gobjectPtr->componentTag = componentTag;
	return gobjectPtr;
}

const Scene & GameObjectFactory::getScene() const {
	return *scene;
}

void GameObjectFactory::fillComponents(const std::shared_ptr<GameObject>& gobjectPtr) {

	if (componentTag & GameObject::Physics) {
		gobjectPtr->physics = physics->clone();
		gobjectPtr->physics->owner = gobjectPtr.get();
	}
	if (componentTag & GameObject::Graphics) {
		gobjectPtr->graphics = graphics->clone();
		gobjectPtr->graphics->owner = gobjectPtr.get();
	}
	if (componentTag & GameObject::Input) {
		gobjectPtr->input = input->clone();
		gobjectPtr->input->owner = gobjectPtr.get();
	}
	if (componentTag & GameObject::Audio) {
		gobjectPtr->audio = audio->clone();
		gobjectPtr->audio->owner = gobjectPtr.get();
	}
}

}
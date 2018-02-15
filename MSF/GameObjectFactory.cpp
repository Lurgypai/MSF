#include "stdafx.h"
#include "GameObjectFactory.h"

namespace msf {
GameObjectFactory::GameObjectFactory(Scene * scene_) : scene{ scene_ }, pos{}, componentTag{} {}

GameObjectFactory::GameObjectFactory(Scene * scene_, const sf::Vector2f pos_) : scene{ scene_ }, pos{ pos_ }, componentTag{} {}

GameObjectFactory::~GameObjectFactory()	{}

Scene* GameObjectFactory::getScene() {
	return scene;
}

std::shared_ptr<GameObject> GameObjectFactory::generate(const std::string & groupId) {
	std::shared_ptr<GameObject> gobjectPtr{ scene->addGObject(pos, groupId) };
	if (componentTag & GameObject::Logic) {
		gobjectPtr->logic = logic->clone();
		gobjectPtr->logic->owner = gobjectPtr.get();
	}
	if (componentTag & GameObject::Graphics) {
		gobjectPtr->graphics = graphics->clone();
		gobjectPtr->graphics->owner = gobjectPtr.get();
	}
	if (componentTag & GameObject::Audio) {
		gobjectPtr->audio = audio->clone();
		gobjectPtr->audio->owner = gobjectPtr.get();
	}
	gobjectPtr->componentTag = componentTag;
	return gobjectPtr;
}

void GameObjectFactory::generate(std::vector<std::shared_ptr<GameObject>>& gobjs, int num, const std::string& groupId)	{
	while(num--) {
		gobjs.push_back(generate(groupId));
	}
}
}
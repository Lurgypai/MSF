#pragma once
#include <vector>
#include <unordered_map>
#include <string>
#include "Scene.h"
//Updater updates its children
//read from action queue
/*
gameobjects will be registered by the scenes. scenes contol what is updated. Updaters will also maintain the "groups" sperately,
and vectors of pointers will be copied into the updater for registration.
scenes will regsiter all of there objects at once, and the scenes will manipulate what are update
register a scene
updating will be done through the scene, do not copy the groups, access using the groups
scene will be told what to update.
need each Updater, and a Updater manager to register the scene with all the Updaters.
basics done
add the master that can update them all individually
separated Updaters MAY BE REMOVED, switch to a single master Updater, pass it the type to update, and give it a pointer/reference to the update queue

UPDATE:
multiple updaters removed:
single updater updates inputs and sensuals
*/
namespace msf {

	class Updater {
	public:
		Updater();
		Updater(Scene& scene);
		Updater(Scene&& scene) = delete;

		inline void updateInputs(std::vector<Action>& actions) {
			for (const auto& tag : currentGroups) {
				for (auto& dobject : currentScene->getDOGroup(tag)) {
					dobject->update(actions);
				}
				for (auto& gobject : currentScene->getGOGroup(tag)) {
					gobject->updateInput(actions);
				}
			}
		}

		inline void updateSensuals(sf::RenderWindow& window) {
			for (auto& tag : currentGroups) {
				for (auto& gobject : currentScene->getGOGroup(tag)) {
					gobject->updateSensuals(window);
				}
			}
		}

		void registerScene(Scene& scene_);
		void registerScene(Scene&& scene_) = delete;

		void setCurrentGroups(std::initializer_list<std::string> ids);
		void setCurrentGroups(std::vector<std::string> ids);
		void addCurrentGroup(const std::string id);
		void removeCurrentGroup(const std::string id);
		std::vector<std::string> getCurrentGroups()  const;

	protected:
		Scene* currentScene;
		std::vector<std::string> currentGroups;
	};
}
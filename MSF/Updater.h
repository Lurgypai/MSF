#pragma once
#include <vector>
#include <unordered_map>
#include <string>
#include "Scene.h"
#include "Camera.h"
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
		Updater(Scene*& scene);

		void registerScene(Scene*& scene_);
		void setCurrentGroups(std::vector<std::string> ids);
		void addCurrentGroup(const std::string id);
		void removeCurrentGroup(const std::string id);

		//the reason it restarts a loop if it detects a size change is to protect from invalidation due to a size change, don't want to miss anything when updating, and
		//objects can delete as many of eachother as they want.
		//a better solution would be that deleting marks an object for deletion, and then it is removed in a final pass after updating. But I'm lazy for now.
		inline void updateInputs() {
			for (const auto& tag : currentGroups) {
				for (auto& dobject : currentScene->getDOGroup(tag)) {
					dobject->update();
				}
				for (auto& gobject : currentScene->getGOGroup(tag)) {
					gobject->updateInput();
				}
			}

			//deleteion pass
			for (const auto& tag : currentGroups) {
				for (int i = 0; i != currentScene->getGOGroup(tag).size(); i++) {
					if (currentScene->getGOGroup(tag)[i]->destroyed()) {
						currentScene->removeGObject(currentScene->getGOGroup(tag)[i]->getTag(), tag);
						i--;
					}
				}
			}
		}

		inline void updateSensuals(std::unordered_map<int, std::shared_ptr<Camera>> cams, std::shared_ptr<Camera> currentCam, sf::RenderWindow& window) {
			for (auto& tag : currentGroups) {
				if (currentScene->hasSpecialCam(tag)) {
					window.setView(cams[currentScene->getSpecialCam(tag)]->getView());
				}
				else {
					window.setView(currentCam->getView());
				}
				for (auto& gobject : currentScene->getGOGroup(tag)) {
					gobject->updateSensuals(window);
				}
			}
		}

		const std::vector<std::string>& getCurrentGroups()  const;

	protected:
		Scene* currentScene;
		std::vector<std::string> currentGroups;
	};
}
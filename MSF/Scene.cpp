#include "stdafx.h"
#define DEFAULT_GROUP_ID "default"

#include "Scene.h"
#include <iostream>

namespace msf {

	using std::make_shared;
	using std::unordered_map;
	using std::string;
	using std::vector;
	using std::shared_ptr;

	using gobject_vec_map = std::unordered_map<std::string, std::vector<GameObject*>>;
	using gobject_vec = std::vector<GameObject*>;

	Scene::Scene(void) :
		objects{},
		groupIds(1, DEFAULT_GROUP_ID),
		groups{ {DEFAULT_GROUP_ID, gobject_vec() } }
	{}

	Scene::Scene(Scene & scene_) :
		groupIds(scene_.groupIds), groups{}, objects{} {

		for (auto& pair : scene_.groups) {
			gobject_vec vec{};
			for (auto& gobject : pair.second) {
				vec.push_back(gobject);
			}
			groups.insert(std::pair<string, gobject_vec>(pair.first, vec));
		}
		//if the source objects and accepter objects are the same, we don't want to clear it, but if we append it will copy whats already there. so make a new one, fill and set the old to it
		gobject_vec objects_;
		for (auto& gobject : scene_.objects) {
			objects_.push_back(gobject);
		}
		objects = objects_;
	}

	Scene::Scene(Scene && scene_) :
		groupIds(scene_.groupIds), groups{}, objects{} {

		for (auto& pair : scene_.groups) {
			gobject_vec vec{};
			for (auto& gobject_ptr : pair.second) {
				vec.push_back(std::move(gobject_ptr));
			}
			groups.insert(std::pair<string, gobject_vec>(pair.first, vec));
		}

		gobject_vec objects_;
		for (auto& gobject : scene_.objects) {
			objects_.push_back(std::move(gobject));
		}
		objects = objects_;
	}

	void Scene::updateAll() {
		for (auto& gobject : objects) {
			gobject->update();
		}
	}

	void Scene::update(const std::string& groupId){
		for (auto& gobject : groups[groupId]) {
			gobject->update();
		}
	}

	gobject_vec& Scene::getGroup(const std::string& groupId) {
		if (groups.find(groupId) != groups.end())
		return (groups[groupId]);
	}

	void Scene::removeGroup(const std::string & groupId) {
		if (std::find(groupIds.begin(), groupIds.end(), groupId) != groupIds.end()) {
			groups.erase(groupId);
			for (auto string = groupIds.begin(); string != groupIds.end(); string++) {
				if (*string == groupId) {
					groupIds.erase(string);
				}
			}
		}
	}

	gobject_vec& Scene::getObjects() {
		return objects;
	}

	void Scene::addObject(GameObject & obj_) {
		obj_.setScene(*this);
		groups[DEFAULT_GROUP_ID].push_back(&obj_);
		objects.push_back(&obj_);
	}

	void Scene::addObject(GameObject & obj_, const string & groupId) {
		obj_.setScene(*this);
		groups[groupId].push_back(&obj_);
		objects.push_back(&obj_);
	}

	bool Scene::hasObject(const GameObject & obj_) const {
		for (const auto& gobject : objects) {
			if (*gobject == obj_) {
				return true;
			}
		}
		return false;
	}

	const vector<string>& Scene::getGroupIds() const {
		return groupIds;
	}

	void Scene::addGroup(const string groupId) {
		groups[groupId] = {};
	}

	bool Scene::hasGroup(const std::string & groupId_) const {
		return std::find(groupIds.begin(), groupIds.end(), groupId_) != groupIds.end();
	}

	void Scene::operator=(const Scene & scene_) {
			groupIds = scene_.groupIds;
			for (auto& pair : scene_.groups) {
				gobject_vec vec{};
				for (auto& gobject : pair.second) {
					vec.push_back(gobject);
				}
				groups.insert(std::pair<string, gobject_vec>(pair.first, vec));
			}

			gobject_vec objects_;
			for (auto& gobject : scene_.objects) {
				objects_.push_back(gobject);
			}
			objects = objects_;
	}

	void Scene::operator=(Scene && scene_) {
		groupIds = scene_.groupIds;
		for (auto& pair : scene_.groups) {
			gobject_vec vec{};
			for (auto& gobject : pair.second) {
				vec.push_back(std::move(gobject));
			}
			groups.insert(std::pair<string, gobject_vec>(pair.first, vec));
		}

		gobject_vec objects_;
		for (auto& gobject : scene_.objects) {
			objects_.push_back(std::move(gobject));
		}
		objects = objects_;
	}

	bool Scene::operator==(const Scene & scene_) const {
		/* if this doesn't work right, other option here (incomplete):
		bool predicate{true};
		//make sure it has the group and object
		for (string groupId : groupIds) {
			if (scene_.hasGroup(groupId)) {
				for (auto gobject : groups[groupId]) {
					if (scene_.hasObject(*gobject)) {

						//find the string, loop the vectors, compare objects
						for (string groupId_ : scene_.groupIds) {
							if (groupId_ == groupId) {
								for (auto gobject : groups[groupId]) {
									for (auto gobject_ : groups[groupId_]) {
										if (*gobject != *gobject_) {
											predicate = false;
											break;
										}
									}
								}
							}
						}
					}
					else {
						predicate = false;
						break;
					}
				}
			}
			else {
				predicate = false;
				break;
			}
		}
		*/
		return (groups == scene_.groups) && (groupIds == scene_.groupIds) && (objects == scene_.objects);
	}

	bool Scene::operator!=(const Scene& scene_) const {

		return (groups != scene_.groups) || (groupIds != scene_.groupIds) || (objects != scene_.objects);
	}
}
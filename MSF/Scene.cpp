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

	using gobject_vec_map = std::unordered_map<std::string, std::vector<std::shared_ptr<GameObject>>>;
	using gobject_vec = std::vector<std::shared_ptr<GameObject>>;

	Scene::Scene(void) :
		objects{},
		groupIds(1, DEFAULT_GROUP_ID),
		groups{ {DEFAULT_GROUP_ID, gobject_vec() } }
	{}

	Scene::Scene(Scene & scene_) :
		groupIds(scene_.groupIds), groups{}, objects{} {

		for (auto pair : scene_.groups) {
			gobject_vec vec{};
			for (auto gobject_ptr : pair.second) {
				vec.push_back(shared_ptr<GameObject> {new GameObject{ *gobject_ptr }});
			}
			groups.insert(std::pair<string, gobject_vec>(pair.first, vec));
		}

		for (auto gobject : scene_.objects) {
			objects.push_back(shared_ptr<GameObject>(new GameObject(*gobject)));
		}
	}

	Scene::Scene(Scene && scene_) :
		groupIds(scene_.groupIds), groups{}, objects{} {

		for (auto pair : scene_.groups) {
			gobject_vec vec{};
			for (auto gobject_ptr : pair.second) {
				vec.push_back(std::move(gobject_ptr));
			}
			groups.insert(std::pair<string, gobject_vec>(pair.first, vec));
		}

		for (auto gobject : scene_.objects) {
			objects.push_back(std::move(gobject));
		}
	}

	void Scene::updateAll() {
		for (auto& objectptr : objects) {
			objectptr->update();
			std::cout << "flag" << std::endl;
		}
		std::cout << "flag" << std::endl;
	}

	void Scene::update(const std::string& groupId){
		for (auto& objectptr : groups[groupId]) {
			objectptr->update();
		}
	}

	shared_ptr<gobject_vec> Scene::getGroup(const string & groupId) {
		if (groups.find(groupId) != groups.end())
		return std::shared_ptr<gobject_vec>(&(groups[groupId]));
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

	shared_ptr<gobject_vec> Scene::getObjects() {
		return std::shared_ptr<gobject_vec>(&objects);
	}

	void Scene::addObject(GameObject & obj_) {
		obj_.setScene(*this);
		groups[DEFAULT_GROUP_ID].push_back(std::shared_ptr<GameObject>(&obj_));
		objects.push_back(std::shared_ptr<GameObject>(&obj_));
	}

	void Scene::addObject(GameObject & obj_, const string & groupId) {
		obj_.setScene(*this);
		groups[groupId].push_back(std::shared_ptr<GameObject>(&obj_));
		objects.push_back(std::shared_ptr<GameObject>(&obj_));
	}

	bool Scene::hasObject(const GameObject & obj_) const {
		bool predicate{ false };
		for (auto gobject : objects) {
			if (*gobject == obj_) {
				predicate = true;
				break;
			}
		}
		return predicate;
	}

	vector<string> Scene::getGroupIds() {
		return groupIds;
	}

	void Scene::addGroup(const string & groupId) {
		groups[groupId] = {};
	}

	void Scene::addGroup(const string & groupId, std::initializer_list<GameObject> objs_) {
		gobject_vec objs{};
		for (auto obj : objs_) {
			objs.push_back(shared_ptr<GameObject>(&obj));
			objects.push_back(shared_ptr<GameObject>(&obj));
		}
		groups[groupId] = objs;
		groupIds.push_back(groupId);
	}

	void Scene::addGroup(const string & groupId, const std::vector<std::shared_ptr<GameObject>>& objs_) {
		groups[groupId] = objs_;
		groupIds.push_back(groupId);
		objects.insert(objects.end(), objs_.begin(), objs_.end());
	}

	bool Scene::hasGroup(const std::string & groupId_) const {
		return std::find(groupIds.begin(), groupIds.end(), groupId_) != groupIds.end();
	}

	void Scene::operator=(const Scene & scene_) {
			groupIds = scene_.groupIds;
			for (auto pair : scene_.groups) {
				gobject_vec vec{};
				for (auto gobject_ptr : pair.second) {
					vec.push_back(shared_ptr<GameObject> {new GameObject{ *gobject_ptr }});
				}
				groups.insert(std::pair<string, gobject_vec>(pair.first, vec));
			}

			for (auto gobject : scene_.objects) {
				objects.push_back(shared_ptr<GameObject>(new GameObject(*gobject)));
			}
	}

	void Scene::operator=(Scene && scene_) {
		groupIds = scene_.groupIds;
		for (auto pair : scene_.groups) {
			gobject_vec vec{};
			for (auto gobject_ptr : pair.second) {
				vec.push_back(std::move(gobject_ptr));
			}
			groups.insert(std::pair<string, gobject_vec>(pair.first, vec));
		}

		for (auto gobject : scene_.objects) {
			objects.push_back(std::move(gobject));
		}
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
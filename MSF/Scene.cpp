#include "stdafx.h"

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

	using dobject_vec_map = std::unordered_map<std::string, std::vector<std::shared_ptr<DataObject>>>;
	using dobject_vec = std::vector<std::shared_ptr<DataObject>>;

	Scene::Scene(void) :
		gogroupIds(1, default_groupid),
		gogroups{ { default_groupid, gobject_vec{} } },

		dogroupIds(1, default_groupid),
		dogroups{ { default_groupid, dobject_vec{} } }
	{	}

	Scene::Scene(const Scene & scene_) :
		gogroupIds(scene_.gogroupIds), gogroups{}, dogroupIds{ scene_.dogroupIds }, dogroups{} {
		gogroups.clear();
		for (auto& pair : scene_.gogroups) {
			gobject_vec vec{};
			for (auto& gobject : pair.second) {
				vec.push_back(gobject);
			}
			gogroups.insert(std::pair<string, gobject_vec>(pair.first, vec));
		}

		dogroups.clear();
		for (auto& pair : scene_.dogroups) {
			dobject_vec vec{};
			for (auto& dobject : pair.second) {
				vec.push_back(dobject);
			}
			dogroups.insert(std::pair<string, dobject_vec>(pair.first, vec));
		}
		//if the source objects and accepter objects are the same, we don't want to clear it, but if we append it will copy whats already there. so make a new one, fill and set the old to it
	}

	Scene::Scene(Scene && scene_) :
		gogroupIds(scene_.gogroupIds), gogroups{}, dogroupIds{ scene_.dogroupIds }, dogroups{} {

		for (auto& pair : scene_.gogroups) {
			gobject_vec vec{};
			for (auto& gobject_ptr : pair.second) {
				vec.push_back(std::move(gobject_ptr));
			}
			gogroups.insert(std::pair<string, gobject_vec>(pair.first, vec));
		}

		for (auto& pair : scene_.dogroups) {
			dobject_vec vec{};
			for (auto& dobject_ptr : pair.second) {
				vec.push_back(std::move(dobject_ptr));
			}
			dogroups.insert(std::pair<string, dobject_vec>(pair.first, vec));
		}
	}

	//GAMEOBJECTS

	void Scene::removeGOGroup(const std::string & gogroupId) {
		if (std::find(gogroupIds.begin(), gogroupIds.end(), gogroupId) != gogroupIds.end()) {
			gogroups.erase(gogroupId);
			for (auto string = gogroupIds.begin(); string != gogroupIds.end(); string++) {
				if (*string == gogroupId) {
					gogroupIds.erase(string);
				}
			}
		}
	}

	std::shared_ptr<GameObject> Scene::addGObject(const string & gogroupId) {
		gogroups[gogroupId].emplace_back(std::make_shared<GameObject>(sf::Vector2f{0,0}));
		gogroups[gogroupId][gogroups[gogroupId].size() - 1]->scene = this;
		return gogroups[gogroupId][gogroups[gogroupId].size() - 1];
	}

	std::shared_ptr<GameObject> Scene::addGObject(const sf::Vector2f& pos, const string & gogroupId) {
		gogroups[gogroupId].emplace_back(std::make_shared<GameObject>(pos));
		gogroups[gogroupId][gogroups[gogroupId].size() - 1]->scene = this;
		return gogroups[gogroupId][gogroups[gogroupId].size() - 1];
	}

	void Scene::removeGObject(const uint64_t & tag, const std::string& groupId) {
		for (auto& i = gogroups[groupId].begin(); i != gogroups[groupId].end(); i++) {
			if ((*i)->getTag() == tag) {
				gogroups[groupId].erase(i);
				return;
			}
		}
	}

	std::shared_ptr<GameObject> Scene::getGObject(const uint64_t & tag, const std::string & gogroupId) {
		for (const auto& gobject : gogroups[gogroupId]) {
			if (gobject->getTag() == tag) {
				return gobject;
			}
		}
	}

	bool Scene::hasGObject(const GameObject & obj_, const std::string& gogroupId) const {
		for (const auto& gobject : gogroups.at(gogroupId)) {
			if (*gobject == obj_) {
				return true;
			}
		}
		return false;
	}

	const vector<string>& Scene::getGOGroupIds() const {
		return gogroupIds;
	}

	void Scene::addGOGroup(const string gogroupId) {
		gogroups[gogroupId] = {};
	}

	bool Scene::hasGOGroup(const std::string & gogroupId_) const {
		return std::find(gogroupIds.begin(), gogroupIds.end(), gogroupId_) != gogroupIds.end();
	}
	//DATAOBJECTS

	void Scene::removeDOGroup(const std::string & dogroupId) {
		if (std::find(gogroupIds.begin(), gogroupIds.end(), dogroupId) != gogroupIds.end()) {
			dogroups.erase(dogroupId);
			for (auto string = gogroupIds.begin(); string != gogroupIds.end(); string++) {
				if (*string == dogroupId) {
					gogroupIds.erase(string);
				}
			}
		}
	}

	std::shared_ptr<DataObject> Scene::addDObject(const string & dogroupid) {
		dogroups[dogroupid].emplace_back(std::make_shared<DataObject>());
		dogroups[dogroupid][dogroups[dogroupid].size() - 1]->scene = this;
		return dogroups[dogroupid][dogroups[dogroupid].size() - 1];
	}

	std::shared_ptr<DataObject> Scene::getDObject(const uint64_t & tag, const std::string & dogroupId) {
		for (const auto& dobject : dogroups[dogroupId]) {
			if (dobject->tag == tag) {
				return dobject;
			}
		}
	}

	bool Scene::hasDObject(const DataObject & obj_, const std::string& dogroupId) const {
		for (const auto& gobject : dogroups.at(dogroupId)) {
			if (*gobject == obj_) {
				return true;
			}
		}
		return false;
	}

	const vector<string>& Scene::getDOGroupIds() const {
		return dogroupIds;
	}

	void Scene::addDOGroup(const string dogroupId) {
		dogroups[dogroupId] = {};
	}

	bool Scene::hasDOGroup(const std::string & dogroupId_) const {
		return std::find(dogroupIds.begin(), dogroupIds.end(), dogroupId_) != dogroupIds.end();
	}

	void Scene::addSpecialCamera(const std::string & groupId, int camNum) {
		specialCameras.insert({ groupId, camNum });
	}

	void Scene::removeSpecialCamera(const std::string & groupId) {
		specialCameras.erase(groupId);
	}

	int Scene::getSpecialCam(const std::string & groupId) {
		return specialCameras[groupId];
	}

	bool Scene::hasSpecialCam(const std::string & groupId) {
		return specialCameras.find(groupId) != specialCameras.end();
	}


	void Scene::operator=(const Scene & scene_) {
		gogroupIds = scene_.gogroupIds;
		gogroups = gobject_vec_map{};
		for (auto& pair : scene_.gogroups) {
			gobject_vec vec{};
			for (auto& gobject : pair.second) {
				vec.push_back(gobject);
			}
			gogroups.insert(std::pair<string, gobject_vec>(pair.first, vec));
		}
		dogroupIds = scene_.dogroupIds;
		dogroups = dobject_vec_map{};
		for (auto& pair : scene_.dogroups) {
			dobject_vec vec{};
			for (auto& dobject : pair.second) {
				vec.push_back(dobject);
			}
			dogroups.insert(std::pair<string, dobject_vec>(pair.first, vec));
		}
	}

	void Scene::operator=(Scene && scene_) {
		gogroupIds = scene_.gogroupIds;
		gogroups = gobject_vec_map{};
		for (auto& pair : scene_.gogroups) {
			gobject_vec vec{};
			for (auto& gobject : pair.second) {
				vec.push_back(std::move(gobject));
			}
			gogroups.insert(std::pair<string, gobject_vec>(pair.first, vec));
		}


		dogroupIds = scene_.dogroupIds;
		dogroups = dobject_vec_map{};
		for (auto& pair : scene_.dogroups) {
			dobject_vec vec{};
			for (auto& dobject : pair.second) {
				vec.push_back(std::move(dobject));
			}
			dogroups.insert(std::pair<string, dobject_vec>(pair.first, vec));
		}
	}

	const std::string Scene::default_groupid = "default";
}
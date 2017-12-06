#include "stdafx.h"
#define DEFAULT_GROUP_ID "default"

#include "Scene.h"

using std::make_shared;

namespace msf {

	msf::Scene::Scene(void) :
		objects(),
		groupIds(1, DEFAULT_GROUP_ID),
		groups{ {DEFAULT_GROUP_ID, gobject_vec() } }
	{}

	msf::Scene::Scene(Scene & scene_) :
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

	msf::Scene::Scene(Scene && scene_) :
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

	shared_ptr<gobject_vec> msf::Scene::getGroup(const string & groupId) {
		if (groups.find(groupId) != groups.end())
		return make_shared<gobject_vec>(groups[groupId]);
	}

	shared_ptr<gobject_vec> msf::Scene::getObjects() {
		return make_shared<gobject_vec>(objects);
	}

	void msf::Scene::addObject(GameObject & obj_) {
		groups[DEFAULT_GROUP_ID].push_back(make_shared<GameObject>(obj_));
	}

	void msf::Scene::addObject(GameObject & obj_, const string & groupId) {
		groups[groupId].push_back(make_shared<GameObject>(obj_));
		objects.push_back(make_shared<GameObject>(obj_));
	}

	vector<string> msf::Scene::getGroupIds() {
		return groupIds;
	}

	void msf::Scene::createGroup(const string & groupId) {
		groups[groupId] = {};
	}

	void msf::Scene::createGroup(const string & groupId, std::initializer_list<GameObject> objs_) {
		gobject_vec objs{};
		for (auto obj : objs_) {
			objs.push_back(make_shared<GameObject>(obj));
			objects.push_back(make_shared<GameObject>(obj));
		}
		groups[groupId] = objs;
		groupIds.push_back(groupId);
	}

	void msf::Scene::createGroup(const string & groupId, const gobject_vec & objs_) {
		groups[groupId] = objs_;
		groupIds.push_back(groupId);
		objects.insert(objects.end(), objs_.begin(), objs_.end());
	}

	void msf::Scene::operator=(const Scene & scene_) {
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

	void msf::Scene::operator=(Scene && scene_) {
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

}
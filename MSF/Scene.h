//a scene is anything that holds game objects for use
#pragma once
#include <unordered_map>
#include <vector>
#include <string>
#include <memory>

#include "GameObject.h"

namespace msf {

	using std::unordered_map;
	using std::string;
	using std::vector;
	using std::shared_ptr;

	using gobject_vec_map = unordered_map<string, vector<shared_ptr<msf::GameObject>>>;
	using gobject_vec = vector<shared_ptr<msf::GameObject>>;

class Scene {
public:
	Scene(void);
	Scene(Scene& scene_);
	Scene(Scene&& scene_);

	shared_ptr<gobject_vec> getGroup(const string& groupId);
	shared_ptr<gobject_vec> getObjects();

	void addObject(GameObject& obj_);
	void addObject(GameObject& obj_, const string& groupId);
	
	vector<string> getGroupIds();
	void createGroup(const string& groupId);
	void createGroup(const string& groupId, std::initializer_list<GameObject> objs_);
	void createGroup(const string& groupId, const gobject_vec& objs_);

	void operator=(const Scene& scene_);
	void operator=(Scene&& scene_);
protected:
	gobject_vec_map groups;
	gobject_vec objects;
	vector<string> groupIds;
};

}
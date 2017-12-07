//a scene is anything that holds game objects for use
#pragma once
#include <unordered_map>
#include <vector>
#include <string>
#include <memory>

#include "GameObject.h"

namespace msf {

	class GameObject;

class Scene {
public:
	Scene(void);
	Scene(Scene& scene_);
	Scene(Scene&& scene_);

	std::shared_ptr<std::vector<std::shared_ptr<GameObject>>> getGroup(const std::string& groupId);
	void removeGroup(const std::string& groupId);
	std::shared_ptr<std::vector<std::shared_ptr<GameObject>>> getObjects();

	void addObject(GameObject& obj_);
	void addObject(GameObject& obj_, const std::string& groupId);
	
	bool hasObject(const GameObject& obj_) const;

	std::vector<std::string> getGroupIds();
	void addGroup(const std::string& groupId);
	void addGroup(const std::string& groupId, std::initializer_list<GameObject> objs_);
	void addGroup(const std::string& groupId, const std::vector<std::shared_ptr<GameObject>>& objs_);
	bool hasGroup(const std::string& groupId_) const;

	void operator=(const Scene& scene_);
	void operator=(Scene&& scene_);

	bool operator==(const Scene& scene_) const;
	bool operator!=(const Scene& scene_) const;
protected:
	std::unordered_map<std::string, std::vector<std::shared_ptr<GameObject>>> groups;
	std::vector<std::shared_ptr<GameObject>> objects;
	std::vector<std::string> groupIds;
};

}
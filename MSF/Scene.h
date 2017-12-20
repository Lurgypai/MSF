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

	void updateAll();
	void update(const std::string& groupId);

	std::vector<GameObject*>& getGroup(const std::string& groupId);
	void removeGroup(const std::string& groupId);
	std::vector<GameObject*>& getObjects();

	void addObject(GameObject& obj_);
	void addObject(GameObject& obj_, const std::string& groupId);
	
	//make sure it can't be a new one as we store a pointer to it (may change later)
	void addObject(GameObject&& obj_) = delete;
	void addObject(GameObject&& obj_, const std::string& groupId) = delete;

	bool hasObject(const GameObject& obj_) const;

	const std::vector<std::string>& getGroupIds() const;
	void addGroup(const std::string groupId);
	bool hasGroup(const std::string& groupId_) const;

	void operator=(const Scene& scene_);
	void operator=(Scene&& scene_);

	bool operator==(const Scene& scene_) const;
	bool operator!=(const Scene& scene_) const;
protected:
	//either references or raw pointers then
	std::unordered_map<std::string, std::vector<GameObject*>> groups;
	std::vector<GameObject*> objects;
	std::vector<std::string> groupIds;
};

}
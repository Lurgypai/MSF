//a scene is anything that holds game objects for use
#pragma once
#include <unordered_map>
#include <vector>
#include <string>
#include <memory>

#include "GameObject.h"
#include "DataObject.h"

namespace msf {

	class GameObject;
	class DataObject;

	class Scene {
	public:
		Scene(void);
		Scene(Scene& scene_);
		Scene(Scene&& scene_);

		static const std::string default_groupid;

		//GObject
		inline const std::vector<std::shared_ptr<GameObject>>& getGOGroup(const std::string& gogroupId) {
			return gogroups[gogroupId];
		}
		void removeGOGroup(const std::string& groupId);

		std::shared_ptr<GameObject> addGObject(const std::string& groupId = default_groupid);
		std::shared_ptr<GameObject> addGObject(const sf::Vector2f& pos, const std::string& groupId = default_groupid);
		void removeGObject(const uint64_t& tag, const std::string& groupId);

		std::shared_ptr<GameObject> getGObject(const uint64_t& tag, const std::string& groupId = default_groupid);
		bool hasGObject(const GameObject& obj_, const std::string& groupId) const;

		const std::vector<std::string>& getGOGroupIds() const;
		void addGOGroup(const std::string groupId);
		bool hasGOGroup(const std::string& groupId_) const;

		//DObject
		inline const std::vector<std::shared_ptr<DataObject>>& getDOGroup(const std::string& dogroupId) {
			return dogroups[dogroupId];
		}
		void removeDOGroup(const std::string& groupId);

		std::shared_ptr<DataObject> addDObject(const std::string& groupId = default_groupid);

		std::shared_ptr<DataObject> getDObject(const uint64_t& tag, const std::string& groupId = default_groupid);
		bool hasDObject(const DataObject& obj_, const std::string& groupId) const;

		const std::vector<std::string>& getDOGroupIds() const;
		void addDOGroup(const std::string groupId);
		bool hasDOGroup(const std::string& groupId_) const;

		void operator=(const Scene& scene_);
		void operator=(Scene&& scene_);
	private:
		//either references or raw pointers then
		std::unordered_map<std::string, std::vector<std::shared_ptr<GameObject>>> gogroups;
		std::vector<std::string> gogroupIds;

		std::unordered_map<std::string, std::vector<std::shared_ptr<DataObject>>> dogroups;
		std::vector<std::string> dogroupIds;

		sf::RenderWindow* window;
	};

}
#pragma once
#include <vector>
#include <memory>

#include "Action.h"
/*
holds actions so that they can be retrieved by what needs them
retrieve action function takes an action, fills it, returns boolean
passAct to give actions
*/
namespace msf {

class ActionQueue {
public:
	~ActionQueue() {
		clearActions();
	}

	inline std::vector<Action*>& getBuffer() {
		return buffer;
	}

	inline bool isEmpty() {
		return buffer.empty();
	}

	inline void storeAction(Action*& action) {
		buffer.push_back(action);
	}

	inline void deleteAction() {
		delete buffer[buffer.size() - 1];
		buffer.pop_back();
	}

	inline void clearActions() {
		for (auto iter = buffer.begin(); iter != buffer.end();) {
			delete *iter;
			iter = buffer.erase(iter);
			if (iter != buffer.end())
				iter++;
		}
	}
private:
	std::vector<Action*> buffer;
};
}
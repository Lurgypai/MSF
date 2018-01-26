#pragma once
#include <vector>
#include <string>
/*
holds actions so that they can be retrieved by what needs them
retrieve action function takes an action, fills it, returns boolean
passAct to give actions
*/
namespace msf {
	
struct Action {
	std::string id;
	bool isNothing;
};

class ActionQueue {
public:
	inline bool pollAction(Action& act) {
		if (actions.size() != 0) {
			act = actions[actions.size() - 1];
			actions.pop_back();
			return true;
		}
		return false;
	}

	inline bool isEmpty() {
		return actions.empty();
	}

	inline void storeAction(const Action action) {
		actions.push_back(action);
	}
private:
	std::vector<Action> actions;
};
}
#pragma once
#include "Controller.h"
class SimpleController : public msf::Controller{
public:
	SimpleController();
	~SimpleController();
	void readInputs();
	bool pollInputs(msf::Action& action);
private:
	std::vector<msf::Action> actionBuffer;
	bool RDown;
	bool LDown;
};


#pragma once
#include "ActionQueue.h"

namespace msf {

class Controller
{
public:
	Controller() {};
	virtual ~Controller() {};
	virtual void readInputs() = 0;
	virtual bool pollInputs(Action& action) = 0;
};

}
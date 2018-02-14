#pragma once
#include <memory>
#include "Action.h"

namespace msf {

class Controller
{
public:
	Controller() {};
	virtual ~Controller() {};
	virtual void readInputs() = 0;
	virtual bool pollInputs(std::shared_ptr<msf::Action>& action) = 0;
};

}
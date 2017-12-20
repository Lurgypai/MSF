#pragma once
#include "GameObject.h"
namespace msf {

class InputComponent {
public:
	virtual void update(GameObject& obj) =0;
};

}
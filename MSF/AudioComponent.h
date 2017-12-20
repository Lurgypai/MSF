#pragma once
#include "GameObject.h"

namespace msf{
class AudioComponent {
public:
	virtual void update(GameObject& obj) = 0;
};
}
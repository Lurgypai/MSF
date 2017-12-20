#pragma once
#include "GameObject.h"

namespace msf {
	class GraphicsComponent {
	public:
		virtual void update(GameObject& obj) =0;
	};
}
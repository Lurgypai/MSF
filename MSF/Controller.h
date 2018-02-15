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
		std::vector<Action>& getBuffer() {
			return buffer;
		}
		void clearBuffer() {
			buffer.clear();
		}
	protected:
		std::vector<Action> buffer;
	};

}
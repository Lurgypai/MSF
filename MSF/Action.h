#pragma once
#include "stdafx.h"
#include <string>
#include <cstdint>
namespace msf {

	class Action {
	public:
		uint32_t id;
		bool isNothing;
		Action() : id{}, isNothing{ true } {};
		Action(const uint32_t& id, bool isNothing_) : id(id), isNothing{ isNothing_ } {};
		virtual ~Action() {};

		void operator=(const Action& act) {
			id = act.id;
			isNothing = act.isNothing;
		}
	};
}
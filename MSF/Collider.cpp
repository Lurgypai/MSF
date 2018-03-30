#include "stdafx.h"
#include "Collider.h"

namespace msf {
	Collider::Collider() : shape{nullptr} {}
	Collider::Collider(const Collider & other) : shape{ other.shape->clone() } {}
	Collider::~Collider() {}

Shape * Collider::getShape() {
	return shape.get();
}
}
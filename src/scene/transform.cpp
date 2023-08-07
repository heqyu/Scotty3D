
#include "transform.h"

Mat4 Transform::local_to_parent() const {
	return Mat4::translate(translation) * rotation.to_mat() * Mat4::scale(scale);
}

Mat4 Transform::parent_to_local() const {
	return Mat4::scale(1.0f / scale) * rotation.inverse().to_mat() * Mat4::translate(-translation);
}

Mat4 Transform::local_to_world() const {
	//A1T1: local_to_world
	//don't use Mat4::inverse() in your code.

	if (parent.expired()) {
		return local_to_parent();
	}
	auto parent_ptr = parent.lock();
	return parent_ptr->local_to_world() * local_to_parent();

	// return Mat4::I; //<-- wrong, but here so code will compile
}

Mat4 Transform::world_to_local() const {
	//A1T1: world_to_local
	//don't use Mat4::inverse() in your code.

	// 1. use inverse
	Mat4 local_to_world = this->local_to_world();
	Mat4 ret1 = local_to_world.inverse();

	// 2. donot use inverse
	if (parent.expired()) {
		return parent_to_local();
	}
	auto parent_ptr = parent.lock();
	Mat4 ret2 = parent_to_local() * parent_ptr->world_to_local();

	assert(ret1.approx_equal(ret2));

	return ret2;
	// assert(ret1 == ret2); approx equal

	// return Mat4::I; //<-- wrong, but here so code will compile
}

bool operator!=(const Transform& a, const Transform& b) {
	return a.parent.lock() != b.parent.lock() || a.translation != b.translation ||
	       a.rotation != b.rotation || a.scale != b.scale;
}

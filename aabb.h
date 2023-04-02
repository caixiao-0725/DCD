#pragma once

#include "origin.h"

class aabb {
public:

	vec3d _min;
	vec3d _max;

	aabb();
	aabb(const vec3d &);

	bool overlaps(const aabb& b) const;
	bool inside(const vec3d &) const;

	aabb &operator += (const vec3d &);
	aabb &operator += (const aabb &);

	double width()  const { return _max[0] - _min[0]; }
	double height() const { return _max[1] - _min[1]; }
	double depth()  const { return _max[2] - _min[2]; }
	vec3d center() { return (_min+_max)*0.5; }

	void empty();
};